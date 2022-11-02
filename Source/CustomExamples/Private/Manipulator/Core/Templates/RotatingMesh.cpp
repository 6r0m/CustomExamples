// 6r0m, MIT liscence


#include "Manipulator/Core/Templates/RotatingMesh.h"


URotatingMeshComponent::URotatingMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InitConstruction();
}

void URotatingMeshComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void URotatingMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Timeline.TickTimeline(DeltaTime);
}

void URotatingMeshComponent::InitConstruction()
{
	InitTimeline();
}

void URotatingMeshComponent::InitTimeline()
{	
	// Set the anim curve by default (just for example). actually do it by an inherited bp
	FString CurveDir = "/CustomExamples/Manipulator/Resources/Objects/RoboParts/Curve_Robo.Curve_Robo";
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(*CurveDir);
	if (Curve.Succeeded())
	{
		AnimCurve = Curve.Object;
	}
	
	Timeline.SetPlayRate(AnimRate);

	FOnTimelineFloat UpdatingFunction{};
	UpdatingFunction.BindUFunction(this, "Rotating");
	Timeline.AddInterpFloat(AnimCurve, UpdatingFunction, FName{ TEXT("Curve_Robo") });
	
	FOnTimelineEventStatic OnTimelineFinished{};
	OnTimelineFinished.BindUObject(this, &URotatingMeshComponent::RotatingFinished);
	Timeline.SetTimelineFinishedFunc(OnTimelineFinished);
}

void URotatingMeshComponent::Rotate(const FRotator& InTargetRotation, bool bFromStart /*= true*/)
{
	InitialRotation = GetRelativeRotation();
	TargetRotation = InTargetRotation;

	if (bFromStart)
	{
		Timeline.PlayFromStart();
	} 
	else
	{
		Timeline.ReverseFromEnd();
	}	
}

void URotatingMeshComponent::Rotating(const float Value)
{
	FRotator NewRotation = FMath::Lerp(InitialRotation, TargetRotation, Value);
	SetRelativeRotation(NewRotation);
}

void URotatingMeshComponent::RotatingFinished()
{
	OnRotationFinished.ExecuteIfBound(this);
}
