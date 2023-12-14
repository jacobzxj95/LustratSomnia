// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "GameFramework/Actor.h"
#include "AIPoolSpawnPoint.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIPoolSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, Category = "AI")
		TSubclassOf<ABaseAI> SpawnClass;

	UPROPERTY(EditAnywhere, Category = "AI")
		int MaxSpawnAmount;

	UPROPERTY(EditAnywhere, Category = "AI")
		int SpawnChance;
	
private:

	UPROPERTY()
		int CurrSpawnAmount;

	UPROPERTY()
		bool CanSpawn;

public:

	AAIPoolSpawnPoint();

	UFUNCTION()
		bool SetSpawnCheck();

	UFUNCTION()
		bool GetSpawnCheck() const;
	
	UFUNCTION()
		int	GetCurrSpawnAmt() const;
	
	UFUNCTION()
		void Spawned();

	UFUNCTION()
		void Reset();
};
