// 6r0m, MIT liscence


#include "GameStages/Core/Templates/GameStage.h"
#include "GameStages/Core/System/StageActorInterface.h"

#include "EngineUtils.h"

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

	StageWorld = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);

	UE_LOG(LogCustomExample, Display, TEXT("%s -- Stage Actor : %s"), *FString(__FUNCTION__), *FString(GetStageActor()->GetName()));
}

const AActor* UGameStage::GetStageActor()
{
	if (StageActor)
	{
		return StageActor;
	}

	// find the target actor by provided tag and class in blueprint's defaults
	if (StageActorClass && StageWorld)
	{
		for (TActorIterator<AActor> It(StageWorld, StageActorClass); It; ++It)
		{
			AActor* Actor = *It;
			
			bool bActorIsValid = Actor && !Actor->IsPendingKill();
			bool bStageActor = Actor->ActorHasTag(StageActorTag) && StageActorClass->ImplementsInterface(UStageActorInterface::StaticClass());
			if (bActorIsValid && bStageActor)
			{
				StageActor = Actor;
				return StageActor;
			}
		}
	}

	return nullptr;
}
