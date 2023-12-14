// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SettingsMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Utility/BaseGameInstance.h"
#include "Widgets/WBP_MainMenu.h"
#include "Widgets/OptionsMenu.h"
#include "Widgets/AudioOptions.h"
#include "Widgets/ControlsOptions.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Widgets/WBP_ButtonsNText.h"

void USettingsMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void USettingsMenu::NativeConstruct()
{
	Super::NativeConstruct();
	OptionsButton->OnClicked.AddDynamic(this, &USettingsMenu::OnClickedOptions);
	OptionsButton->BackgroundButton->OnHovered.AddDynamic(this, &USettingsMenu::OnHoveredOptions); 
	AudioButton->OnClicked.AddDynamic(this, &USettingsMenu::OnClickedAudio);
	AudioButton->BackgroundButton->OnHovered.AddDynamic(this, &USettingsMenu::OnHoveredAudio); 
	ControlsButton->OnClicked.AddDynamic(this, &USettingsMenu::OnClickedControls);
	ControlsButton->BackgroundButton->OnHovered.AddDynamic(this, &USettingsMenu::OnHoveredControls);
	BackButton->OnClicked.AddDynamic(this, &USettingsMenu::OnClickedBack);

	for (UWidget* buttons : SettingsBox->GetAllChildren())
	{
		UWBP_ButtonsNText* button = Cast<UWBP_ButtonsNText>(buttons);
		if (button)
		{
			SettingButtons.Add(button);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Button: %s"), *button->ButtonText->GetText().ToString()));
		}
	}
	UpdateButtonState();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}
}

void USettingsMenu::OnClickedOptions()
{
	RemoveFromParent();
	OptionsHUD = CreateWidget<UOptionsMenu>(GetWorld(), OptionsClass);
	OptionsHUD->AddToViewport();
}

void USettingsMenu::OnHoveredOptions()
{
	SettNavIndex = 0;
	UpdateButtonState();
}

void USettingsMenu::OnClickedAudio()
{
	RemoveFromParent();
	AudioHUD = CreateWidget<UAudioOptions>(GetWorld(), AudioClass);
	AudioHUD->AddToViewport();
}

void USettingsMenu::OnHoveredAudio()
{
	SettNavIndex = 1;
	UpdateButtonState();
}

void USettingsMenu::OnClickedControls()
{
	RemoveFromParent();
	ControlsHUD = CreateWidget<UControlsOptions>(GetWorld(), ControlsClass);
	ControlsHUD->AddToViewport();
}

void USettingsMenu::OnHoveredControls()
{
	SettNavIndex = 2;
	UpdateButtonState();
}

void USettingsMenu::OnClickedBack()
{
	RemoveFromParent();
	MainMenuHUD = CreateWidget<UWBP_MainMenu>(GetWorld(), MainMenuClass);
	MainMenuHUD->AddToViewport();
}

void USettingsMenu::UpdateButtonState()
{
	for (int i = 0; i < SettingButtons.Num(); i++)
	{
		if (i == SettNavIndex)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Index: %d FOUND"), SettNavIndex));
			SettingButtons[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			SettingButtons[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
