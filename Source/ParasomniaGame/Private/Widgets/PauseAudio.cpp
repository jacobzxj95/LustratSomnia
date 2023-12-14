// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseAudio.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Utility/BaseGameInstance.h"
#include "Widgets/PauseSettings.h"

void UPauseAudio::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UPauseAudio::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UPauseAudio::OnClickedBack);

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}
}

void UPauseAudio::OnClickedBack()
{
	RemoveFromParent();
	SettingsHUD->SetVisibility(ESlateVisibility::Visible);
	SettingsHUD->AddToViewport();
	SettingsHUD->SetFocus();
}
