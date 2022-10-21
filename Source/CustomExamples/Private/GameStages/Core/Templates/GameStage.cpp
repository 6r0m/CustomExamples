// 6r0m, MIT liscence


#include "GameStages/Core/Templates/GameStage.h"
#include "GameStages/Placeables/InfoStand.h"
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

void UGameStage::Activate()
{
	// Activate Stage Actor
	if (GetStageActor() && StageActor->GetClass()->ImplementsInterface(UStageActorInterface::StaticClass()))
	{
		IStageActorInterface::Execute_Activate(StageActor, this);
	}
	
	// Show Marker
		// here could be some spawn fx realization on stage actor position with self-destroy on pawn overlap
}

void UGameStage::Activate(AInfoStand* InfoStand)
{
	Activate();

	// Show Hint
	if (InfoStand && !StageHint.IsEmpty()) 
	{		
		InfoStand->SetInfo(StageHint);
	}
}

void UGameStage::RequestFinishStage()
{
	FinishStage();
}

void UGameStage::StageBeginPlay_Implementation()
{	
	StageWorld = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
}

void UGameStage::FinishStage()
{
	OnStageFinished.ExecuteIfBound();

	// if the stage no needed anymore - to force GC use ConditionalBeginDestroy() on this
}

const AActor* UGameStage::GetStageActor()
{
	if (StageActor)
	{
		return StageActor;
	}

	// Find the target actor by provided tag and class in blueprint's defaults
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

void UGameStage::ShowHint()
{
	//StageHint.IsEmpty();
}
