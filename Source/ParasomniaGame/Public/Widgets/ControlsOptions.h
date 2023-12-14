// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlsOptions.generated.h"

/**
 * 
 */

class UCheckBox;

UCLASS()
class PARASOMNIAGAME_API UControlsOptions : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
		class UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USettingsMenu* SettingsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class USettingsMenu> SettingsClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UCheckBox* CrouchCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UCheckBox* SprintCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* BackButton;

	UFUNCTION()
		void OnClickedBack();

	UFUNCTION()
		void OnCheckMarkCrouch(bool IsChecked);

	UFUNCTION()
		void OnCheckMarkSprint(bool IsChecked);
};
