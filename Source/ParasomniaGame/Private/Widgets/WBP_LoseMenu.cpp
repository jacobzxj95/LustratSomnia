// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_LoseMenu.h"
#include "Widgets/WBP_ButtonsNText.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/BaseGameInstance.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UWBP_LoseMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UWBP_LoseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	RetryButton->OnClicked.AddDynamic(this, &UWBP_LoseMenu::OnClickedRetry);
	RetryButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_LoseMenu::OnHoveredRetry);

	MainMenuButton->OnClicked.AddDynamic(this, &UWBP_LoseMenu::OnClickedMainMenu);
	MainMenuButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_LoseMenu::OnHoveredMainMenu);

	QuitButton->OnClicked.AddDynamic(this, &UWBP_LoseMenu::OnClickedQuit);
	QuitButton->BackgroundButton->OnHovered.AddDynamic(this, &UWBP_LoseMenu::OnHoveredQuit);

	for (UWidget* Options : DeathChoiceBox->GetAllChildren())
	{
		if (Options->IsA<UWBP_ButtonsNText>())
		{
			DeathChoices.Add(Cast<UWBP_ButtonsNText>(Options));
		}
	}
	CurrentChoice = 0;
	UpdateButtonState();

	if (!HasAnyUserFocus())
	{
		SetFocus();
	}

	GameInstance->CalculateFinalScore();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(GameInstance->FinalScore));

	UGameplayStatics::SetGamePaused(GetWorld(), true);
	FinalScoreText->SetText(FText::FromString(FString::FromInt(GameInstance->FinalScore)));
}

void UWBP_LoseMenu::OnClickedRetry_Implementation()
{
	GameInstance->RestartLevel();
}

void UWBP_LoseMenu::OnHoveredRetry()
{
	CurrentChoice = 0;
	UpdateButtonState();
}

void UWBP_LoseMenu::OnClickedMainMenu()
{
	GameInstance->LoadMainMenu();
}

void UWBP_LoseMenu::OnHoveredMainMenu()
{
	CurrentChoice = 1;
	UpdateButtonState();
}

void UWBP_LoseMenu::OnClickedQuit()
{
	GameInstance->RestartLevel();
	GameInstance->Quit();
}

void UWBP_LoseMenu::OnHoveredQuit()
{
	CurrentChoice = 2;
	UpdateButtonState();
}

void UWBP_LoseMenu::UpdateButtonState()
{
	for (int i = 0; i < DeathChoices.Num(); i++)
	{
		if (i == CurrentChoice)
		{
			//set the background button of the current choice to be yellow
			//DeathChoices[i]->BackgroundButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
			DeathChoices[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
			DeathChoices[i]->BackgroundButton->SetBackgroundColor(FLinearColor(0.533333f, 0.019f, 0.019f, 1.0f));
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Choice: %d"), CurrentChoice));
		}
		else
		{
			//set the color to be white
			//DeathChoices[i]->BackgroundButton->SetBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			DeathChoices[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			DeathChoices[i]->BackgroundButton->SetBackgroundColor(FLinearColor(FColor::Black));
		}
	}
}

void UWBP_LoseMenu::MoveDownArray()
{
	if (CurrentChoice < DeathChoices.Num() - 1)
	{
		CurrentChoice++;
	}
	else
	{
		CurrentChoice = 0;
	}
	UpdateButtonState();
}

void UWBP_LoseMenu::MoveUpArray()
{
	if (CurrentChoice > 0)
	{
		CurrentChoice--;
	}
	else
	{
		CurrentChoice = DeathChoices.Num() - 1;
	}
	UpdateButtonState();
}

void UWBP_LoseMenu::SelectChoice()
{
	switch (CurrentChoice)
	{
	case 0:
		OnClickedRetry();
		break;

	case 1:
		OnClickedMainMenu();
		break;

	case 3:
		OnClickedQuit();
		break;
	}
}
