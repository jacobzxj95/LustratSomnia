// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// Functions
	AMainMenuPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	// Functions
	virtual void BeginPlay() override;

public:
	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWBP_MainMenu> MainMenuHUD;
};
