// 6r0m, MIT liscence

#include "Kismet/KismetMathLibrary.h"

#include "Manipulator/Core/Templates/RoboManipulator.h"
#include "Manipulator/Core/Templates/RotatingMesh.h"

#define GetMeshWithName(name) #name, &name

ARoboManipulator::ARoboManipulator()
{
 	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	if (Root) SetRootComponent(Root);

	CreateRotatingMeshes({{ GetMeshWithName(BaseMesh) }, { GetMeshWithName(UpperArm) }, { GetMeshWithName(ForeArm) }});	
}

void ARoboManipulator::ManipulatePackage()
{
	if (Package)
	{
		NextAction(EManipulatorState::TurnPackage);
	}
	else
	{
		UE_LOG(LogCustomExample, Error, TEXT("%s -- Package isn't valid!"), *FString(__FUNCTION__));
	}	
}

void ARoboManipulator::BeginPlay()
{
	Super::BeginPlay();
	
	UpperArmLength = GetSegmentLength(UpperArm);
	ForeArmLength = GetSegmentLength(ForeArm);
}

void ARoboManipulator::CreateRotatingMeshes(TMap<FString, URotatingMeshComponent**> MeshesWithName)
{
	if (MeshesWithName.Num() == 0)
	{
		UE_LOG(LogCustomExample, Warning, TEXT("%s -- Meshes are empty."), *FString(__FUNCTION__));
		return;
	}

	URotatingMeshComponent* PreviousMesh = nullptr;	
	for (TPair<FString, URotatingMeshComponent**> It_CurrentMesh : MeshesWithName)
	{
		URotatingMeshComponent* CurrentMesh = *It_CurrentMesh.Value;
		
		CurrentMesh = CreateDefaultSubobject<URotatingMeshComponent>(*It_CurrentMesh.Key);

		// attach hierarchically
		if (!PreviousMesh)
		{
			CurrentMesh->SetupAttachment(this->GetRootComponent());
		} 
		else
		{
			CurrentMesh->SetupAttachment(PreviousMesh);
		}		
		
		CurrentMesh->OnRotationFinished.BindUObject(this, &ARoboManipulator::MeshRotationFinished);

		PreviousMesh = CurrentMesh;
	}
}

void ARoboManipulator::MeshRotationFinished(const UObject* Mesh)
{	
	// BaseMesh has finished rotation
	if (Mesh == BaseMesh)
	{
		// BaseMesh was turned for grab
		if (ManipulatorState == EManipulatorState::TurnPackage)
		{
			StartGrabbing();
		}
		else if (ManipulatorState == EManipulatorState::TurnTarget) 
		{
			StartDropping();
		}
		else if (ManipulatorState == EManipulatorState::TurnIdle)
		{
			NextAction(Idle);
		}
		else if (ManipulatorState == EManipulatorState::TurnTarget)
		{
			check(false);
		}
		
		return;
	}

	// Segment has finished rotation
	if ((Mesh == UpperArm) || (Mesh == ForeArm))
	{
		// Next Stage, in case the all hand animations were completed
		if (bArmAnimFinished) 
		{			
			NextAction(EManipulatorState( (ManipulatorState + 1) % (TurnIdle + 1) ));
		}		
		
		bArmAnimFinished = !bArmAnimFinished;

		return;
	}
}

void ARoboManipulator::NextAction(const EManipulatorState NextState)
{
	ManipulatorState = NextState;
	
	switch (ManipulatorState)
	{
	case EManipulatorState::Idle:		
		GetWorldTimerManager().SetTimer(RepeatTimerHandle, this, &ARoboManipulator::RepeatPackageManipulation, 1.0f, false, 1.0f);
		break;
	
	case EManipulatorState::TurnPackage:				
		Turn(Package->GetActorLocation());
		break;

	case EManipulatorState::Grab:
		FinishGrabbing();		
		break;

	case EManipulatorState::TurnTarget:
		Turn(PackageTargetLocation);
		break;

	case EManipulatorState::Drop:
		FinishDropping();
		break;

	case EManipulatorState::TurnIdle:
		BaseMesh->Rotate(FRotator{});
		break;
	}
}

