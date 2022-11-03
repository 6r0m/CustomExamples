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
	void Rotate(const FRotator& InTargetRotation);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manipulator|RotatingMesh")
	float AnimRate = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "Manipulator|RotatingMesh")
	void ReverseLastRotation();

	FOnRotationFinished OnRotationFinished;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manipulator|RotatingMesh", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* AnimCurve;
	
	void InitConstruction();
	void InitTimeline();
	FTimeline Timeline;

	UFUNCTION()
	void Rotating(const float Value);

	FRotator InitialRotation;
	FRotator TargetRotation;
	void RotatingFinished();	
};
