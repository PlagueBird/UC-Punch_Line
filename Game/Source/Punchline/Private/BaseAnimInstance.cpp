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
		UE_LOG(LogTemp, Warning, TEXT("Playing kick montage"));
		IsKicking = true;
		float MontageDuration = KickMontage->GetPlayLength();
		GetWorld()->GetTimerManager().SetTimer(KickTimerHandle, this, &UBaseAnimInstance::NotifyToEndKick, MontageDuration, false);
	}
}

void UBaseAnimInstance::NotifyToEndKick_Implementation()
{
	IsKicking = false;
	UE_LOG(LogTemp, Warning, TEXT("End kick montage"));
	KickTimerHandle.Invalidate();
}

void UBaseAnimInstance::NotifyToEndPunch_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End punch montage"));
	IsPunching = false;
	PunchTimerHandle.Invalidate();
}

void UBaseAnimInstance::NotifyToDie_Implementation()
{
	IsDead = true;
}

void UBaseAnimInstance::NotifyToReset_Implementation()
{
	IsDead = false;
	IsPunching = false;
	IsKicking = false;
	IsBlocking = false;
}