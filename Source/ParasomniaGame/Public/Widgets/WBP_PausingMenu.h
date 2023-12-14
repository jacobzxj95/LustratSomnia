// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_PausingMenu.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UWBP_PausingMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	// Variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ResumeButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* RestartButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* OptionButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* QuitButton;

	UPROPERTY(BlueprintReadOnly)
		TArray<class UWBP_ButtonsNText*> Buttons;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* ButtonBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ButtonIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UPauseSettings* SettingsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UPauseSettings> SettingsClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pause Menu")
		bool bResumedFromButton;

	// Functions
	UFUNCTION(BlueprintCallable)
		void OnClickedResume();

	UFUNCTION()
		void OnHoveredResume();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedRestart();

	virtual void OnClickedRestart_Implementation();

	UFUNCTION()
		void OnHoveredRestart();

	UFUNCTION(BlueprintCallable)
		void OnClickedOptions();

	UFUNCTION()
		void OnHoveredOptions();

	UFUNCTION(BlueprintCallable)
		void OnClickedMainMenu();

	UFUNCTION()
		void OnHoveredMainMenu();

	UFUNCTION(BlueprintCallable)
		void OnClickedQuit();

	UFUNCTION()
		void OnHoveredQuit();

	UFUNCTION(BlueprintCallable)
		void UpdateButtonState();
};
