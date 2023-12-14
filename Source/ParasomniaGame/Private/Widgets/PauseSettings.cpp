// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseSettings.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Utility/BaseGameInstance.h"
#include "Widgets/PauseAudio.h"
#include "Widgets/PauseControls.h"
#include "Widgets/WBP_PausingMenu.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPauseSettings::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UPauseSettings::NativeConstruct()
{
	Super::NativeConstruct();
	AudioButton->OnClicked.AddDynamic(this, &UPauseSettings::OnClickedAudio);
	AudioButton->BackgroundButton->OnHovered.AddDynamic(this, &UPauseSettings::OnHoveredAudio);
	ControlsButton->OnClicked.AddDynamic(this, &UPauseSettings::OnClickedControls);
	ControlsButton->BackgroundButton->OnHovered.AddDynamic(this, &UPauseSettings::OnHoveredControls);
	BackButton->OnClicked.AddDynamic(this, &UPauseSettings::OnClickedBack);

	for (UWidget* Button : ButtonBox->GetAllChildren())
	{
		UWBP_ButtonsNText* ButtonText = Cast<UWBP_ButtonsNText>(Button);
		if (ButtonText)
		{
			Buttons.Add(ButtonText);
			//print out the buttons onto the screen
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Button: %s"), *ButtonText->ButtonText->GetText().ToString()));
		}
	}
	UpdateButtonState();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}
}

void UPauseSettings::OnClickedAudio()
{
	//RemoveFromParent();
	SetVisibility(ESlateVisibility::Hidden);
	AudioHUD = CreateWidget<UPauseAudio>(GetWorld(), AudioClass);
	AudioHUD->AddToViewport();
	AudioHUD->SettingsHUD = this;
}

void UPauseSettings::OnHoveredAudio()
{
	ButtonIndex = 0;
	UpdateButtonState();
}

void UPauseSettings::OnClickedControls()
{
	//RemoveFromParent();
	SetVisibility(ESlateVisibility::Hidden);
	ControlsHUD = CreateWidget<UPauseControls>(GetWorld(), ControlsClass);
	ControlsHUD->AddToViewport();
	ControlsHUD->SettingsHUD = this;
}

void UPauseSettings::OnHoveredControls()
{
	ButtonIndex = 1;
	UpdateButtonState();
}

void UPauseSettings::OnClickedBack()
{
	RemoveFromParent();
	PauseHUD->AddToViewport();
	PauseHUD->SetVisibility(ESlateVisibility::Visible);

	if (!PauseHUD->IsInViewport())
	{
		PauseHUD->SetFocus();
	}
}

void UPauseSettings::UpdateButtonState()
{
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		if (i == ButtonIndex)
		{
			//Buttons[i]->BackgroundButton->SetVisibility(ESlateVisibility::Visible);
			Buttons[i]->ButtonText->SetColorAndOpacity(FLinearColor::Yellow);
		}
		else
		{
			//Buttons[i]->BackgroundButton->SetVisibility(ESlateVisibility::Hidden);
			Buttons[i]->ButtonText->SetColorAndOpacity(FLinearColor::White);
		}
	}
}

void UPauseSettings::MoveArrayDown()
{
	if (ButtonIndex < Buttons.Num() - 1)
	{
		ButtonIndex++;
	}
	else
	{
		ButtonIndex = 0;
	}
	UpdateButtonState();
}

void UPauseSettings::MoveArrayUp()
{
	if (ButtonIndex > 0)
	{
		ButtonIndex--;
	}
	else
	{
		ButtonIndex = Buttons.Num() - 1;
	}
	UpdateButtonState();
}
