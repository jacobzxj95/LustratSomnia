// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CreditsMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Utility/BaseGameInstance.h"
#include "Widgets/WBP_MainMenu.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UCreditsMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UCreditsMenu::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UCreditsMenu::OnClickedBack);
	BackButton->BackgroundButton->OnHovered.AddDynamic(this, &UCreditsMenu::OnHoveredBack);
}

void UCreditsMenu::OnClickedBack()
{
	RemoveFromParent();
	MainMenuHUD = CreateWidget<UWBP_MainMenu>(GetWorld(), MainMenuClass);
	MainMenuHUD->AddToViewport();
}

void UCreditsMenu::OnHoveredBack()
{
	BackButton->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
}

