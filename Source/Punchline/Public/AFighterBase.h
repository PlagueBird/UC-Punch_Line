// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <EnhancedInputLibrary.h>
#include <BaseAnimInstance.h>
#include "AFighterBase.generated.h"



UCLASS(Blueprintable)
class PUNCHLINE_API AAFighterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAFighterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enhanced Input")
	UInputMappingContext* FighterMappingContext;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enhanced Input")
	UInputAction* InputToMove;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enhanced Input")
	UInputAction* InputToJump;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enhanced Input")
	UInputAction* InputToPunch;
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enhanced Input")
	UInputAction* InputToKick;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Enhanced Input")
	UInputAction* InputToBlock;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Animation")
	UBaseAnimInstance* AnimInstance;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health;

	// Can add more stats in the future, but currently not sure
	// what to add or what we want to do for different characters
	// Some ideas: Speed, Jump Height, Overall Damage Modifier




	// Basic Moves
	virtual void Punch();
	virtual void Kick();
	virtual void Block();


	virtual void Jump();
	virtual void StopJumping();
	virtual void Move(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimMontage* PunchKickMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};