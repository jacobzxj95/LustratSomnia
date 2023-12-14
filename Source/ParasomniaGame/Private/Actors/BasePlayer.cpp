

// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "Actors/BaseSentry.h"
#include "Actors/BasePickup.h"
#include "Actors/RationsPickup.h"
#include "Actors/EnergyPickup.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerInput.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Art/PlayerAnimInstance.h"
#include "Components/SpotLightComponent.h"
#include "Components/EnergyComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaminaComponent.h"
#include "Components/RationsComponent.h"
#include "Widgets/WBP_HUD.h"
#include "Widgets/WBP_TestHUD.h"
#include "Widgets/WBP_PickupTextDisplay.h"
#include "Widgets/MountTurretText.h"
#include "Widgets/CollectionHUD.h"
#include "Widgets/StaminaWidget.h"
#include "Components/ProgressBar.h"
#include "Widgets/FlashWidget.h"
#include "AI/HumanAI/HumanAI.h"
#include "Components/TextBlock.h"
#include "Widgets/WBP_TestTurretHUD.h"
#include "Widgets/WBP_Turret.h"
#include "Controllers/BasePlayerController.h"
#include "Widgets/TimerText.h"

/*Code shared by another classmate. Good thing to write down:

	DefaultHUD = CreateWidget<UWBP_HUD>(GetWorld(), HUDClass);
	DefaultHUD = DefaultHUD == nullptr ? CreateWidget<UWBP_HUD>(GetWorld(), HUDClass) : DefaultHUD;
	DefaultHUD->AddToViewport();
*/

ABasePlayer::ABasePlayer()
{
	SpotLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light Component"));
	SpotLightComp->SetupAttachment(CameraComp);

	SecondLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("Second Spot Light Component"));
	SecondLightComp->SetupAttachment(SpotLightComp);

	LightHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Light Hit Box"));
	LightHitBox->SetupAttachment(SpotLightComp);

	LightHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StaminaComp = CreateDefaultSubobject<UStaminaComponent>(TEXT("Stamina Component"));
	RationsComp = CreateDefaultSubobject<URationsComponent>(TEXT("Rations Component"));

	bIsNearSentry = false;
	bIsAttacking = false;
	bLightOn = false;
	bUpdatedPickupHUD = false;
	SkippedToNight = false;
	PressedOnce = false;
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();

	bDayTimeEnd = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	SpotLightComp->SetVisibility(false);

	ControlsHUD = CreateWidget<UWBP_TestHUD>(GetWorld(), ControllerHUDClass);

	ControlsHUD->AddToViewport();

	CollectionHUD = CreateWidget<UCollectionHUD>(GetWorld(), CollectionHUDClass);
	CollectionHUD->AddToViewport();

	StaminaHUD = CreateWidget<UStaminaWidget>(GetWorld(), StaminaHUDClass);
	StaminaHUD->AddToViewport();

	FlashHUD = CreateWidget<UFlashWidget>(GetWorld(), FlashHUDClass);
	FlashHUD->AddToViewport();
	FlashHUD->FlashBar->SetPercent(100);

	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GetMesh()->SetMaterial(0, GameInstance->CharacterMaterial);
		RationsComp->SetRations(GameInstance->RationsSaved);
		RationsCollected = GameInstance->RationsSaved;
	}
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ABasePlayer::SprintAction);
		EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ABasePlayer::ReleaseSprintAction);
		EnhancedInputComponent->BindAction(IA_ToggleSprint, ETriggerEvent::Triggered, this, &ABasePlayer::ToggleSprint);

		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &ABasePlayer::CrouchAction);
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &ABasePlayer::ReleaseCrouchAction);
		EnhancedInputComponent->BindAction(IA_ToggleCrouch, ETriggerEvent::Triggered, this, &ABasePlayer::CrouchFunctionality);

		EnhancedInputComponent->BindAction(IA_Light, ETriggerEvent::Triggered, this, &ABasePlayer::LightAction);
	}
}

