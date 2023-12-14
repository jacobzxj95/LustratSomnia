// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseSentry.h"
#include "Components/BoxComponent.h"
#include "Actors/BasePlayer.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/EnergyComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Widgets/WBP_TestHUD.h"
#include "Widgets/WBP_TestTurretHUD.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Actors/BaseProjectile.h"
#include "Widgets/MountTurretText.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/WBP_Turret.h"
#include "Components/ProgressBar.h"
#include "EnhancedInputComponent.h" 
#include "EnhancedInputSubsystems.h" 
#include "InputActionValue.h"
#include "Widgets/StaminaWidget.h"
#include "Widgets/CollectionHUD.h"
#include "Widgets/FlashWidget.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

 
ABaseSentry::ABaseSentry()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);

	SpringArmComp->SetupAttachment(GetMesh(), "New_Turret_Head");
	CameraComp->SetupAttachment(SpringArmComp);
}

void ABaseSentry::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABasePlayer* Player = Cast<ABasePlayer>(OtherActor);
	if (Player)
	{
		MountHUD->SetVisibility(ESlateVisibility::Visible);
		Player->bIsNearSentry = true;
	}
}

void ABaseSentry::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABasePlayer* Player = Cast<ABasePlayer>(OtherActor);
	if (Player)
	{
		MountHUD->SetVisibility(ESlateVisibility::Hidden);
		Player->bIsNearSentry = false;
		
	}
}

void ABaseSentry::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseSentry::OnBoxBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ABaseSentry::OnBoxEndOverlap);

	GetCapsuleComponent()->SetWorldLocation(PlayerPositions[0]);
	LocationIndex = 0;

	ProjectileIndex = 0;
	ProjectileClass = ProjectileClassArray[ProjectileIndex];

	bCanShoot = true;

	MountHUD = CreateWidget<UMountTurretText>(GetWorld(), MountHUDClass);
	MountHUD->AddToViewport();
	MountHUD->SetVisibility(ESlateVisibility::Hidden);
}

void ABaseSentry::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_BulletSwap, ETriggerEvent::Triggered, this, &ABaseSentry::ChangeBullet);
	}

}

void ABaseSentry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMovingRight || bIsMovingLeft)
	{
		MoveSentry(DeltaTime, bIsMovingRight, bIsMovingLeft);
	}

	if (bMovedIntoSentry)
	{

		if (!TurretControlsHUD)
		{
			TurretControlsHUD = CreateWidget<UWBP_TestTurretHUD>(GetWorld(), TurretControlsHUDClass);
			TurretControlsHUD->AddToViewport();
		}

		if (!TurretHUD)
		{
			if (PlayerController)
			{
				TurretHUD = CreateWidget<UWBP_Turret>(GetWorld()/*PlayerController*/, TurretHUDClass);
				TurretHUD->AddToViewport();
				TurretHUD->EnergyBar->SetPercent(CurrMaxEnergy/CurrMaxEnergy);
			}
		}
	}

	if (bMovedIntoSentry && MountHUD->IsVisible())
	{
		MountHUD->RemoveFromParent();
	}

	if (TurretHUD)
	{
		if (CurrMaxEnergy == 0)
			TurretHUD->EnergyBar->SetPercent(0);
		else
			TurretHUD->EnergyBar->SetPercent(EnergyComp->GetEnergyAmount() / CurrMaxEnergy);
	}
}

void ABaseSentry::MoveAction(const FInputActionValue& Value)
{
	const FVector2D MoveDirection = Value.Get<FVector2D>();
	
	if (!bIsMovingLeft && (MoveDirection.X > 0 && !bIsMovingRight))
	{
		bIsMovingRight = true;
		bStartMovement = true;
	}
	else if (!bIsMovingRight && (MoveDirection.X < 0 && !bIsMovingLeft))
	{
		bIsMovingLeft = true;
		bStartMovement = true;
	}
	
}

void ABaseSentry::CameraAction(const FInputActionValue& Value)
{
	Super::CameraAction(Value);
}

