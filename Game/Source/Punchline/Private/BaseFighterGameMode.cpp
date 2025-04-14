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
	UWorld* WorldContext = GetWorld();

	if (!WorldContext) return;

	// Loop through all PlayerControllers
	for (FConstPlayerControllerIterator Iterator = WorldContext->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Iterator->Get();
		if (PC)
		{
			int32 ControllerId = UGameplayStatics::GetPlayerControllerID(PC);
			UE_LOG(LogTemp, Warning, TEXT("Found PlayerController: %s | ID: %d"), *PC->GetName(), ControllerId);
		}
	}
	

	UE_LOG(LogTemp, Warning, TEXT("Game Mode Begin Play"));
	UGameplayStatics::CreatePlayer(GetWorld(), 1, true);

	if (FightingUIClass)
	{
		FightingUIWidget = CreateWidget<UBaseHealthbar>(GetWorld(), FightingUIClass);


		if (FightingUIWidget)
		{
			FightingUIWidget->AddToViewport();
		}
	}
	
	
	SpawnPlayers();
	InitCameraManager();
	StartRound();
}

void ABaseFighterGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Player logged in: %s"), *NewPlayer->GetName());
	if (!Players.Contains(NewPlayer))
	{
		Players.Add(NewPlayer);
		PlayerWins.Add(NewPlayer, 0);

	}
	
}

void ABaseFighterGameMode::SpawnPlayers()
{
	if (HasSpawnedPlayers)
	{
		return;
	}


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

	APlayerController* Player2Controller = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	

	if (!PlayerController) return;

	// --- Spawn Player 1 (Human) ---
	FVector P1SpawnLocation = PlayerStarts[0]->GetActorLocation();
	FRotator P1SpawnRotation = FRotator(0, 180, 0);

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
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Character not possessed"))
	}

	// --- Spawn Player 2 (Dummy) ---
	FVector P2SpawnLocation = PlayerStarts[1]->GetActorLocation();
	FRotator P2SpawnRotation = FRotator(0, 0, 0);

	// Option 1: Static Dummy (No AI)
	AAFighterBase* DummyCharacter = GetWorld()->SpawnActor<AAFighterBase>(
		FighterBlueprintClass,
		P2SpawnLocation,
		P2SpawnRotation
	);

	if (DummyCharacter)
	{
		if (Player2Controller)
		{
			
			Player2Controller->Possess(DummyCharacter);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Player 2 Controller not found!"));
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Spawned Dummy Character at %s"), *P2SpawnLocation.ToString());
		DummyCharacter->SetPlayerIndex(2);  // Set Player Index
	}

	DummyCharacter->OtherPlayer = PlayerCharacter;
	PlayerCharacter->OtherPlayer = DummyCharacter;
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
			//UE_LOG(LogTemp, Warning, TEXT("Player Start: %s"), *PlayerStart->GetName());
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

	//UE_LOG(LogTemp, Warning, TEXT("Percent: " + ToText(Percent), Percent);
	if (Percent == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseFighterGameMode::EndRound, 3.0f, false);
		
	}
}

void ABaseFighterGameMode::StartRound()
{
	// Reset players to their starting positions
	UE_LOG(LogTemp, Warning, TEXT("Round %d"), CurRound);
	ResetPlayers();
	// Reset health
	int test = 0;
	for (APlayerController* Player : Players)
	{
		
		AAFighterBase* Fighter = Cast<AAFighterBase>(Player->GetPawn());
		if (Fighter)
		{
			UE_LOG(LogTemp, Warning, TEXT("RESETING HEALTH: %d"), test)
			Fighter->ResetHealth();
			UpdateHealthbars(Fighter->GetPlayerIndex(), Fighter->Health / Fighter->MaxHealth);
		}
		test++;
	}
	IsMatchOver = false;
}

void ABaseFighterGameMode::EndRound()
{
	for (APlayerController* Player : Players)
	{
		AAFighterBase* Fighter = Cast<AAFighterBase>(Player->GetPawn());
		if (Fighter)
		{
			if (Fighter->Health <= 0)
			{
				if (Fighter->GetPlayerIndex() == 1)
				{
					Player1Wins++;
				}
				else
				{
					Player2Wins++;
				}
			}
		}
	}

	// Check if the match is over
	if (Player1Wins >= TotalRounds || Player2Wins >= TotalRounds)
	{
		IsMatchOver = true;
		// Handle match over logic here (e.g., show end screen, reset game, etc.)
	}
	else
	{
		// Start a new round
		CurRound++;
		StartRound();
	}
}