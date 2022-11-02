// 6r0m, MIT liscence

#pragma once

#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "RotatingMesh.generated.h"

//DECLARE_DELEGATE(FOnRotationFinished);
DECLARE_DELEGATE_OneParam(FOnRotationFinished, const UObject*);

/** Mesh component with rotation animation. */
UCLASS(Blueprintable)
class CUSTOMEXAMPLES_API URotatingMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	URotatingMeshComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
	
	UFUNCTION(BlueprintCallable, Category = "Manipulator|RotatingMesh")
	void Rotate(const FRotator& InTargetRotation, bool bFromStart = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manipulator|RotatingMesh")
	float AnimRate = 1.0;

	FOnRotationFinished OnRotationFinished;

private:
	void InitConstruction();
	void InitTimeline();

	UFUNCTION()
	void Rotating(const float Value);
	void RotatingFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manipulator|RotatingMesh", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* AnimCurve;

	FTimeline Timeline; 

	FRotator InitialRotation;
	FRotator TargetRotation;
};