void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMovedIntoPlayer)
	{
		ControlsHUD->SetVisibility(ESlateVisibility::Visible);
		bMovedIntoPlayer = false;
	}

	if (GetCharacterMovement()->GetCurrentAcceleration().Size() > 0)
	{
		bIsMoving = true;
	}
	else
	{
		bIsMoving = false;
	}

	StaminaHUD->StaminaBar->SetPercent(StaminaComp->GetStamina() / StaminaComp->MaxStamina);

	bToggleCrouch = GameInstance->bIsCrouchChecked;
	bToggleSprint = GameInstance->bIsSprintChecked;

	if ((bIsSprinting && GetCharacterMovement()->Velocity.Size() <= WalkSpeed)
		|| (bIsSprinting && StaminaComp->GetStamina() <= 0)
		|| (FVector::DotProduct(GetActorForwardVector(), GetCharacterMovement()->Velocity.GetSafeNormal()) < 0 && bIsSprinting))
	{
		SprintFunctionality(false);
	}

	if (bUpdatedPickupHUD)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasePlayer::ResetHUDColor, PickupHUDTimer, false);
	}
}

void ABasePlayer::OnAttack()
{
	FlashHUD->FlashBar->SetPercent(0);
	FTimerHandle LightTimer;
	GetWorldTimerManager().SetTimer(LightTimer, this, &ABasePlayer::ChangeFlashColor, 0.1f, false, 0.5f);
	GetWorldTimerManager().SetTimer(EndTimerHandle, this, &ABasePlayer::OnEndAttack, 0.1f, true, 0.5f);
}

void ABasePlayer::OnEndAttack()
{
	FlashCoolDown = FlashCoolDown + 2.5f;
	FlashHUD->FlashBar->SetPercent(FlashCoolDown / 100);

	if(FlashCoolDown >= 100)
	{
		bOnCooldown = false;
		UGameplayStatics::PlaySound2D(GetWorld(), CoolDownSound[FMath::RandRange(0, CoolDownSound.Num()-1)]);
		GetWorldTimerManager().ClearTimer(EndTimerHandle);
	}
}

void ABasePlayer::MoveAction(const FInputActionValue& Value)
{
	const FVector2D MoveDirection = Value.Get<FVector2D>();

	if (bOnLadder)
	{
		if (GetMovementComponent()->IsMovingOnGround())
			AddMovementInput(GetActorRightVector(), MoveDirection.X);

		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		AddMovementInput(GetActorUpVector(), MoveDirection.Y);
	}
	else
	{
		AddMovementInput(GetActorForwardVector(), MoveDirection.Y);
		AddMovementInput(GetActorRightVector(), MoveDirection.X);
	}
}

void ABasePlayer::SprintAction(const FInputActionValue& Value)
{
	if (!bToggleSprint)
		SprintFunctionality(Value.Get<bool>());
}

void ABasePlayer::ReleaseSprintAction(const FInputActionValue& Value)
{
	if (!bToggleSprint)
		SprintFunctionality(Value.Get<bool>());
}

void ABasePlayer::CrouchFunctionality(const FInputActionValue& Value)
{
	if (bToggleCrouch)
	{
		if (!bIsCrouching)
		{
			if (bIsSprinting)
			{
				SprintFunctionality(false);
			}

			GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
			GetCapsuleComponent()->SetCapsuleHalfHeight(60.0f);
			PlayerAnimInstance->IsCrouching(true);
			bIsCrouching = true;
		}
		else if (bIsCrouching)
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
			GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
			PlayerAnimInstance->IsCrouching(false);
			bIsCrouching = false;
		}
	}
}

void ABasePlayer::CrouchAction(const FInputActionValue& Value)
{
	if (!bToggleCrouch)
	{
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(60.0f);
		PlayerAnimInstance->IsCrouching(true);
		bIsCrouching = true;
	}
}

void ABasePlayer::ReleaseCrouchAction(const FInputActionValue& Value)
{
	if (!bToggleCrouch)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
		PlayerAnimInstance->IsCrouching(false);
		bIsCrouching = false;
	}
}

