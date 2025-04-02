// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstance.h"

void UBaseAnimInstance::PlayPunchAnimation_Implementation()
{
	if (PunchMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Playing punch montage"));
		IsPunching = true;

		/*float MontageDuration = PunchMontage->GetPlayLength();

		GetWorld()->GetTimerManager().SetTimer(PunchTimerHandle, this, &UBaseAnimInstance::StopPunchAnimation, MontageDuration, false);
	}*/
	}
}