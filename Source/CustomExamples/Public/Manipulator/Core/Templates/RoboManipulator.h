// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoboManipulator.generated.h"

class URotatingMeshComponent;

UCLASS(Blueprintable)
class CUSTOMEXAMPLES_API ARoboManipulator : public AActor
{
	GENERATED_BODY()
	
public:		
	ARoboManipulator();

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
};
