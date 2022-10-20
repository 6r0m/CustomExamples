// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStage.generated.h"

DECLARE_DELEGATE(FOnStageFinished_Signature);

/**
 * Base class for derived game stages.
 */
UCLASS(Abstract, Blueprintable)
class UGameStage : public UObject
{
	GENERATED_BODY()
	
public:	
	virtual void PostInitProperties() override;

	FOnStageFinished_Signature OnStageFinished;

protected:
	UFUNCTION(BlueprintCallable, Category = "GameStages|Stage", meta = (BlueprintProtected = "true"))
	void FinishStage();	

	UFUNCTION(BlueprintNativeEvent, Category = "GameStages|Stage", meta = (BlueprintProtected = "true"))
	void StageBeginPlay();
	virtual void StageBeginPlay_Implementation();
};
