// Fill out your copyright notice in the Description page of Project Settings.


#include "HitboxActor.h"

// Sets default values
AHitboxActor::AHitboxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHitboxActor::VisualizeHitbox()
{
}

void AHitboxActor::CheckCollision()
{
    //if (!HitBox) return;

    //// Array to hold all overlapping actors
    //TArray<AActor*> OverlappingActors;
    //HitBox->GetOverlappingActors(OverlappingActors);

    //for (AActor* Actor : OverlappingActors)
    //{
    //    if (Actor && Actor != this)
    //    {
    //        // Optional: Check for specific tag or interface
    //        if (Actor->ActorHasTag(FName("Enemy")) || Actor->Implements<UDamageableInterface>())
    //        {
    //            UE_LOG(LogTemp, Warning, TEXT("Hit detected on %s"), *Actor->GetName());

    //            // Example: Call an interface function
    //            IDamageableInterface::Execute_TakeDamage(Actor, 10.0f); // Apply 10 damage

    //            // Optionally disable hitbox to prevent multiple hits
    //            HitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    //            return;
    //        }
    //    }
    //}
}



// Called when the game starts or when spawned
void AHitboxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitboxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

