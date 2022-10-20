// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameStages/Core/Templates/GameStage.h"

#include "DemoGameStage.generated.h"

/**
 * Stage for example. It uses time for its lifetime maintenance.
 */
UCLASS(Blueprintable)
class CUSTOMEXAMPLES_API UDemoGameStage : public UGameStage
{
	GENERATED_BODY()
	
protected:	
	virtual void StageBeginPlay_Implementation() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameStages|Stage")
	float AutoFinishTime = 0.f;

private:
	void AutoFinish();
};
