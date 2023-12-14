// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Utility/BaseGameInstance.h"
#include "Actors/SelectionPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/WBP_LoadScreen.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */

class UWBP_ButtonsNText;
class USlider;
class ASelectionPawn;
//class ABasePlayer;
class UBaseGameIsntance;
class USkeletalMesh;
class UMaterial;
class UMaterialInstance;
class UCanvasPanel;

UCLASS()
class PARASOMNIAGAME_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UWBP_ButtonsNText* Char1Button;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UWBP_ButtonsNText* Char2Button;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UWBP_ButtonsNText* Char3Button;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		USlider* PlayerSlider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UWBP_ButtonsNText* ContinueButton;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
		UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<UWBP_ButtonsNText*> ButtonArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int CurrentButtonIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Value;

	UFUNCTION(BlueprintCallable)
		void OnClickedChar1();

	UFUNCTION()
		void OnHoveredChar1();

	UFUNCTION(BlueprintCallable)
		void OnClickedChar2();

	UFUNCTION()
		void OnHoveredChar2();

	UFUNCTION(BlueprintCallable)
		void OnClickedChar3();

	UFUNCTION()
		void OnHoveredChar3();

	UFUNCTION(BlueprintCallable)
		void OnValueChangedSlider(float _Value);

	UFUNCTION()
		void SliderLeft(float _Value);

	UFUNCTION(BlueprintCallable)
		void OnClickedContinue();

	UFUNCTION()
		void OnHoveredContinue();

	UFUNCTION()
		void JustToCheckTimer();

	UFUNCTION(BlueprintCallable)
		void UpdateButtonState();

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ASelectionPawn* CharacterPawn;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ABasePlayer* PlayerCppFile;*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterial* CharacterMaterial1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterialInstance* CharacterMaterial2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterialInstance* CharacterMaterial3;

	UPROPERTY()
		UBaseGameInstance* GameInstance;
};
