// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// Functions
	ABasePlayerController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		void WinMenuControllerSetup();

	UFUNCTION(BlueprintCallable)
		void WinMenuControllerTeardown();

protected:
	// Functions
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWBP_WinMenu> WinHUD;
};
