#include "BaseFighterGameMode.h"
#include "Punchline/Public/AFighterBase.h"
#include "GameFramework/PlayerStart.h"
#include <Kismet/GameplayStatics.h>

ABaseFighterGameMode::ABaseFighterGameMode()
{
PrimaryActorTick.bCanEverTick = true;
}

void ABaseFighterGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	//FindPlayerStarts();

	InitCameraManager();

	if (FightingUIClass)
	{
		FightingUIWidget = CreateWidget<UBaseHealthbar>(GetWorld(), FightingUIClass);


		if (FightingUIWidget)
		{
			FightingUIWidget->AddToViewport();
		}
	}
}

void ABaseFighterGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!Players.Contains(NewPlayer))
	{
		Players.Add(NewPlayer);
		PlayerWins.Add(NewPlayer, 0);
		
	}
	
	SpawnPlayers();
	//StartRound();
}

void ABaseFighterGameMode::SpawnPlayers()
{
	if (!FighterBlueprintClass) return;  // Ensure Blueprint class is assigned

	if (PlayerStarts.Num() < 2)
	{
		FindPlayerStarts();

		if (PlayerStarts.Num() < 2)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not enough PlayerStarts to spawn players!"));
			return;
		}
	}

	// Get Player 1's controller (assumes at least one player is connected)
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogTemp, Warning, TEXT("Starting Spawned Players"));
	if (!PlayerController) return;

	// --- Spawn Player 1 (Human) ---
	FVector P1SpawnLocation = PlayerStarts[0]->GetActorLocation();
	FRotator P1SpawnRotation = FRotator(0, 90.f, 0);

	AAFighterBase* PlayerCharacter = GetWorld()->SpawnActor<AAFighterBase>(
		FighterBlueprintClass,
		P1SpawnLocation,
		P1SpawnRotation
	);

	if (PlayerCharacter)
	{
		PlayerController->Possess(PlayerCharacter);
		UE_LOG(LogTemp, Warning, TEXT("Spawned Player 1 at %s"), *P1SpawnLocation.ToString());
		PlayerCharacter->SetPlayerIndex(1);  // Set Player Index
	}

	// --- Spawn Player 2 (Dummy) ---
	FVector P2SpawnLocation = PlayerStarts[1]->GetActorLocation();
	FRotator P2SpawnRotation = FRotator(0, -90.f, 0);

	// Option 1: Static Dummy (No AI)
	AAFighterBase* DummyCharacter = GetWorld()->SpawnActor<AAFighterBase>(
		FighterBlueprintClass,
		P2SpawnLocation,
		P2SpawnRotation
	);

	if (DummyCharacter)
	{
		//DummyCharacter->SetActorTickEnabled(false);  // Make it non-responsive
		UE_LOG(LogTemp, Warning, TEXT("Spawned Dummy Character at %s"), *P2SpawnLocation.ToString());
		DummyCharacter->SetPlayerIndex(2);  // Set Player Index
	}
}

void ABaseFighterGameMode::InitCameraManager()
{
m_CameraManager = GetWorld()->SpawnActor<AFightingCameraManager>();
}

void ABaseFighterGameMode::FindPlayerStarts()
{
	PlayerStarts.Empty();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(Actor);
		if (PlayerStart)
		{
			PlayerStarts.Add(PlayerStart); // Store PlayerStart references
			UE_LOG(LogTemp, Warning, TEXT("Player Start: %s"), *PlayerStart->GetName());
		}
	}

	if (PlayerStarts.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Starts found!"));
	}
}

void ABaseFighterGameMode::ResetPlayers()
{
	for (int32 i = 0; i < Players.Num(); i++)
	{
		ACharacter* Character = Cast<ACharacter>(Players[i]->GetPawn());
		if (Character)
		{
			Character->SetActorLocation(PlayerStarts[i]->GetActorLocation());
			Character->SetActorRotation(FRotator(0, (i == 0) ? 90.f : -90.f, 0));
		}
	}
}

void ABaseFighterGameMode::UpdateHealthbars(int PlayerIndex, float Percent)
{
	if (FightingUIWidget)
	{
		FightingUIWidget->SetPlayerHealth(PlayerIndex, Percent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FightingUIWidget is not initialized!"));
	}
}