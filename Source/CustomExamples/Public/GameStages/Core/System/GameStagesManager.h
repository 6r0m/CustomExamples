// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameStages/Core/Templates/GameStage.h"

#include "GameStagesManager.generated.h"

/**
 * Manager controls game stages.
 */
UCLASS()
class UGameStagesManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "GameStages")
	void NextStage();

private:
	uint8 IdCurrentStage = 0;

	TSubclassOf<UGameStage> GameStages;
};
