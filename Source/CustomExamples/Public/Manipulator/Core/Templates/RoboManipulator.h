// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoboManipulator.generated.h"

enum EManipulatorState
{	
	Idle = 0,
	TurnPackage = 1,	
	Grab = 2,	
	TurnTarget = 3,
	Drop = 4,
	TurnIdle = 5,
};

class URotatingMeshComponent;

UCLASS(Blueprintable)
class CUSTOMEXAMPLES_API ARoboManipulator : public AActor
{
	GENERATED_BODY()
	
public:		
	ARoboManipulator();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Manipulator")
	void ManipulatePackage();

	UPROPERTY(EditAnywhere, Category = "Manipulator")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Manipulator")
	URotatingMeshComponent* BaseMesh;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Manipulator")
	URotatingMeshComponent* UpperArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Manipulator")
	URotatingMeshComponent* ForeArm;

private:
	// Choose package in the derived BP from scene
	UPROPERTY(EditAnywhere, Category = "Manipulator")
	AActor* Package;
	// Choose target location of the package in the derived BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manipulator", meta = (MakeEditWidget, AllowPrivateAccess = "true"))
	FVector PackageTargetLocation;

	// Mesh components creation with modifying the variables itself instead of the objects
	void CreateRotatingMeshes(TMap<FString, URotatingMeshComponent**> MeshesWithName);
	
	void MeshRotationFinished(const UObject* Mesh);
	bool bArmAnimFinished = false;

	void NextAction(const EManipulatorState NextState);
	EManipulatorState ManipulatorState = EManipulatorState::Idle;

	void Turn(const FVector& TargetLocation, bool bShortDistance = true);
	const float CalculateTurnAngle(FVector TargetLocation, bool bShortDistance) const;
	
	void StartGrabbing();
	void FinishGrabbing();
	void StartDropping();
	void FinishDropping();

	const FRotator CalculateSegmentRotation(const float& DistanceToObject, bool bUpperArm) const;
	float UpperArmLength, ForeArmLength;
	const float GetSegmentLength(const UStaticMeshComponent* InMesh, bool bFromPivot = true) const;

	void RepeatPackageManipulation();	
	FTimerHandle RepeatTimerHandle;
};
