// Fill out your copyright notice in the Description page of Project Settings.


#include "CoyoteAICharacter.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Prey/KilldeerCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ACoyoteAICharacter::ACoyoteAICharacter()
{
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CollisionCompCap = GetCapsuleComponent();
	CollisionCompCap->SetCapsuleRadius(50.f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);
}

// Called when the game starts or when spawned
void ACoyoteAICharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = FMath::RandRange(minSpeed, maxSpeed);
}

// Called every frame
void ACoyoteAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, FString::Printf(TEXT("VELOCITY: %d"), this->GetVelocity().Length()));
	if (this->GetVelocity().Length() > 3 && this->GetVelocity().Length() < 401)
		EZombieMovementEnums = EZombieMovement::EMWalking;
	else if(this->GetVelocity().Length() >= 401)
		EZombieMovementEnums = EZombieMovement::EMRunning;
	if (this->GetVelocity().Length() <= 3)
		EZombieMovementEnums = EZombieMovement::EMIdle;*/  // Will be used for animation maybe?

}

// Called to bind functionality to input
void ACoyoteAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



