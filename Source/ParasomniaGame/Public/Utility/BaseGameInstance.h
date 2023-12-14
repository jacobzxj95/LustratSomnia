// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */

class USkeletalMesh;
class UMaterialInstance;
class UBaseSaveSystem;
class UWBP_LoadScreen;

UCLASS()
class PARASOMNIAGAME_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Functions
	UFUNCTION(BlueprintCallable)
		void LoadLevelOne();

	UFUNCTION(BlueprintCallable)
		void LoadSelectLevel();

	UFUNCTION(BlueprintCallable)
		void LoadLevelSafe(int32 MapIndex);

	UFUNCTION(BlueprintCallable)
		void Quit();

	UFUNCTION(BlueprintCallable)
		void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
		void LoadLevelCurrent();

	UFUNCTION(BlueprintCallable)
		void RestartLevel();

	UFUNCTION(BlueprintCallable)
		void CalculateFinalScore();

	UFUNCTION(BlueprintCallable)
		void SaveGame(FString SlotName, bool Setting = false);

	UFUNCTION(BlueprintCallable)
		void LoadGame(FString SlotName, bool Setting = false);

	// Variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UBaseSaveSystem* SaveSystem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FName> LevelArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 LevelOne;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CharSelectLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 LevelCurrent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 LevelMainMenu;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName LevelName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString SlotString;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ObjectiveIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USkeletalMesh* CharacterMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterialInstance* CharacterMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UWBP_LoadScreen* LoadingHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UWBP_LoadScreen> LoadingClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CellPointModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RationPointModifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float PeoplePointModifier;


#pragma region Stats Tracked
	UPROPERTY()
		float EnergyAmountSaved;

	UPROPERTY()
		int EnergyCellsCollected;

	UPROPERTY()
		int32 RationsSaved;

	UPROPERTY()
		int32 PeopleSaved;

	UPROPERTY()
		bool bIsNightmare;

	UPROPERTY()
		bool bQuitThroughPause;

	UPROPERTY()
		int Minutes;

	UPROPERTY()
		int Seconds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<EWindowMode::Type> WindowType;

	UPROPERTY()
		int FinalScore;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsCrouchChecked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsSprintChecked;

	UPROPERTY()
		bool bHintHUD = false;
#pragma endregion

	// MoviePlayer
	virtual void Init() override;

	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* InLoadedWorld);
};
