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
	if (ManipulatorState != EManipulatorState::Idle)
	{
		// Manipulating in progress
		return;
	}

	if (Package)
	{
		Turn(Package->GetActorLocation());
	}
	else
	{
		UE_LOG(LogCustomExample, Error, TEXT("%s -- Package isn't valid!"), *FString(__FUNCTION__));
	}	
}

void ARoboManipulator::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (Mesh == BaseMesh)
	{

		return;
	}

	if ((Mesh == UpperArm) || (Mesh == ForeArm))
	{
		// Next Stage, in case the all hand animations were completed
		if (bArmAnimFinished) 
		{
			
		}		
		
		bArmAnimFinished = !bArmAnimFinished;

		return;
	}
}

void ARoboManipulator::Turn(const FVector& TargetLocation)
{
	ManipulatorState = EManipulatorState::Turn;
	
	FRotator TargetRotation = BaseMesh->GetRelativeRotation();
	TargetRotation.Yaw = CalculateTurnAngle(TargetLocation);

	BaseMesh->Rotate(TargetRotation);
}

const float ARoboManipulator::CalculateTurnAngle(FVector TargetLocation)
{
	// Calculate angle through conversion from the Cartesian coordinates to the Polar coordinates
	float ResultAngle = UKismetMathLibrary::DegAtan2(TargetLocation.Y, TargetLocation.X) + 180.f;
	
	if (ResultAngle > 180.f)
	{
		// Take in count the closest path
		ResultAngle = -(360.f - ResultAngle);
	}

	return ResultAngle;
}
