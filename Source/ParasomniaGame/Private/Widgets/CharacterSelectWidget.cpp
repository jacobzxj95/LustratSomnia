// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CharacterSelectWidget.h"


void UCharacterSelectWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
}

void UCharacterSelectWidget::NativeConstruct()
{
	Char1Button->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnClickedChar1);
	Char1Button->BackgroundButton->OnHovered.AddDynamic(this, &UCharacterSelectWidget::OnHoveredChar1);
	Char2Button->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnClickedChar2);
	Char2Button->BackgroundButton->OnHovered.AddDynamic(this, &UCharacterSelectWidget::OnHoveredChar2);
	Char3Button->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnClickedChar3);
	Char3Button->BackgroundButton->OnHovered.AddDynamic(this, &UCharacterSelectWidget::OnHoveredChar3);
	ContinueButton->OnClicked.AddDynamic(this, &UCharacterSelectWidget::OnClickedContinue);
	ContinueButton->BackgroundButton->OnHovered.AddDynamic(this, &UCharacterSelectWidget::OnHoveredContinue);
	PlayerSlider->OnValueChanged.AddDynamic(this, &UCharacterSelectWidget::OnValueChangedSlider);

	for (UWidget* buttons : CanvasPanel->GetAllChildren())
	{
		UWBP_ButtonsNText* button = Cast<UWBP_ButtonsNText>(buttons);
		if (button)
		{
			ButtonArray.Add(button);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Button: %s"), *button->ButtonText->GetText().ToString()));
		}
	}
	UpdateButtonState();

	TArray<AActor*> Pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), Pawns);

	for (AActor* Pawn : Pawns)
	{
		CharacterPawn = Cast<ASelectionPawn>(Pawn);
		if (CharacterPawn)
		{
			CharacterPawn->SetMaterial(CharacterMaterial1);
			GameInstance->CharacterMesh = CharacterPawn->GetMesh();
			GameInstance->CharacterMaterial = CharacterPawn->GetMaterialInstance();
			break;
		}
	}
}

void UCharacterSelectWidget::OnClickedChar1()
{
	CharacterPawn->SetMaterial(CharacterMaterial1);
	GameInstance->CharacterMaterial = CharacterPawn->GetMaterialInstance();
}

void UCharacterSelectWidget::OnHoveredChar1()
{
	CurrentButtonIndex = 0;
	UpdateButtonState();
}

void UCharacterSelectWidget::OnClickedChar2()
{
	CharacterPawn->SetMaterialInstance(CharacterMaterial2);
	GameInstance->CharacterMaterial = CharacterPawn->GetMaterialInstance();
}

void UCharacterSelectWidget::OnHoveredChar2()
{
	CurrentButtonIndex = 1;
	UpdateButtonState();
}

void UCharacterSelectWidget::OnClickedChar3()
{
	CharacterPawn->SetMaterialInstance(CharacterMaterial3);
	GameInstance->CharacterMaterial = CharacterPawn->GetMaterialInstance();
}

void UCharacterSelectWidget::OnHoveredChar3()
{
	CurrentButtonIndex = 2;
	UpdateButtonState();
}

void UCharacterSelectWidget::OnValueChangedSlider(float _Value)
{
	Value = _Value * -700.f;

	CharacterPawn->SetActorRelativeRotation(FRotator(0, Value, 0));
}

void UCharacterSelectWidget::SliderLeft(float _Value)
{
	float NewValue = Value * -700.f;

	CharacterPawn->SetActorRelativeRotation(FRotator(0, NewValue, 0));
}

void UCharacterSelectWidget::OnClickedContinue()
{
	GameInstance->LoadLevelOne();
}

void UCharacterSelectWidget::OnHoveredContinue()
{
	CurrentButtonIndex = 3;
	UpdateButtonState();
}

void UCharacterSelectWidget::JustToCheckTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Timer Has Been Called... Finally")));
}

void UCharacterSelectWidget::UpdateButtonState()
{
	for (int i = 0; i < ButtonArray.Num(); i++)
	{
		if (i == CurrentButtonIndex)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Index: %d FOUND"), CurrentButtonIndex));
			ButtonArray[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			ButtonArray[i]->ButtonText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
