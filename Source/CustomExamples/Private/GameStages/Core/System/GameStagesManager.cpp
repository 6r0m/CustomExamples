// 6r0m, MIT liscence


#include "GameStages/Core/System/GameStagesManager.h"

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
	CurrentGameStage->OnStageFinished.BindUObject(this, &UGameStagesManager::StageFinished);
	
	IdCurrentStage++;
}

void UGameStagesManager::StageFinished()
{
	NextStage();
}
