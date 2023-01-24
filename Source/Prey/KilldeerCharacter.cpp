// Fill out your copyright notice in the Description page of Project Settings.


#include "KilldeerCharacter.h"

// Engine includes
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Enhanced Input includes
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AKilldeerCharacter::AKilldeerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AKilldeerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(KilldeerMappingContext, 0);
		}
	}

	bIsFlying = false;
}

// Move input binding
void AKilldeerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement
		if(!bIsFlying)
		{
			GEngine->AddOnScreenDebugMessage(0,0.f,FColor::Green, FString::Printf(TEXT("MOV: %f"),CurrentForwardSpeed));
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
		else
		{
			if ( FMath::Abs(MovementVector.X) > .2f)
				ProcessRoll(MovementVector.X * 2.f);
			if ( FMath::Abs(MovementVector.Y) > .2f)
				ProcessPitch(MovementVector.Y * 2.f);
		}
	}
}

// Look input binding
void AKilldeerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if(!bIsFlying)
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
		else
		{
			ProcessRoll(LookAxisVector.X);
			ProcessPitch(LookAxisVector.Y);
		}
	}
}

// Called every frame
void AKilldeerCharacter::Tick(float DeltaTime)
{
	if(bIsFlying)
	{
		float CurrentAcc = -GetActorRotation().Pitch * DeltaTime * Acceleration;
		float NewForwardSpeed = CurrentForwardSpeed + CurrentAcc;
		CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);

		const FVector LocalMove = FVector (CurrentForwardSpeed * DeltaTime, 0.f,0.f);
		AddActorLocalOffset(LocalMove, true);
		
		FRotator DeltaRotation(0,0,0);

		DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;
		DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
		DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;

		AddActorLocalRotation(DeltaRotation);

		GEngine->AddOnScreenDebugMessage(0,0.f,FColor::Green, FString::Printf(TEXT("SPD: %f"),CurrentForwardSpeed));
	}
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AKilldeerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKilldeerCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKilldeerCharacter::Look);
	}
}

void AKilldeerCharacter::ProcessRoll(float Value)
{
	bIntentionalRoll = FMath::Abs(Value) > 0.f;

	if(bIntentionalPitch && !bIntentionalRoll) return;
	
	float TargetRollSpeed = bIntentionalRoll? (Value * RollRateMultiplier): GetActorRotation().Roll * -2.f;
	
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(),2.f);
}

void AKilldeerCharacter::ProcessPitch(float Value)
{
	bIntentionalPitch = FMath::Abs(Value) > 0.f;
	
	float TargetPitchSpeed = Value * PitchRateMultiplier;
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(),2.f);
}
