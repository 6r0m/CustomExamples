// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoboManipulator.generated.h"

enum EManipulatorState
{	
	Idle = 0,
	Grab = 1,
	Turn = 2,
	Drop = 3,
};

class URotatingMeshComponent;

UCLASS(Blueprintable)
class CUSTOMEXAMPLES_API ARoboManipulator : public AActor
{
	GENERATED_BODY()
	
public:		
	ARoboManipulator();

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

protected:
	virtual void BeginPlay() override;

private:
	
	// Mesh components creation with modifying the variables itself instead of the objects
	void CreateRotatingMeshes(TMap<FString, URotatingMeshComponent**> MeshesWithName);
	void MeshRotationFinished(const UObject* Mesh);

	void Turn(const FVector& TargetLocation);
	const float CalculateTurnAngle(FVector TargetLocation);
		
	//void Drop();
	//void Idle();

	EManipulatorState ManipulatorState = EManipulatorState::Idle;

	// Choose package in the derived BP from scene
	UPROPERTY(EditAnywhere, Category = "Robo Manipulator")
	AActor* Package;	
	
	bool bPackageHandled = false;
	bool bArmAnimFinished = false;
};
