// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseControls.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Utility/BaseGameInstance.h"
#include "Components/CheckBox.h"
#include "Widgets/PauseSettings.h"

void UPauseControls::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UPauseControls::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance->LoadGame(GameInstance->SlotString);

	CrouchCheckBox->SetIsChecked(GameInstance->bIsCrouchChecked);
	SprintCheckBox->SetIsChecked(GameInstance->bIsSprintChecked);

	BackButton->OnClicked.AddDynamic(this, &UPauseControls::OnClickedBack);
	CrouchCheckBox->OnCheckStateChanged.AddDynamic(this, &UPauseControls::OnCheckMarkCrouch);
	SprintCheckBox->OnCheckStateChanged.AddDynamic(this, &UPauseControls::OnCheckMarkSprint);

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}
}

void UPauseControls::OnClickedBack()
{
	RemoveFromParent();
	//SettingsHUD = CreateWidget<UPauseSettings>(GetWorld(), SettingsClass);
	SettingsHUD->SetVisibility(ESlateVisibility::Visible);
	SettingsHUD->AddToViewport();
	SettingsHUD->SetFocus();
	GameInstance->SaveGame(GameInstance->SlotString);
}

void UPauseControls::OnCheckMarkCrouch(bool IsChecked)
{
	GameInstance->bIsCrouchChecked = IsChecked;
}

void UPauseControls::OnCheckMarkSprint(bool IsChecked)
{
	GameInstance->bIsSprintChecked = IsChecked;
}
