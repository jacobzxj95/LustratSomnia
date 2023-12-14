// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseChar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Controllers/BasePlayerController.h"
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "InputActionValue.h"
#include "Components/EnergyComponent.h"
#include "Widgets/WBP_PausingMenu.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Widgets/TimerText.h"
#include "Utility/BaseGameInstance.h"
#include "Widgets/PauseSettings.h"



// Sets default values
ABaseChar::ABaseChar()
{
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

	SpringArmComp->SetupAttachment(GetMesh(), FName("head"));
	CameraComp->SetupAttachment(SpringArmComp);

	EnergyComp = CreateDefaultSubobject<UEnergyComponent>(TEXT("Energy Component"));
}

// Called when the game starts or when spawned
void ABaseChar::BeginPlay()
{
	Super::BeginPlay();

	TimerMenu = CreateWidget<UTimerText>(GetWorld(), TimerClass);
	TimerMenu->AddToViewport();
	TimerMenu->SetRenderOpacity(0.0f);

	PausingMenu = CreateWidget<UWBP_PausingMenu>(GetWorld(), PausingMenuClass);
	PausingMenu->AddToViewport();
	PausingMenu->SetVisibility(ESlateVisibility::Hidden);

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			LocalPlayerSubsystem->AddMappingContext(PlayerInputContext, 0);
		}
	}

	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		const bool bShouldLoadInfo = GameInstance->bQuitThroughPause;
		const bool bIsItNightYet = GameInstance->bIsNightmare;

		if (bShouldLoadInfo && !bIsItNightYet)
		{
			Minutes = GameInstance->Minutes;
			Seconds = GameInstance->Seconds;
			GameInstance->bQuitThroughPause = false;
		}
		else if (bShouldLoadInfo && bIsItNightYet)
		{
			Minutes = NightMinutes;
			Seconds = NightSeconds;
			GameInstance->bQuitThroughPause = false;
		}
		else
		{
			Minutes = DayMinutes;
			Seconds = DaySeconds;
		}

		EnergyComp->SetEnergyAmount(GameInstance->EnergyAmountSaved);
		CellsCollected = GameInstance->EnergyCellsCollected;
		PeopleSaved = GameInstance->PeopleSaved;
	}
}

// Called every frame
void ABaseChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PausingMenu)
	{
		CheckIfPaused();
	}
	
	if (Minutes % 9 == 0 && Seconds == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle, this, &ABaseChar::DelayForTimer, 0.125f, true);
	}

	if (Minutes == 1)
	{
		GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle, this, &ABaseChar::DelayForTimer, 0.125f, true); 
	}

	if (Minutes == 0 && Seconds == 30)
	{
		GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle, this, &ABaseChar::DelayForTimer, 0.125f, true); 
	}
}

// Called to bind functionality to input
void ABaseChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &ABaseChar::MoveAction);
		EnhancedInputComponent->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &ABaseChar::CameraAction);
		EnhancedInputComponent->BindAction(IA_Action, ETriggerEvent::Triggered, this, &ABaseChar::Action);
		EnhancedInputComponent->BindAction(IA_Interaction, ETriggerEvent::Triggered, this, &ABaseChar::InteractionAction);

		EnhancedInputComponent->BindAction(IA_PrototypeHUDAction, ETriggerEvent::Triggered, this, &ABaseChar::ControllerHUDActionHeld);
		EnhancedInputComponent->BindAction(IA_PauseAction, ETriggerEvent::Triggered, this, &ABaseChar::PauseAction);

		//Menu nav bindings

		EnhancedInputComponent->BindAction(IA_PauseNavDown, ETriggerEvent::Triggered, this, &ABaseChar::PauseNavMoveDown);
		EnhancedInputComponent->BindAction(IA_PauseNavUp, ETriggerEvent::Triggered, this, &ABaseChar::PauseNavMoveUp);
		EnhancedInputComponent->BindAction(IA_PauseAccept, ETriggerEvent::Triggered, this, &ABaseChar::PauseNavAccept);
		EnhancedInputComponent->BindAction(IA_PauseReturn, ETriggerEvent::Triggered, this, &ABaseChar::PauseNavReturn);
	}
}

void ABaseChar::MoveAction(const FInputActionValue& Value) {}

void ABaseChar::CameraAction(const FInputActionValue& Value)
{
	const FVector2D CameraDirection = Value.Get<FVector2D>();

	AddControllerYawInput(CameraDirection.X);
	AddControllerPitchInput(-CameraDirection.Y);
}

void ABaseChar::Action(const FInputActionValue& Value) {}

void ABaseChar::InteractionAction(const FInputActionValue& Value) {}

