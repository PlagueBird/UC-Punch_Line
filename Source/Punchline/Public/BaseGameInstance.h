// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"


UENUM(BlueprintType)
enum class EGameModeType : uint8 {
	E_Versus		UMETA(DisplayName = "VERSUS"),
	E_Online		UMETA(DisplayName = "ONLINE")
};

UENUM(BlueprintType)
enum class ECharacterClass : uint8 {
	VE_Default	UMETA(DisplayName = "Temp_Name"),
	VE_PIETRO	UMETA(DisplayName = "Pietro")
	//More characters added here
};

/**
 * 
 */
UCLASS()
class PUNCHLINE_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//UBaseGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamemode Reference")
	EGameModeType gameModeType;

	UFUNCTION(BlueprintCallable)
	void HostSession();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	ECharacterClass characterClass;
	
};
