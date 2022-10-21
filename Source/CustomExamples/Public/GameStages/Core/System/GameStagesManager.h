// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameStagesManager.generated.h"

class UGameStage;
class AInfoStand;

/**
 * Manager controls game stages.
 */
UCLASS(Abstract, Blueprintable)
class UGameStagesManager : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintCallable, Category = "GameStages")
	void NextStage();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameStages")
	TArray<TSubclassOf<UGameStage>> GameStages;

private:
	
	void StageFinished();

	uint8 IdCurrentStage = 0;
	
	AInfoStand* InfoStand;

	UPROPERTY()
	UGameStage* CurrentGameStage;
};