void ABaseChar::PauseAction(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	
	if (!PausingMenu->IsVisible() && !PausingMenu->SettingsHUD)
	{
		PausingMenu->SetVisibility(ESlateVisibility::Visible);
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetPause(true);

		if (PausingMenu->HasAnyUserFocus())
		{
			PausingMenu->SetFocus();
		}

		PausingMenu->ButtonIndex = 0;
		PausingMenu->UpdateButtonState();
	}

	else if (PausingMenu->IsVisible())
	{
		PausingMenu->SettingsHUD = nullptr;
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PausingMenu->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->SetPause(false);
	}
}

void ABaseChar::CheckIfPaused() const {}

void ABaseChar::ControllerHUDActionHeld(const FInputActionValue& Value) {}

void ABaseChar::DelayForTimer()
{
	if (TimerMenu)
	{
		float Opacity = TimerMenu->GetRenderOpacity();
		if (bIsHudVisible == false)
		{
			Opacity = Opacity + 0.1f;
			TimerMenu->SetRenderOpacity(Opacity);
			if(Opacity >= 1.0f && Minutes > 0)
			{
				bIsHudVisible = true;
				GetWorldTimerManager().ClearTimer(OpacityTimerHandle);
				GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle, this, &ABaseChar::DelayForTimer, 0.125f, true, 10.0f); 
			}
		}
		else if (bIsHudVisible == true)
		{
			Opacity = Opacity - 0.1f;
			TimerMenu->SetRenderOpacity(Opacity);
			if(Opacity <= 0.0f)
			{
				bIsHudVisible = false;
				GetWorldTimerManager().ClearTimer(OpacityTimerHandle);
			}
		}
	}
}

void ABaseChar::PauseNavMoveDown(const FInputActionValue& Value)
{
	if (PausingMenu->IsVisible())
	{
		if (PausingMenu->ButtonIndex < PausingMenu->Buttons.Num() - 1)
		{
			PausingMenu->ButtonIndex++;
			PausingMenu->UpdateButtonState();
		}
		else
		{
			PausingMenu->ButtonIndex = 0;
			PausingMenu->UpdateButtonState();
		}
	}
}

void ABaseChar::PauseNavMoveUp(const FInputActionValue& Value)
{
	if (PausingMenu->IsVisible())
	{
		if (PausingMenu->ButtonIndex > 0)
		{
			PausingMenu->ButtonIndex--;
			PausingMenu->UpdateButtonState();
		}
		else
		{
			PausingMenu->ButtonIndex = PausingMenu->Buttons.Num() - 1;
			PausingMenu->UpdateButtonState();
		}
	}
}

void ABaseChar::PauseNavAccept(const FInputActionValue& Value)
{
	if (PausingMenu->IsVisible())
	{
		switch (PausingMenu->ButtonIndex)
		{
		case 0:
			PausingMenu->OnClickedResume();
			break;

		case 1:
			PausingMenu->OnClickedRestart();
			break;

		case 2:
			PausingMenu->OnClickedOptions();
			break;

		case 3:
			PausingMenu->OnClickedMainMenu();
			break;

		case 4:
			PausingMenu->OnClickedQuit();
			break;
		default: ;
		}
	}

	else if (PausingMenu->SettingsHUD)
	{
		switch (PausingMenu->SettingsHUD->ButtonIndex)
		{
		case 0:
		{
			PausingMenu->SettingsHUD->OnClickedAudio();
			break;
		}
		case 1:
		{
			PausingMenu->SettingsHUD->OnClickedControls();
			break;
		}
		default: ;
		}
	}
}

void ABaseChar::PauseNavReturn(const FInputActionValue& Value)
{
	if (PausingMenu->IsVisible())
	{
		PausingMenu->OnClickedResume();
	}

	else if (PausingMenu->SettingsHUD)
	{
		PausingMenu->SettingsHUD->OnClickedBack();
	}
}

void ABaseChar::CountdownTimer()
{
	if (Seconds == 0)
	{
		if (Minutes == 0)
		{
			if (Cast<ABasePlayerController>(GetController()))
			{

				if (bNightTimeMode)
				{
					if (Minutes == 0 && Seconds == 0)
					{
						bNightTimeEnd = true;
					}
				}
				else
				{
					Minutes = NightMinutes;
					Seconds = NightSeconds;
					bDayTimeEnd = true;
					bNightTimeMode = true;
					GameInstance->bIsNightmare = true;

					OnNightfall.Broadcast();
				}
			}
		}
		else
		{
			Minutes--;
			Seconds = 59;
		}
	}
	else
	{
		Seconds--;
	}

	GameInstance->Minutes = Minutes;
	GameInstance->Seconds = Seconds;
}

