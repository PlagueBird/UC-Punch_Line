// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHealthbar.h"

#include "Components/ProgressBar.h"

void UBaseHealthbar::SetPlayerHealth(int PlayerIndex, float Percent)
{
	if (PlayerIndex == 1 && P1_HealthBar)
	{
		P1_HealthBar->SetPercent(Percent);
	}
	else if (PlayerIndex == 2 && P2_HealthBar)
	{
		P2_HealthBar->SetPercent(Percent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Player Index or Health Bar not found"));
	}
   
}