void ABasePlayer::SprintFunctionality(bool IsPressed)
{
	if (bIsMoving && !bIsCrouching)
	{
		if (IsPressed && !StaminaComp->bIsExhausted && StaminaComp->CanSprint())
		{
			StartSprint();
		}
		else if (IsPressed && !StaminaComp->CanSprint())
		{
			StaminaComp->bIsExhausted = true;
			StopSprint();
		}
		else if (!IsPressed)
		{
			StopSprint();
		}
	}
}

void ABasePlayer::ToggleSprint(const FInputActionValue& Value)
{
	if (bToggleSprint)
	{
		if (!bIsSprinting)
		{
			SprintFunctionality(true);
		}
		else if (bIsSprinting)
		{
			SprintFunctionality(false);
		}
	}
}

void ABasePlayer::StartSprint()
{
	StaminaComp->bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	PlayerAnimInstance->IsRunning(true);
	bIsSprinting = true;
	
}

void ABasePlayer::StopSprint()
{
	StaminaComp->bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	PlayerAnimInstance->IsRunning(false);
	bIsSprinting = false;
}

void ABasePlayer::LightAction(const FInputActionValue& Value)
{
	bool bIsLightOn = SpotLightComp->IsVisible();
	SpotLightComp->SetVisibility(!bIsLightOn);
	bLightOn = !bIsLightOn;
}

void ABasePlayer::InteractionAction(const FInputActionValue& Value)
{
	TArray<AActor*> OverlappingActors;

	if (!bIsNearSentry)
	{
		GetOverlappingActors(OverlappingActors, PickupClass);

		for (AActor* Actor : OverlappingActors)
		{
			ABasePickup* Pickup = Cast<ABasePickup>(Actor);
			if (Pickup->IsA<AEnergyPickup>())
			{
				EnergyComp->AddEnergy(Pickup->Pickup());
				GameInstance->EnergyAmountSaved = EnergyComp->GetEnergyAmount();
				CellsCollected++;
				GameInstance->EnergyCellsCollected = CellsCollected;
				CollectionHUD->CurrentEnergyObjective->SetColorAndOpacity(UpdatePickupHUDColor);
				CollectionHUD->EnergyGoal->SetColorAndOpacity(UpdatePickupHUDColor);
				bUpdatedPickupHUD = true;
			}
			else if (Pickup->IsA<ARationsPickup>())
			{
				RationsComp->AddRations((int)Pickup->Pickup());
				GameInstance->RationsSaved = RationsComp->GetRations();
				RationsCollected++;
				GameInstance->RationsSaved = RationsCollected;
				CollectionHUD->CurrentRationsObjective->SetColorAndOpacity(UpdatePickupHUDColor);
				CollectionHUD->RationsGoal->SetColorAndOpacity(UpdatePickupHUDColor);
				bUpdatedPickupHUD = true;
			}
		}

		GetOverlappingActors(OverlappingActors, AHumanAI::StaticClass());
		for (AActor* Actor : OverlappingActors)
		{
			AHumanAI* HumanAI = Cast<AHumanAI>(Actor);
			if (HumanAI && !HumanAI->bInteractedByPlayer)
			{
				HumanAI->ToggleBool();
				PeopleSaved++;
				GameInstance->PeopleSaved++;
				CollectionHUD->CurrentPeopleObjective->SetColorAndOpacity(UpdatePickupHUDColor);
				CollectionHUD->PeopleGoal->SetColorAndOpacity(UpdatePickupHUDColor);
				bUpdatedPickupHUD = true;
			}
		}
		
		
	}
	else if (bIsNearSentry && bNightTimeMode)
	{
		GetOverlappingActors(OverlappingActors, ABaseSentry::StaticClass());

		for (AActor* Actor : OverlappingActors)
		{
			ABaseSentry* Sentry = Cast<ABaseSentry>(Actor);
			if (Sentry)
			{
				ControlsHUD->RemoveFromParent();

				GetCharacterMovement()->StopMovementImmediately();
				GetController()->Possess(Sentry);
				GetMesh()->SetVisibility(false);

				Sentry->previousPlayerX = GetCapsuleComponent()->GetComponentLocation().X;
				Sentry->previousPlayerY = GetCapsuleComponent()->GetComponentLocation().Y;
				Sentry->previousPlayerZ = GetCapsuleComponent()->GetComponentLocation().Z;

				GetCapsuleComponent()->SetWorldLocation(FVector(GetCapsuleComponent()->GetComponentLocation().X, GetCapsuleComponent()->GetComponentLocation().Y, GetCapsuleComponent()->GetComponentLocation().Z + 100.0f));
				SpotLightComp->SetVisibility(false);

				Sentry->MountHUD->SetVisibility(ESlateVisibility::Hidden);

				Sentry->EnergyComp->SetEnergyAmount(EnergyComp->GetEnergyAmount());
				Sentry->CurrMaxEnergy = EnergyComp->GetEnergyAmount();

				Sentry->bMovedIntoSentry = true;
				bMovedIntoPlayer = false;
				bIsSentryMode = true;

				CollectionHUD->SetVisibility(ESlateVisibility::Hidden);
				StaminaHUD->SetVisibility(ESlateVisibility::Hidden);
				FlashHUD->SetVisibility(ESlateVisibility::Hidden);

				/*if (Sentry->TurretControlsHUD)
				{
					Sentry->TurretControlsHUD->SetVisibility(ESlateVisibility::Visible);
				}

				if (Sentry->TurretHUD)
				{
					Sentry->TurretHUD->SetVisibility(ESlateVisibility::Visible);
					Sentry->TurretHUD->EnergyBar->SetPercent(Sentry->CurrMaxEnergy / Sentry->CurrMaxEnergy);
				}*/

				if (!Sentry->PlayerRef)
				{
					Sentry->PlayerRef = this;
				}

				if (!Sentry->PlayerController)
				{
					ABasePlayerController* PC = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
					if (PC)
					{
						Sentry->PlayerController = PC;
					}
				}
			}
		}
	}
	else if (bIsNearSentry && !bNightTimeMode)
	{
		if (!SkippedToNight && !PressedOnce)
		{
			SkippedToNight = true;
			PressedOnce = true;
		}
	}
}

