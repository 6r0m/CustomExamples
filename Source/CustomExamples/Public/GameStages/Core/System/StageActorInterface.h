// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/EngineTypes.h"

#include "StageActorInterface.generated.h"

UINTERFACE(Category = "GameStages", BlueprintType, meta = (DisplayName = "Stage Actor Interface"))
class UStageActorInterface : public UInterface
{
	GENERATED_BODY()
};

class CUSTOMEXAMPLES_API IStageActorInterface
{
	GENERATED_BODY()

public:		
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GameStages")
	void Activate();
};

