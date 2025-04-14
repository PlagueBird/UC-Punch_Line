// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FightingCameraManager.generated.h"

UCLASS()
class PUNCHLINE_API AFightingCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFightingCameraManager();

	virtual void UpdateCamera(float DeltaTime) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinCameraDistance = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxCameraDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraHeight = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraZoomSpeed = 5.0f;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	FVector CalculateCameraPosition(const FVector& Player1Location, const FVector& Player2Location);

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	BP_*/
};
