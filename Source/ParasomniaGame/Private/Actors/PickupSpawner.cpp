// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickupSpawner.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");

}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();

	int rand = UKismetMathLibrary::RandomIntegerInRange(1, 2);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Random Number: %d"), rand));

	switch (rand)
	{
	case 1:
	{
		AEnergyPickup* Cell = GetWorld()->SpawnActor<AEnergyPickup>(EnergyPickupClass, GetActorLocation(), GetActorRotation());
		Cell->PickupMesh->SetVisibility(false);
		MeshComp->SetVisibility(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Destroy();
		break;
	}
	case 2:
	{
		ARationsPickup* Food = GetWorld()->SpawnActor<ARationsPickup>(RationsPickupClass, GetActorLocation(), GetActorRotation());
		Food->PickupMesh->SetVisibility(false);
		MeshComp->SetVisibility(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	}

	case 3:
		break;
	}
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

