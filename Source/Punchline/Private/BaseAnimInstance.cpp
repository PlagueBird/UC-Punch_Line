// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"

void UBaseAnimInstance::NotifyToPunch_Implementation()
{
	if (PunchMontage && !IsPunching )
	{
		UE_LOG(LogTemp, Warning, TEXT("Playing punch montage"));
		IsPunching = true;

		float MontageDuration = PunchMontage->GetPlayLength();

		GetWorld()->GetTimerManager().SetTimer(PunchTimerHandle, this, &UBaseAnimInstance::NotifyToEndPunch, MontageDuration, false);
	
	}
}

void UBaseAnimInstance::NotifyToKick_Implementation()
{
	if (PunchMontage && !IsPunching) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Playing punch montage"));
		IsPunching = true;

		float MontageDuration = PunchMontage->GetPlayLength();

		GetWorld()->GetTimerManager().SetTimer(KickTimerHandle, this, &UBaseAnimInstance::NotifyToEndKick, MontageDuration, false);

	}
}

void UBaseAnimInstance::NotifyToEndKick_Implementation()
{
}

void UBaseAnimInstance::NotifyToEndPunch_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End punch montage"));
	IsPunching = false;
	PunchTimerHandle.Invalidate();
}
