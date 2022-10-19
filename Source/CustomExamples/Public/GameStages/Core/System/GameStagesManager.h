// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameStages/Core/Templates/GameStage.h"

#include "GameStagesManager.generated.h"

/**
 * Manager controls game stages.
 */
UCLASS(Abstract, Blueprintable)
class UGameStagesManager : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "GameStages")
	void NextStage();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameStages")
	TArray<TSubclassOf<UGameStage>> GameStages;

private:
	
	void StageFinished();

	uint8 IdCurrentStage = 0;

	UPROPERTY()
	UGameStage* CurrentGameStage;
};
