// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenu.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API USettingsMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
		class UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* SettingsBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int SettNavIndex;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<class UWBP_ButtonsNText*> SettingButtons;

	// Main Menu
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UWBP_MainMenu* MainMenuHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWBP_MainMenu> MainMenuClass;

	// Options
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UOptionsMenu* OptionsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UOptionsMenu> OptionsClass;

	// Audio
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UAudioOptions* AudioHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UAudioOptions> AudioClass;

	// Controls
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UControlsOptions* ControlsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UControlsOptions> ControlsClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* OptionsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* AudioButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ControlsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* BackButton;

	UFUNCTION(BlueprintCallable)
		void OnClickedOptions();

	UFUNCTION()
		void OnHoveredOptions();

	UFUNCTION(BlueprintCallable)
		void OnClickedAudio();

	UFUNCTION()
		void OnHoveredAudio();

	UFUNCTION(BlueprintCallable)
		void OnClickedControls();

	UFUNCTION()
		void OnHoveredControls();

	UFUNCTION(BlueprintCallable)
		void OnClickedBack();

	UFUNCTION(BlueprintCallable)
		void UpdateButtonState();
};
