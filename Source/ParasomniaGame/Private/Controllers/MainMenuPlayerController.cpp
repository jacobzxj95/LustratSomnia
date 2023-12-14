// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MainMenuPlayerController.h"
#include "Widgets/WBP_MainMenu.h"
#include "Widgets/WBP_HUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

AMainMenuPlayerController::AMainMenuPlayerController(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	bShowMouseCursor = true;
	bEnableTouchEvents = true;
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UWBP_MainMenu* TempMainMenuHUD = CreateWidget<class UWBP_MainMenu>(GetWorld(), MainMenuHUD);
	TempMainMenuHUD->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), TempMainMenuHUD, EMouseLockMode::LockAlways);
}
