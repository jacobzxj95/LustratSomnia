// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AudioOptions.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAudioOpts
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		class UWBP_ButtonsNText* AudioOptButton;

	UPROPERTY(BlueprintReadWrite)
		class USlider* AudioOptSlider;
};

UCLASS()
class PARASOMNIAGAME_API UAudioOptions : public UUserWidget
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
		class UVerticalBox* AudioOptBox;

	UPROPERTY(BlueprintReadWrite)
		TArray<FAudioOpts> AudioOpts;

	UPROPERTY(BlueprintReadWrite)
		int AudioOptIndex;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class USlider* MasterSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ToggleAll;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class USlider* MusicSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ToggleMusic;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class USlider* SFXSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ToggleSFX;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class USlider* VoiceSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ToggleVoice;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* BackButton;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedToggleAll();

	void OnClickedToggleAll_Implementation();

	UFUNCTION(BlueprintCallable)
		void OnHoveredToggleAll();

	UFUNCTION(BlueprintNativeEvent)
		void OnChangedMasterVolume(float Value);

	void OnChangedMasterVolume_Implementation(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedToggleMusic();

	void OnClickedToggleMusic_Implementation();

	UFUNCTION(BlueprintCallable)
		void OnHoveredToggleMusic();

	UFUNCTION(BlueprintNativeEvent)
		void OnChangedMusicVolume(float Value);

	void OnChangedMusicVolume_Implementation(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedToggleSFX();

	void OnClickedToggleSFX_Implementation();

	UFUNCTION(BlueprintCallable)
		void OnHoveredToggleSFX();

	UFUNCTION(BlueprintNativeEvent)
		void OnChangedSFXVolume(float Value);

	void OnChangedSFXVolume_Implementation(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedToggleVoice();

	void OnClickedToggleVoice_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void OnChangedVoiceVolume(float Value);

	void OnChangedVoiceVolume_Implementation(float Value);

	UFUNCTION(BlueprintCallable)
		void OnHoveredToggleVoice();

	UFUNCTION(BlueprintCallable)
		void OnClickedBack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void SetAudioLevel(float Value);

	void SetAudioLevel_Implementation(float Value);

	UFUNCTION(BlueprintCallable)
		void MoveDownArray();

	UFUNCTION(BlueprintCallable)
		void MoveUpArray();

	UFUNCTION(BlueprintCallable)
		void UpdateButtonState();
	
};
