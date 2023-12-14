// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utility/BaseGameInstance.h"
#include "OptionsMenu.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FVideoOptions
{
	GENERATED_BODY()

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UHorizontalBox*> VidsOpts;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTextBlock* VidOptName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<class UWBP_ButtonsNText*> ChoiceInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ChoiceIndex;
};

UCLASS()
class PARASOMNIAGAME_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
		UBaseGameInstance* GameInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USettingsMenu* SettingsHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class USettingsMenu> SettingsClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UVerticalBox* VidOptBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FVideoOptions> VidOptArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int VidOptIndex;

	TArray<UTextBlock*> SecretArray;

	// Window Mode

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* WindowModeText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* windowmodeM;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* windowmodeP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TEnumAsByte<EWindowMode::Type> windowmodeType;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedWindowModeM();

	void OnClickedWindowModeM_Implementation();

	UFUNCTION()
		void OnHoveredWindowModeM();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedWindowModeP();

	void OnClickedWindowModeP_Implementation();

	UFUNCTION()
		void OnHoveredWindowModeP();
	
	// Screen Resolution
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* ScreenResolutionText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* screenresolutionM;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* screenresolutionP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 resolutionIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntPoint resolution;

	UFUNCTION(BlueprintCallable)
		void OnClickedScreenResolutionM();

	UFUNCTION()
		void OnHoveredScreenResolutionM();

	UFUNCTION(BlueprintCallable)
		void OnClickedScreenResolutionP();

	UFUNCTION()
		void OnHoveredScreenResolutionP();

	// Graphics
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* GraphicsText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* graphicsM;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* graphicsP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 graphicsIndex;

	UFUNCTION(BlueprintCallable)
		void OnClickedGraphicsM();

	UFUNCTION()
		void OnHoveredGraphicsM();
	
	UFUNCTION(BlueprintCallable)
		void OnClickedGraphicsP();

	UFUNCTION()
		void OnHoveredGraphicsP();

	// VSync
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* VSyncText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* vsyncM;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* vsyncP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bIsVsync;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TObjectPtr<class UGameUserSettings> settings;

	UFUNCTION(BlueprintCallable)
		void OnClickedVSyncM();

	UFUNCTION()
		void OnHoveredVSyncM();

	UFUNCTION(BlueprintCallable)
		void OnClickedVSyncP();

	UFUNCTION()
		void OnHoveredVSyncP();

	// Apply
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* ApplyButton;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClickedApply();

	virtual void OnClickedApply_Implementation();

	// Back
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UWBP_ButtonsNText* BackButton;

	UFUNCTION(BlueprintCallable)
		void OnClickedBack();

	UFUNCTION(BlueprintCallable)
		void UpdateButtonStates();

	UFUNCTION(BlueprintCallable)
		void MoveThroughOptionsDown();

	UFUNCTION(BlueprintCallable)
		void MoveThroughOptionsUp();

	UFUNCTION(BlueprintCallable)
		void MoveThroughChoicesRight();

	UFUNCTION(BlueprintCallable)
		void MoveThroughChoicesLeft();

	UFUNCTION(BlueprintCallable)
		void OnChoice();
};
