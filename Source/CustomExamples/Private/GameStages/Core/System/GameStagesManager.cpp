// 6r0m, MIT liscence


#include "GameStages/Core/System/GameStagesManager.h"
#include "GameStages/Core/Templates/GameStage.h"
#include "GameStages/Placeables/InfoStand.h"

#include "EngineUtils.h"

void UGameStagesManager::PostInitProperties()
{
	Super::PostInitProperties();
	
	// Init Info Stand in the most universal way
	if (FApp::IsGame())
	{		
		UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{
			for (TActorIterator<AInfoStand> It(World, AInfoStand::StaticClass()); It; ++It)
			{
				InfoStand = *It;
				break;				
			}
		}
	}
}

void UGameStagesManager::NextStage()
{
	if (IdCurrentStage >= GameStages.Num())
	{
		UE_LOG(LogCustomExample, Display, TEXT("%s -- Game Stages are finished."), *FString(__FUNCTION__));
		return;
	}
	
	if (!GameStages.IsValidIndex(IdCurrentStage)) 
	{
		UE_LOG(LogCustomExample, Warning, TEXT("%s -- Game Stage with Current Id isn't Valid!"), *FString(__FUNCTION__));
		return;
	}
	
	UClass* CurrentStageClass = GameStages[IdCurrentStage];

	CurrentGameStage = NewObject<UGameStage>(this, CurrentStageClass);	
	CurrentGameStage->Activate(InfoStand);
	CurrentGameStage->OnStageFinished.BindUObject(this, &UGameStagesManager::StageFinished);
	
	IdCurrentStage++;
}

void UGameStagesManager::StageFinished()
{
	NextStage();
}
