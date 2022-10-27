// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoboManipulator.generated.h"

class URotatingMesh;

UCLASS()
class CUSTOMEXAMPLES_API ARoboManipulator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoboManipulator();

	UPROPERTY(EditDefaultsOnly, Category = "Manipulator")
	URotatingMesh* BaseMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Manipulator")
	URotatingMesh* UpperArm;

	UPROPERTY(EditDefaultsOnly, Category = "Manipulator")
	URotatingMesh* ForeArm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void CreateRotatingMeshes(TMap<FString, URotatingMesh*> MeshesWithName);


};
