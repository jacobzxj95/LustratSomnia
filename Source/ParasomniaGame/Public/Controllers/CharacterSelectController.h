// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "CharacterSelectController.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API ACharacterSelectController : public APlayerController
{
	GENERATED_BODY()

private:

	//create a begin play function
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		TSubclassOf<class UCharacterSelectWidget> CharacterSelectHUD;

	UPROPERTY()
		class UCharacterSelectWidget* CharacterSelectWidget;
	
};
