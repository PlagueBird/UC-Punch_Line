// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingCameraManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFightingCameraManager::AFightingCameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFightingCameraManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFightingCameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void AFightingCameraManager::UpdateCamera(float DeltaTime)
{
    Super::UpdateCamera(DeltaTime);
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), BP_PlayerCharacter, PlayerCharacters);    
    // Get player characters
   /* AActor* Player1 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AActor* Player2 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
  
    if (Player1 && Player2) 
    {
        FVector Player1Location = Player1->GetActorLocation();
        FVector Player2Location = Player2->GetActorLocation();

        FVector NewCameraLocation = CalculateCameraPosition(Player1Location, Player2Location);
        SetActorLocation(NewCameraLocation);
    }*/
}

FVector AFightingCameraManager::CalculateCameraPosition(const FVector& Player1Location, const FVector& Player2Location)
{
    FVector MidPoint = (Player1Location - Player2Location);
    float Distance = FVector::Dist(Player1Location, Player2Location);

    float CameraDistance = FMath::Clamp(Distance, MinCameraDistance, MaxCameraDistance);
    FVector CameraLocation = MidPoint + FVector(0.0f, 0.0f, CameraHeight) - FVector(CameraDistance, 0.0f, 0.0f);

    return CameraLocation;
}

