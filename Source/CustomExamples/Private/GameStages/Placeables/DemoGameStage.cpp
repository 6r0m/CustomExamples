// 6r0m, MIT liscence

#include "GameStages/Placeables/DemoGameStage.h"

#include "GameFramework/Actor.h"

void UDemoGameStage::StageBeginPlay_Implementation()
{
	// set timer for auto finishing
	if (AutoFinishTime != 0 && GEngine) 
	{
		FTimerHandle TimerHandle;		
		if (UWorld* World = GEngine->GetWorldFromContextObject(this))
		{
			World->GetTimerManager().SetTimer(TimerHandle, this, &UDemoGameStage::AutoFinish, AutoFinishTime);
		}		
	}
}

void UDemoGameStage::AutoFinish()
{
	FinishStage();
}
