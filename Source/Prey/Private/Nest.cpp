// Fill out your copyright notice in the Description page of Project Settings.


#include "Nest.h"
#include "Components/SphereComponent.h"

// Sets default values
ANest::ANest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	RootComponent = SphereComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(SphereComp);

	//NestSpawnPoint = CreateDefaultSubobject(USceneComponent)(TEXT("Nest Spawn Point"));

}

// Called when the game starts or when spawned
void ANest::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
