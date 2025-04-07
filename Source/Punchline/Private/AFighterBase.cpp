// Fill out your copyright notice in the Description page of Project Settings.


#include "AFighterBase.h"

#include <EnhancedInputLibrary.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>



// Sets default values
AAFighterBase::AAFighterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Hurtbox = nullptr;
}

// Called when the game starts or when spawned
void AAFighterBase::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("FighterBase: Failed to get BaseAnimInstance!"));
	}

	// Add Mapping Context
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (InputSubsystem)
		{
			InputSubsystem->AddMappingContext(FighterMappingContext, 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Input Subsystem found"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Controller found"));
	}
}

void AAFighterBase::Punch()
{
	if (PunchKickMontage && GetMesh()->GetAnimInstance())
	{
		// Currently this is not working, believe it is due to the State Machine overriding 
		// the animation. Thinking we need to add a new state and make some communication for the
		// Animation to trigger.
		//GetMesh()->GetAnimInstance()->Montage_Play(PunchKickMontage);
		
		// Attempting for this to be right
		AnimInstance->NotifyToPunch();
		UE_LOG(LogTemp, Warning, TEXT("Punching!"));
	}
}

void AAFighterBase::Kick()
{
	UE_LOG(LogTemp, Warning, TEXT("Default Kicking"));
	InflictDamage(50);
}

void AAFighterBase::Block()
{
	UE_LOG(LogTemp, Warning, TEXT("Default Blocking"));
	AnimInstance->NotifyToDie();
	Health = 0;
}


void AAFighterBase::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Default Dying"));
	AnimInstance->NotifyToDie();
	Health = 0;
}

void AAFighterBase::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Jumping Jumping"));
	if (CanJump())
	{
		ACharacter::Jump();  // Calls built-in UE5 jump function
	}
}

void AAFighterBase::StopJumping()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop Jumping"));
	ACharacter::StopJumping();
}

void AAFighterBase::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	if (Movement.SizeSquared() < 0.01f || Health <= 0)
	{
		Movement = FVector2D::ZeroVector;
	}

	float xInput = Movement.X * -1;


	AddMovementInput(FVector(xInput, 0, 0), Value.GetMagnitude());
	
}

// Called every frame
void AAFighterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0) {
		Die();
		return;
	}
}

void AAFighterBase::InflictDamage(int Amount)
{
	Health -= Amount;
}

// Called to bind functionality to input
void AAFighterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(InputToMove, ETriggerEvent::Triggered, this, &AAFighterBase::Move);
		EnhancedInputComponent->BindAction(InputToJump, ETriggerEvent::Triggered, this, &AAFighterBase::Jump);
		EnhancedInputComponent->BindAction(InputToJump, ETriggerEvent::Completed, this, &AAFighterBase::StopJumping);
		EnhancedInputComponent->BindAction(InputToBlock, ETriggerEvent::Triggered, this, &AAFighterBase::Block);
		EnhancedInputComponent->BindAction(InputToPunch, ETriggerEvent::Triggered, this, &AAFighterBase::Punch);
		EnhancedInputComponent->BindAction(InputToKick, ETriggerEvent::Triggered, this, &AAFighterBase::Kick);
	}

}

