// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameStage.generated.h"

DECLARE_DELEGATE(FOnStageFinished_Signature);

class AInfoStand;

/**
 * Base class for derived game stages.
 */

UCLASS(Abstract, Blueprintable)
class UGameStage : public UObject
{
	GENERATED_BODY()

public:	
	virtual void PostInitProperties() override;

	virtual void Activate();

	virtual void Activate(AInfoStand* InfoStand);

	UFUNCTION(BlueprintCallable, Category = "GameStages|Stage")
	void RequestFinishStage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStages|Stage")
	FText StageHint;

	FOnStageFinished_Signature OnStageFinished;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "GameStages|Stage", meta = (BlueprintProtected = "true"))
	void StageBeginPlay();
	virtual void StageBeginPlay_Implementation();
	
	virtual void FinishStage();

	const virtual AActor* GetStageActor();

	virtual void ShowHint();

	UWorld* StageWorld;

	UPROPERTY(EditDefaultsOnly, Category = "GameStages|Stage", meta = (BlueprintProtected = "true"))
	TSubclassOf<AActor> StageActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameStages|Stage", meta = (BlueprintProtected = "true"))
	FName StageActorTag;

private:
	// Target Actor is the main actor (with the StageActorInterface) on whose state this stage depends.
	// Review BP_StageActor example for more.
	AActor* StageActor;
};