void ABasePlayer::Action(const FInputActionValue& Value)
{
	if (bLightOn && !bOnCooldown)
	{
		SpotLightComp->SetLightColor(AttackLightColor);
		LightHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		TArray<AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors, ABaseAI::StaticClass());

		for (AActor* Actor : OverlappingActors)
		{
			ABaseAI* HuntPlayerAI = Cast<ABaseAI>(Actor);
			if (HuntPlayerAI)
			{
				HuntPlayerAI->bGotLit = true;
			}
		}

		UGameplayStatics::PlaySound2D(GetWorld(), AttackSound);

		bIsAttacking = true;

		bOnCooldown = true;

		LightHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FlashCoolDown = 0;
		OnAttack();
	}
}

void ABasePlayer::ControllerHUDActionHeld(const FInputActionValue& Value)
{
	if (ControlsHUD)
	{
		if (ControlsHUD->IsVisible())
			ControlsHUD->RemoveFromParent();
		else
			ControlsHUD->AddToViewport();
	}
}

void ABasePlayer::SetMesh(USkeletalMesh* _Mesh)
{
	GetMesh()->SetSkeletalMesh(_Mesh);
}

void ABasePlayer::ChangeFlashColor()
{
	SpotLightComp->SetLightColor(LightColor);
}

void ABasePlayer::ResetHUDColor()
{
	CollectionHUD->CurrentEnergyObjective->SetColorAndOpacity(DefaultHUDColor);
	CollectionHUD->EnergyGoal->SetColorAndOpacity(DefaultHUDColor);
	CollectionHUD->CurrentRationsObjective->SetColorAndOpacity(DefaultHUDColor);
	CollectionHUD->RationsGoal->SetColorAndOpacity(DefaultHUDColor);
	CollectionHUD->CurrentPeopleObjective->SetColorAndOpacity(DefaultHUDColor);
	CollectionHUD->PeopleGoal->SetColorAndOpacity(DefaultHUDColor);
	bUpdatedPickupHUD = false;

}
