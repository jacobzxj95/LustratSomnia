// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaWidget.generated.h"

/**
 * 
 */

class UProgressBar;
class ABasePlayer;

UCLASS()
class PARASOMNIAGAME_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Variables", meta = (BindWidget))
		UProgressBar* StaminaBar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Variables")
		ABasePlayer* PlayerRef;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Variables")
		TSubclassOf<ABasePlayer> PlayerClass;
};
