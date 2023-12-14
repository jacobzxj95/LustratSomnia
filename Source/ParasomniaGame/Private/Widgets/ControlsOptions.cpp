// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ControlsOptions.h"
#include "Widgets/SettingsMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Utility/BaseGameInstance.h"
#include "Components/CheckBox.h"

void UControlsOptions::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UControlsOptions::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance->LoadGame(GameInstance->SlotString);

	CrouchCheckBox->SetIsChecked(GameInstance->bIsCrouchChecked);
	SprintCheckBox->SetIsChecked(GameInstance->bIsSprintChecked);

	BackButton->OnClicked.AddDynamic(this, &UControlsOptions::OnClickedBack);
	CrouchCheckBox->OnCheckStateChanged.AddDynamic(this, &UControlsOptions::OnCheckMarkCrouch);
	SprintCheckBox->OnCheckStateChanged.AddDynamic(this, &UControlsOptions::OnCheckMarkSprint);
}

void UControlsOptions::OnClickedBack()
{
	RemoveFromParent();
	SettingsHUD = CreateWidget<USettingsMenu>(GetWorld(), SettingsClass);
	SettingsHUD->AddToViewport();
	GameInstance->SaveGame(GameInstance->SlotString);
}

void UControlsOptions::OnCheckMarkCrouch(bool IsChecked)
{
	GameInstance->bIsCrouchChecked = IsChecked;
}

void UControlsOptions::OnCheckMarkSprint(bool IsChecked)
{
	GameInstance->bIsSprintChecked = IsChecked;
}
