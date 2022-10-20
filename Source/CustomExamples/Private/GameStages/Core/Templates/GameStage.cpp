// 6r0m, MIT liscence


#include "GameStages/Core/Templates/GameStage.h"

void UGameStage::PostInitProperties()
{
	Super::PostInitProperties();

	if (FApp::IsGame())
	{
		StageBeginPlay();
	}
}	

void UGameStage::FinishStage()
{
	OnStageFinished.ExecuteIfBound();

	// if this stage no needed anymore - to force GC use ConditionalBeginDestroy() on this
}

void UGameStage::StageBeginPlay_Implementation()
{
	// reserved for a base cpp Stage Logic that can be ovverriden in derived classes
	UE_LOG(LogCustomExample, Display, TEXT("%s -- Stage Begin Play"), *FString(__FUNCTION__));
}
