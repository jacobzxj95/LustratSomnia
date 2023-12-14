// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_PausingMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/BaseGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Utility/BaseSaveSystem.h"
#include "Actors/BasePlayer.h"
#include "Widgets/OptionsMenu.h"
#include "Widgets/PauseSettings.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWBP_PausingMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UWBP_PausingMenu::NativeConstruct()
{
	Super::NativeConstruct();

	/*SettingsHUD = CreateWidget<UPauseSettings>(GetWorld(), SettingsClass);
	SettingsHUD->AddToViewport();
	SettingsHUD->SetVisibility(ESlateVisibility::Hidden);*/

	ResumeButton->OnClicked.AddDynamic(this, &UWBP_PausingMenu::OnClickedResume);
	ResumeButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_PausingMenu::OnHoveredResume);

	RestartButton->OnClicked.AddDynamic(this, &UWBP_PausingMenu::OnClickedRestart);
	RestartButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_PausingMenu::OnHoveredRestart);

	OptionButton->OnClicked.AddDynamic(this, &UWBP_PausingMenu::OnClickedOptions);
	OptionButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_PausingMenu::OnHoveredOptions);

	MainMenuButton->OnClicked.AddDynamic(this, &UWBP_PausingMenu::OnClickedMainMenu);
	MainMenuButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_PausingMenu::OnHoveredMainMenu);

	QuitButton->OnClicked.AddDynamic(this, &UWBP_PausingMenu::OnClickedQuit);
	QuitButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_PausingMenu::OnHoveredQuit);

	for (UWidget* Buttons_ : ButtonBox->GetAllChildren())
	{
		UWBP_ButtonsNText* Button = Cast<UWBP_ButtonsNText>(Buttons_);
		if (Button)
			Buttons.Add(Button);
	}
	UpdateButtonState();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}

	bResumedFromButton = false;
}

void UWBP_PausingMenu::OnClickedResume()
{
	//RemoveFromParent();
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer()->bShowMouseCursor = false;
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	GetOwningPlayer()->SetPause(false);
	SettingsHUD = nullptr;

	bResumedFromButton = true;
}

void UWBP_PausingMenu::OnHoveredResume()
{
	ButtonIndex = 0;
	UpdateButtonState();
}

void UWBP_PausingMenu::OnClickedRestart_Implementation()
{
	GameInstance->RestartLevel();
}

void UWBP_PausingMenu::OnHoveredRestart()
{
	ButtonIndex = 1;
	UpdateButtonState();
}

void UWBP_PausingMenu::OnClickedOptions()
{
	//RemoveFromParent();
	SetVisibility(ESlateVisibility::Hidden);
	SettingsHUD = CreateWidget<UPauseSettings>(GetWorld(), SettingsClass);
	SettingsHUD->AddToViewport();
	SettingsHUD->SetVisibility(ESlateVisibility::Visible);
	SettingsHUD->PauseHUD = this;

	if (!SettingsHUD->HasAnyUserFocus())
	{
		SettingsHUD->SetFocus();
	}
}

void UWBP_PausingMenu::OnHoveredOptions()
{
	ButtonIndex = 2;
	UpdateButtonState();
}

void UWBP_PausingMenu::OnClickedMainMenu()
{
	GameInstance->LoadMainMenu();
}

void UWBP_PausingMenu::OnHoveredMainMenu()
{
	ButtonIndex = 3;	
	UpdateButtonState();
}

void UWBP_PausingMenu::OnClickedQuit()
{
	GameInstance->bQuitThroughPause = true;

	GameInstance->SaveGame(GameInstance->SlotString);
	GameInstance->Quit();
}

void UWBP_PausingMenu::OnHoveredQuit()
{
	ButtonIndex = 4;
	UpdateButtonState();
}

void UWBP_PausingMenu::UpdateButtonState()
{
	for (int i = 0; i < Buttons.Num(); i++)
	{
		if (i == ButtonIndex)
		{
			Buttons[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			Buttons[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
