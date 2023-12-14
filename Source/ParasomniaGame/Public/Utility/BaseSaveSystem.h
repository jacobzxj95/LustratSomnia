// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BaseSaveSystem.generated.h"

/**
 * 
 */

class USkeletalMesh;
class UMaterialInstance;

//using namespace EWindowMode;

UCLASS()
class PARASOMNIAGAME_API UBaseSaveSystem : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint32 LevelIndex;

	UPROPERTY()
		USkeletalMesh* CharMesh;

	UPROPERTY()
		UMaterialInstance* CharMaterial;

	UPROPERTY()
		float EnergyAmountSaved;

	UPROPERTY()
		int32 EnergyCellsCollected;

	UPROPERTY()
		int32 RationsSaved;

	UPROPERTY()
		int32 PeopleSaved;

	UPROPERTY()
		bool bIsNightmare;

	UPROPERTY()
		bool bQuitThroughPause;

	UPROPERTY()
		bool bToggleCrouch;

	UPROPERTY()
		bool bToggleSprint;

	UPROPERTY()
		int Minutes;

	UPROPERTY()
		int Seconds;

	UPROPERTY()
		TEnumAsByte<EWindowMode::Type> WindowType;

	UPROPERTY();
		int FinalScore;

	//here would be the array of the spawn points for energy

	//here would be the array of the spawn points for rations

	//here would be the array of the spawn points for the enemies

	//here would be the array of the spawn points for houses
};
