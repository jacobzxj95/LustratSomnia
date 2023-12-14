// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsMenu.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UCreditsMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
		class UBaseGameInstance* GameInstance;

	// Main Menu
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UWBP_MainMenu* MainMenuHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWBP_MainMenu> MainMenuClass;
	
	// Buttons
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* BackButton;

	UFUNCTION(BlueprintCallable)
		void OnClickedBack();

	UFUNCTION(BlueprintCallable)
		void OnHoveredBack();
	
};
