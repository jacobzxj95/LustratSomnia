// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_WinMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/BaseGameInstance.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UWBP_WinMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UWBP_WinMenu::NativeConstruct()
{
	Super::NativeConstruct();
	MainMenuButton->OnClicked.AddDynamic(this, &UWBP_WinMenu::OnClickedMainMenu);
	MainMenuButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_WinMenu::OnHoveredMainMenu);
	RetryButton->OnClicked.AddDynamic(this, &UWBP_WinMenu::OnClickedRetry);
	RetryButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_WinMenu::OnHoveredRetry);

	for (UWidget* Options : WinChoiceBox->GetAllChildren())
	{
		if (Options->IsA<UWBP_ButtonsNText>())
		{
			UWBP_ButtonsNText* WinChoice = Cast<UWBP_ButtonsNText>(Options);
			WinChoices.Add(WinChoice);
		}
	}

	CurrentChoice = 0;
	UpdateButtonState();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}

	GameInstance->CalculateFinalScore();

	//UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	FinalScoreText->SetText(FText::FromString(FString::FromInt(GameInstance->FinalScore)));

	//GameInstance->FinalScore;
}

void UWBP_WinMenu::OnClickedMainMenu()
{
	GameInstance->LoadMainMenu();
}

void UWBP_WinMenu::OnHoveredMainMenu()
{
	CurrentChoice = 1;
	UpdateButtonState();
}

void UWBP_WinMenu::OnClickedRetry_Implementation()
{
	GameInstance->RestartLevel();
}

void UWBP_WinMenu::OnHoveredRetry()
{
	CurrentChoice = 0;
	UpdateButtonState();
}

void UWBP_WinMenu::UpdateButtonState()
{
	for (int i = 0; i < WinChoices.Num(); i++)
	{
		if (i == CurrentChoice)
		{
			WinChoices[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
			WinChoices[i]->BackgroundButton->SetBackgroundColor(FLinearColor(0.533333f, 0.019f, 0.019f, 1.0f));
		}
		else
		{
			WinChoices[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			WinChoices[i]->BackgroundButton->SetBackgroundColor(FLinearColor(FColor::Black));
		}
	}
}

void UWBP_WinMenu::MoveChoiceUp()
{
	if (CurrentChoice > 0)
	{
		CurrentChoice--;
	}
	else
	{
		CurrentChoice = WinChoices.Num() - 1;
	}

	UpdateButtonState();
}

void UWBP_WinMenu::MoveChoiceDown()
{
	if (CurrentChoice < WinChoices.Num() - 1)
	{
		CurrentChoice++;
	}
	else
	{
		CurrentChoice = 0;
	}

	UpdateButtonState();
}

void UWBP_WinMenu::SelectChoice()
{
	switch (CurrentChoice)
	{
	case 0:
		OnClickedRetry();
		break;

	case 1:
		OnClickedMainMenu();
		break;
	}
}


