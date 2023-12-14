// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BasePlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widgets/WBP_WinMenu.h"

ABasePlayerController::ABasePlayerController(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABasePlayerController::BeginPlay()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
}

void ABasePlayerController::WinMenuControllerSetup()
{
	UWBP_WinMenu* HUD = CreateWidget<class UWBP_WinMenu>(GetWorld(), WinHUD);
	
	if (HUD)
	{
		bShowMouseCursor = true;
		HUD->AddToViewport();
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), HUD, EMouseLockMode::LockAlways);
	}
}

void ABasePlayerController::WinMenuControllerTeardown()
{
	
}
