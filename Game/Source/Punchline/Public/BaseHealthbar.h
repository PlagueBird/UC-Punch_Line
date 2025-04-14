// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <AFighterBase.h>
#include "BaseHealthbar.generated.h"


/**
 * 
 */
UCLASS()
class PUNCHLINE_API UBaseHealthbar : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetPlayerHealth(int PlayerIndex, float Percent);

protected:
    // Bind these in the Widget Blueprint (UMG)
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* P1_HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* P2_HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
    AAFighterBase* plat1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AAFighterBase* plat2;

	
};
