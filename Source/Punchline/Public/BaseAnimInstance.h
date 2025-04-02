// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUNCHLINE_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Animation")
	void PlayPunchAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PunchMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsPunching = false;

};
