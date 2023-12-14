// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "Components/SceneComponent.h"
#include "SpawnPointSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARASOMNIAGAME_API USpawnPointSceneComponent : public USceneComponent
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
	USpawnPointSceneComponent();

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
