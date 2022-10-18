// 6r0m, MIT liscence


#include "GameStages/Placeables/InfoStand.h"

// Sets default values
AInfoStand::AInfoStand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AInfoStand::BeginPlay()
{
	Super::BeginPlay();
	
	Init();
}

void AInfoStand::Init()
{
	InfoWidget = WidgetComponent->GetUserWidgetObject();
	if (!InfoWidget)
	{
		UE_LOG(LogCustomExample, Error, TEXT("%s -- Widget isn't Valid!"), *FString(__FUNCTION__));
		return;
	}	

	SetTextSize(WidgetTextSize);
	SetInfo(DefaultWidgetText);
}

