// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoboManipulator.generated.h"

class URotatingMeshComponent;

// test
class UStaticMesh;

UCLASS(Blueprintable)
class CUSTOMEXAMPLES_API ARoboManipulator : public AActor
{
	GENERATED_BODY()
	
public:		
	ARoboManipulator();

	UPROPERTY(EditAnywhere, Category = "Manipulator")
	URotatingMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere, Category = "Manipulator")
	URotatingMeshComponent* UpperArm;

	UPROPERTY(EditAnywhere, Category = "Manipulator")
	URotatingMeshComponent* ForeArm;

	// test
	UPROPERTY(EditAnywhere, Category = "Manipulator")
	URotatingMeshComponent* TestMesh;

protected:
	virtual void BeginPlay() override;

private:
	
	// modify the variables itself instead of the object
	void CreateRotatingMeshes(TMap<FString, URotatingMeshComponent**> MeshesWithName);
};
