// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <AFighterBase.h>
#include "HitboxActor.generated.h"



UENUM(BlueprintType)
enum class EHitboxEnum : uint8
{
	HB_PROXIMITY UMETA(DisplayName = "Proximity"),
	HB_STRIKE UMETA(DisplayName = "Strike"),
	HB_HURTBOX UMETA(DisplayName = "Hurtbox")
};


UCLASS()
class PUNCHLINE_API AHitboxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitboxActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
	AAFighterBase* OwningPlayer;
	
	UFUNCTION(BlueprintCallable)
	void VisualizeHitbox();

	UFUNCTION(BlueprintCallable)
	void CheckCollision();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	EHitboxEnum HitboxType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	FVector HitboxLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	float HitboxDamage = 0;

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
