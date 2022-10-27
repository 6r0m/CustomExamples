// 6r0m, MIT liscence

#include "Manipulator/Core/Templates/RoboManipulator.h"
#include "Manipulator/Core/Templates/RotatingMesh.h"

#define GetMeshWithName(name) #name, name

ARoboManipulator::ARoboManipulator()
{
 	PrimaryActorTick.bCanEverTick = false;

	CreateRotatingMeshes({{ GetMeshWithName(BaseMesh) }, { GetMeshWithName(UpperArm) }, { GetMeshWithName(ForeArm) }});
}

void ARoboManipulator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoboManipulator::CreateRotatingMeshes(TMap<FString, URotatingMesh*> MeshesWithName)
{
	if (MeshesWithName.Num() == 0)
	{
		UE_LOG(LogCustomExample, Warning, TEXT("%s -- Meshes are empty."), *FString(__FUNCTION__));
		return;
	}

	URotatingMesh* PreviousMesh = nullptr;
	for (TPair<FString, URotatingMesh*>& CurrentMesh : MeshesWithName)
	{
		CurrentMesh.Value = CreateDefaultSubobject<URotatingMesh>(*CurrentMesh.Key);
		
		if (!PreviousMesh)
		{
			CurrentMesh.Value->SetupAttachment(this->GetRootComponent());			
		} 
		else
		{
			CurrentMesh.Value->SetupAttachment(PreviousMesh);
		}		
		PreviousMesh = CurrentMesh.Value;
	}
}

