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
	void NotifyToPunch();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Animation")
	void NotifyToEndPunch();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Animation")
	void NotifyToKick();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Animation")
	void NotifyToEndKick();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Animation")
	void NotifyToDie();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Animation")
	void NotifyToReset();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* PunchMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* KickMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsPunching = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsKicking = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsBlocking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool IsDead = false;

private:
	FTimerHandle PunchTimerHandle;

	FTimerHandle KickTimerHandle;

	FTimerHandle BlockTimerHandle;
};
