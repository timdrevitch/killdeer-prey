// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nest.generated.h"

UCLASS()
class PREY_API ANest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANest();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	//USceneComponent* NestSpawnPoint;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;


	UPROPERTY(EditAnywhere, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float NestHealth = 100.0f;

};