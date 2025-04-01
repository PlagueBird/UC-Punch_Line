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

	//PunchKickMontage = nullptr;

	/*static ConstructorHelpers::FObjectFinder<UAnimMontage> MontageObj(TEXT("/Script/Engine.AnimMontage'/Game/Mutant/Animations/Mutant_Punch_Montage.Mutant_Punch_Montage'"));
	if (MontageObj.Succeeded())
	{
		PunchKickMontage = MontageObj.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Montage found"));
	}*/
}

// Called when the game starts or when spawned
void AAFighterBase::BeginPlay()
{
	Super::BeginPlay();

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
		GetMesh()->GetAnimInstance()->Montage_Play(PunchKickMontage);
		UE_LOG(LogTemp, Warning, TEXT("Punching!"));
	}
}

void AAFighterBase::Kick()
{
	UE_LOG(LogTemp, Warning, TEXT("Default Kicking"));
}

void AAFighterBase::Block()
{
	UE_LOG(LogTemp, Warning, TEXT("Default Blocking"));
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

	if (Movement.SizeSquared() < 0.01f)
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

