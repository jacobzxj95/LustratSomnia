// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UWBP_MainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	// Variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* MainMenuBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* NewGameButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ContinueButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* OptionsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* CreditsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* QuitButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MenuNavIndex;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<UWBP_ButtonsNText*> MenuButtons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USettingsMenu* SettingsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class USettingsMenu> SettingsClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCreditsMenu* CreditsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UCreditsMenu> CreditsClass;


	// Functions
	UFUNCTION(BlueprintCallable)
		void OnClickedNewGame();

	UFUNCTION(BlueprintCallable)
		void OnHoveredNewGame();

	UFUNCTION(BlueprintCallable)
		void OnClickedContinue();

	UFUNCTION(BlueprintCallable)
		void OnHoveredContinue();

	UFUNCTION(BlueprintCallable)
		void OnClickedOptions();

	UFUNCTION(BlueprintCallable)
		void OnHoveredOptions();

	UFUNCTION(BlueprintCallable)
		void OnClickedCredits();

	UFUNCTION(BlueprintCallable)
		void OnHoveredCredits();

	UFUNCTION(BlueprintCallable)
		void OnClickedQuit();

	UFUNCTION(BlueprintCallable)
		void OnHoveredQuit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UpdateButtonState();

	void UpdateButtonState_Implementation();

	//virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
};
