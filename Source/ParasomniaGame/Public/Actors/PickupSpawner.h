// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyPickup.h"
#include "RationsPickup.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "PickupSpawner.generated.h"

class AEnergyPickup;
class ARationsPickup;
class UStaticMeshComponent;

UCLASS()
class PARASOMNIAGAME_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

	UPROPERTY(EditAnywhere, Category = "Pickup")
		TSubclassOf<AEnergyPickup> EnergyPickupClass;

	UPROPERTY(EditAnywhere, Category = "Pickup")
		TSubclassOf<ARationsPickup> RationsPickupClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
