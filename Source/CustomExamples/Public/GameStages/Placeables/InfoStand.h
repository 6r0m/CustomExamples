// 6r0m, MIT liscence

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UMG/Public/Blueprint/UserWidget.h"
#include "UMG/Public/Components/WidgetComponent.h"
#include "Internationalization/Text.h"

#include "InfoStand.generated.h"

/**
 * Base class for derived Info Stand in the blueprints for convenient widget setup.
 */

UCLASS(Abstract)
class CUSTOMEXAMPLES_API AInfoStand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInfoStand();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameStages|Info Stand")
	void SetTextSize(const uint8& TextSize);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameStages|Info Stand")
	void SetInfo(const FText& Info);
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameStages|Info Stand")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "GameStages|Info Stand")
	FText DefaultWidgetText = FText::FromString("Default Widget Text");

	UPROPERTY(EditDefaultsOnly, Category = "GameStages|Info Stand")
	uint8 WidgetTextSize = 52;
	
private:
	void Init();
};