void ABaseSentry::MoveSentry(float DeltaTime, bool rightMovement, bool leftMovement)
{
	if (bStartMovement)
	{
		if (bIsMovingRight)
		{
			if (LocationIndex < 3 && bStartMovement)
			{
				LocationIndex++;
			}
			else if (LocationIndex >= 3 && bStartMovement)
			{
				LocationIndex = 0;
			}
		}
		else if (bIsMovingLeft)
		{
			if (LocationIndex > 0 && bStartMovement)
			{
				LocationIndex--;
			}
			else if (LocationIndex <= 0 && bStartMovement)
			{
				LocationIndex = 3;
			}
		}

		bStartMovement = false;
	}

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = PlayerPositions[LocationIndex];
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, 1.5f);
	SetActorLocation(FVector(NewLocation.X, NewLocation.Y, CurrentLocation.Z));

	if (FMath::Abs(CurrentLocation.Y - TargetLocation.Y) < 0.3f || FMath::Abs(CurrentLocation.X - TargetLocation.X) < 0.3f)
	{
		SetActorLocation(TargetLocation);
		PlayerRef->GetCapsuleComponent()->SetWorldLocation(FVector(TargetLocation.X, TargetLocation.Y, TargetLocation.Z + 50.f));
		bIsMovingRight = false;
		bIsMovingLeft = false;

		if (MountHUD->IsVisible())
		{
			MountHUD->RemoveFromParent();
		}
	}
}

void ABaseSentry::ChangeBullet()
{
	if (ProjectileIndex < ProjectileClassArray.Num() - 1)
	{
		ProjectileIndex++;
	}
	else
	{
		ProjectileIndex = 0;
	}

	ProjectileClass = ProjectileClassArray[ProjectileIndex];
}

void ABaseSentry::ControllerHUDActionHeld(const FInputActionValue& Value)
{
	
	if (TurretControlsHUD->IsVisible())
	{
		TurretControlsHUD->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TurretControlsHUD->SetVisibility(ESlateVisibility::Visible);
	}	
}

void ABaseSentry::ResetShoot()
{
	bCanShoot = true;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GetActorLocation());
}

void ABaseSentry::Action(const FInputActionValue& Value)
{
	if (EnergyComp->GetEnergyAmount() > 0)
	{
		if (bCanShoot)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = this;

			ABaseProjectile* Bullet = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, GetMesh()->GetSocketLocation(BarrelSocketName),
				GetBaseAimRotation(), SpawnParams);
			if (Bullet)
			{
				EnergyComp->RemoveEnergy(Bullet->EnergyCost);
				GameInstance->EnergyAmountSaved = EnergyComp->GetEnergyAmount();

				RechargeTime = Bullet->RechargeTimer;
				bCanShoot = false;
				FTimerHandle ShootTimer;
				GetWorldTimerManager().SetTimer(ShootTimer, this, &ABaseSentry::ResetShoot, RechargeTime, false);
			}
		}
	}
}

void ABaseSentry::InteractionAction(const FInputActionValue& Value)
{
	TArray<AActor*> OverlappingActors;

	BoxComp->GetOverlappingActors(OverlappingActors, ABasePlayer::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		ABasePlayer* Player = Cast<ABasePlayer>(Actor);
		if (Player)
		{
			TurretControlsHUD->SetVisibility(ESlateVisibility::Collapsed);

			//TurretHUD->SetVisibility(ESlateVisibility::Collapsed);
			TurretHUD->RemoveFromParent();
			TurretHUD = nullptr;

			GetController()->Possess(Player);
			PlayerController->Possess(Player);
			Player->GetMesh()->SetVisibility(true);
			Player->SpotLightComp->SetVisibility(false);

			Player->GetCapsuleComponent()->SetWorldLocation(FVector(previousPlayerX, previousPlayerY, previousPlayerZ));

			Player->bMovedIntoPlayer = true;

			Player->EnergyComp->SetEnergyAmount(EnergyComp->GetEnergyAmount());

			bMovedIntoSentry = false;

			bIsSentryMode = false;

			Player->CollectionHUD->SetVisibility(ESlateVisibility::Visible);
			Player->StaminaHUD->SetVisibility(ESlateVisibility::Visible);
			Player->FlashHUD->SetVisibility(ESlateVisibility::Visible);
			
			GetCapsuleComponent()->SetWorldRotation(FRotator(0.f, GetMesh()->GetComponentRotation().Yaw, 0.f));
			
		}
	}
}

