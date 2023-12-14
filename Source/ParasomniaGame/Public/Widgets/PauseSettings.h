// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseSettings.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UPauseSettings : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
		class UBaseGameInstance* GameInstance;
	// Pause Menu
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UWBP_PausingMenu* PauseHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWBP_PausingMenu> PauseClass;

	// Audio
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UPauseAudio* AudioHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UPauseAudio> AudioClass;

	// Controls
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UPauseControls* ControlsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UPauseControls> ControlsClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* AudioButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ControlsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* BackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* ButtonBox;

	UPROPERTY(BlueprintReadOnly)
		TArray<class UWBP_ButtonsNText*> Buttons;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int ButtonIndex;

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

	UFUNCTION(BlueprintCallable)
		void MoveArrayDown();

	UFUNCTION(BlueprintCallable)
		void MoveArrayUp();
	
};
