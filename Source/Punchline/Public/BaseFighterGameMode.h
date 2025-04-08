// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include <FightingCameraManager.h>
#include <AFighterBase.h>
#include <Animation/UMGSequencePlayer.h>
#include <BaseHealthbar.h>
#include "BaseFighterGameMode.generated.h"




/**
 * 
 */
UCLASS()
class PUNCHLINE_API ABaseFighterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABaseFighterGameMode();

	
	//virtual AActor* ChosePlayerStart(AController* Player) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void ResetPlayers();

	void UpdateHealthbars(int PlayerIndex, float Percent);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	AFightingCameraManager* m_CameraManager;

	void InitCameraManager();
	void FindPlayerStarts();
	void SpawnPlayers();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AAFighterBase> FighterBlueprintClass;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UUserWidget> Healthbar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBaseHealthbar> FightingUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBaseHealthbar* FightingUIWidget;

private: 
	TArray<APlayerController*> Players;
	TArray<APlayerStart*> PlayerStarts;
	int32 CurrentRound = 1;
	int32 MaxRounds = 3;
	TMap<APlayerController*, int32> PlayerWins;
};
