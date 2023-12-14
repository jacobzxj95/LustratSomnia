


// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CharacterSelectController.h"
#include "Widgets/CharacterSelectWidget.h"

void ACharacterSelectController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	CharacterSelectWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), CharacterSelectHUD);
	CharacterSelectWidget->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), CharacterSelectWidget, EMouseLockMode::LockAlways);
}
