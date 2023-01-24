// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "KilldeerCharacter.generated.h"

UCLASS()
class PREY_API AKilldeerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKilldeerCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	bool bIsFlying;
	
	float Acceleration{30.f};
	float MaxSpeed{4000.0f};
	float MinSpeed{500.f};

	float RollRateMultiplier{200.f};
	float YawRateMultiplier{200.f};
	float PitchRateMultiplier{200.f};
	
	float CurrentForwardSpeed{500.f};

	float CurrentYawSpeed;
	float CurrentRollSpeed;
	float CurrentPitchSpeed;

	bool bIntentionalPitch{false};
	bool bIntentionalRoll{false};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* KilldeerMappingContext;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void ProcessPitch(float value);

	UFUNCTION()
	void ProcessRoll(float value);

private:	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

};