void ARoboManipulator::Turn(const FVector& TargetLocation, bool bShortDistance /*= true*/)
{
	FRotator TargetRotation = BaseMesh->GetRelativeRotation();
	TargetRotation.Yaw = CalculateTurnAngle(TargetLocation, bShortDistance);

	BaseMesh->Rotate(TargetRotation);
}

const float ARoboManipulator::CalculateTurnAngle(FVector TargetLocation, bool bShortDistance) const
{
	// Calculate angle through conversion from the Cartesian coordinates to the Polar coordinates
	float ResultAngle = UKismetMathLibrary::DegAtan2(TargetLocation.Y, TargetLocation.X) + 180.f;
	
	if (ResultAngle > 180.f && bShortDistance)
	{
		// Take in count the closest path
		ResultAngle = -(360.f - ResultAngle);
	}

	return ResultAngle;
}

void ARoboManipulator::StartGrabbing()
{
	float DistanceToObject = UKismetMathLibrary::Vector_Distance(UpperArm->GetComponentTransform().GetLocation(), Package->GetActorLocation());
	
	UpperArm->Rotate(CalculateSegmentRotation(DistanceToObject, true));
	ForeArm->Rotate(CalculateSegmentRotation(DistanceToObject, false));
}

void ARoboManipulator::FinishGrabbing()
{
	Package->AttachToComponent(ForeArm, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

	UpperArm->ReverseLastRotation();
	ForeArm->ReverseLastRotation();
}

void ARoboManipulator::StartDropping()
{
	float DistanceToObject = UKismetMathLibrary::Vector_Distance(UpperArm->GetComponentTransform().GetLocation(), PackageTargetLocation);
	
	UpperArm->Rotate(CalculateSegmentRotation(DistanceToObject, true));
	ForeArm->Rotate(CalculateSegmentRotation(DistanceToObject, false));
}

void ARoboManipulator::FinishDropping()
{
	Package->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

	UpperArm->ReverseLastRotation();
	ForeArm->ReverseLastRotation();
}

const FRotator ARoboManipulator::CalculateSegmentRotation(const float& DistanceToObject, bool bUpperArm) const
{
	FRotator CalculatedRotation;
	
	if (bUpperArm)
	{
		CalculatedRotation = UpperArm->GetRelativeRotation();
		// Solving SSS Triangles: cos(A) = (bb + cc − aa) / 2bc
		CalculatedRotation.Pitch = 90.f - UKismetMathLibrary::DegAcos(
			(FMath::Square(UpperArmLength) + FMath::Square(DistanceToObject) - FMath::Square(ForeArmLength)) / (2 * UpperArmLength * DistanceToObject));
	}
	// ForeArm
	else
	{	
		CalculatedRotation = ForeArm->GetRelativeRotation();
		// Solving SSS Triangles: cos(C) = (aa + bb − cc) / 2ab
		CalculatedRotation.Pitch = 180.f - UKismetMathLibrary::DegAcos(
			(FMath::Square(ForeArmLength) + FMath::Square(UpperArmLength) - FMath::Square(DistanceToObject)) / (2 * ForeArmLength * UpperArmLength));
	}

	return CalculatedRotation;
}

const float ARoboManipulator::GetSegmentLength(const UStaticMeshComponent* InMesh, bool bFromPivot /*= true*/) const
{
	if (!InMesh)
	{
		UE_LOG(LogCustomExample, Error, TEXT("%s -- InMesh isn't valid!"), *FString(__FUNCTION__));
		return 0.0f;
	}

	FVector MinBounds, MaxBounds;
	if (bFromPivot)
	{
		InMesh->GetLocalBounds(MinBounds, MaxBounds);
		return MaxBounds.Z;
	}
	// Calculate whole Segment Length
	else
	{
		return (InMesh->GetStaticMesh()->GetBoundingBox().GetSize().X);
	}
}

void ARoboManipulator::RepeatPackageManipulation()
{
	int32 RandomDistance = UKismetMathLibrary::RandomIntegerInRange(100, 150);
	FVector RandomLocation = UKismetMathLibrary::RandomUnitVector() * RandomDistance;
	Package->SetActorLocation(FVector(RandomLocation.X, RandomLocation.Y, Package->GetActorLocation().Z));

	NextAction(TurnPackage);
}
