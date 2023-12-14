// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_LoseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UWBP_LoseMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	// Variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* RetryButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* QuitButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UVerticalBox* DeathChoiceBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UTextBlock* FinalScoreText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class UWBP_ButtonsNText*> DeathChoices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CurrentChoice;

	// Functions
	UFUNCTION(BlueprintNativeEvent)
		void OnClickedRetry();

	void OnClickedRetry_Implementation();

	UFUNCTION()
		void OnHoveredRetry();

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

	UFUNCTION(BlueprintCallable)
		void MoveDownArray();

	UFUNCTION(BlueprintCallable)
		void MoveUpArray();

	UFUNCTION(BlueprintCallable)
		void SelectChoice();
};
