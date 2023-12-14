// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_WinMenu.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UWBP_WinMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	// Variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* RetryButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* WinChoiceBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class UWBP_ButtonsNText*> WinChoices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CurrentChoice;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		class UTextBlock* FinalScoreText;

	// Functions
	UFUNCTION(BlueprintCallable)
		void OnClickedMainMenu();

	UFUNCTION()
		void OnHoveredMainMenu();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void OnClickedRetry();

	void OnClickedRetry_Implementation();

	UFUNCTION()
		void OnHoveredRetry();

	UFUNCTION(BlueprintCallable)
		void UpdateButtonState();

	UFUNCTION(BlueprintCallable)
		void MoveChoiceUp();

	UFUNCTION(BlueprintCallable)
		void MoveChoiceDown();

	UFUNCTION(BlueprintCallable)
		void SelectChoice();
};
