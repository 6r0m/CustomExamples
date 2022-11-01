// 6r0m, MIT liscence

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
	for (TPair<FString, URotatingMeshComponent**> CurrentMesh : MeshesWithName)
	{
		*CurrentMesh.Value = CreateDefaultSubobject<URotatingMeshComponent>(*CurrentMesh.Key);

		// attach hierarchically
		if (!PreviousMesh)
		{
			(*CurrentMesh.Value)->SetupAttachment(this->GetRootComponent());						
		} 
		else
		{
			(*CurrentMesh.Value)->SetupAttachment(PreviousMesh);
		}		
		
		PreviousMesh = *CurrentMesh.Value;
	}
}

