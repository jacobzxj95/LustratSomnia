// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_MainMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/BaseGameInstance.h"
#include "Widgets/WBP_LoadScreen.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Widgets/OptionsMenu.h"
#include "GameFramework/GameUserSettings.h"
#include "Widgets/SettingsMenu.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Widgets/CreditsMenu.h"


void UWBP_MainMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		GameInstance->LoadGame(GameInstance->SlotString, true);
	}
}

void UWBP_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameButton->OnClicked.AddDynamic(this, &UWBP_MainMenu::OnClickedNewGame);
	NewGameButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_MainMenu::OnHoveredNewGame);

	ContinueButton->OnClicked.AddDynamic(this, &UWBP_MainMenu::OnClickedContinue);
	ContinueButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_MainMenu::OnHoveredContinue);

	OptionsButton->OnClicked.AddDynamic(this, &UWBP_MainMenu::OnClickedOptions);
	OptionsButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_MainMenu::OnHoveredOptions);

	CreditsButton->OnClicked.AddDynamic(this, &UWBP_MainMenu::OnClickedCredits);
	CreditsButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_MainMenu::OnHoveredCredits);

	QuitButton->OnClicked.AddDynamic(this, &UWBP_MainMenu::OnClickedQuit);
	QuitButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_MainMenu::OnHoveredQuit);

	for (UWidget* buttons : MainMenuBox->GetAllChildren())
	{
		UWBP_ButtonsNText* button = Cast<UWBP_ButtonsNText>(buttons); 
		if (button)
			MenuButtons.Add(button);
	}
	MenuNavIndex = 0;
	UpdateButtonState();

	TObjectPtr<class UGameUserSettings> settings;
	settings = UGameUserSettings::GetGameUserSettings();
	settings->LoadSettings();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}
}

void UWBP_MainMenu::OnClickedNewGame()
{
	GameInstance->RestartLevel();
	GameInstance->LoadSelectLevel();
}

void UWBP_MainMenu::OnHoveredNewGame()
{
	MenuNavIndex = 0;
	UpdateButtonState();
}

void UWBP_MainMenu::OnClickedContinue()
{
	GameInstance->LoadLevelCurrent();
}

void UWBP_MainMenu::OnHoveredContinue()
{
	MenuNavIndex = 1;
	UpdateButtonState();
}

void UWBP_MainMenu::OnClickedOptions()
{
	SettingsHUD = CreateWidget<class USettingsMenu>(GetWorld(), SettingsClass);
	SettingsHUD->AddToViewport();
}

void UWBP_MainMenu::OnHoveredOptions()
{
	MenuNavIndex = 2;
	UpdateButtonState();
}

void UWBP_MainMenu::OnClickedCredits()
{
	CreditsHUD = CreateWidget<class UCreditsMenu>(GetWorld(), CreditsClass);
	CreditsHUD->AddToViewport();
}

void UWBP_MainMenu::OnHoveredCredits()
{
	MenuNavIndex = 3;
	UpdateButtonState();
}

void UWBP_MainMenu::OnClickedQuit()
{
	GameInstance->Quit();
}

void UWBP_MainMenu::OnHoveredQuit()
{
	MenuNavIndex = 4;
	UpdateButtonState();
}

void UWBP_MainMenu::UpdateButtonState_Implementation()
{
	for (int i = 0; i < MenuButtons.Num(); i++)
	{
		if (i == MenuNavIndex)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Index: %d FOUND"), MenuNavIndex));
			MenuButtons[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
			MenuButtons[i]->BackgroundButton->SetBackgroundColor(FLinearColor(0.533333f, 0.019f, 0.019f, 1.0f));
			//MenuButtons[i]->BackgroundButton->
			//MenuButtons[i]->BackgroundButton->SetKeyboardFocus();
		}
		else
		{
			MenuButtons[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			MenuButtons[i]->BackgroundButton->SetBackgroundColor(FLinearColor(FColor::Black));
		}
	}
}
