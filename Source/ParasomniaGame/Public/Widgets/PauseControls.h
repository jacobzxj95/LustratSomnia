// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseControls.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UPauseControls : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
		class UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UPauseSettings* SettingsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UPauseSettings> SettingsClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UCheckBox* CrouchCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UCheckBox* SprintCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* BackButton;

	UFUNCTION(BlueprintCallable)
		void OnClickedBack();

	UFUNCTION()
		void OnCheckMarkCrouch(bool IsChecked);

	UFUNCTION()
		void OnCheckMarkSprint(bool IsChecked);
};
