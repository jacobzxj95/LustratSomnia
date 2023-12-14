// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/AIPoolSpawnPoint.h"
#include "Components/SpawnPoolComponent.h"
#include "NightSpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API ANightSpawnPoint : public AAIPoolSpawnPoint
{
	GENERATED_BODY()

public:

	ANightSpawnPoint();
	
	UFUNCTION()
    	void SpawnNightAI();

	UFUNCTION()
		void StartSpawn();

	UPROPERTY(EditAnywhere, Category = "AI")
		float SpawnRate;

	UPROPERTY(EditAnywhere, Category = "AI")
		float SpawnDelay;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
		USpawnPoolComponent* AssignedPool;
};
