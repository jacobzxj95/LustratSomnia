// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaminaComponent.h"
#include "TimerManager.h"
#include "Runtime/Engine/Public/TimerManager.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "CoreUObject.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	Stamina = MaxStamina;

	bIsExhausted = false;
	bIsSprinting = false;
	// ...
	
}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	float RealSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	Super::TickComponent(RealSeconds, TickType, ThisTickFunction);

	FTimerHandle StaminaRegenTimer;

	if (bIsSprinting)
	{
		DrainStamina(StaminaRegenTimer, DeltaTime);
	}
	else if (!bIsSprinting && Stamina < MaxStamina)
	{
		RegenStamina(StaminaRegenTimer, DeltaTime);
	}
}

void UStaminaComponent::SetStamina(float DeltaStamina)
{
	if (bIsSprinting)
	{
		if (DeltaStamina < 0)
		{
			return;
		}
		else
		{
			Stamina = FMath::Clamp(Stamina - DeltaStamina, 0.0f, MaxStamina);
		}
	}
	else
	{
		Stamina = FMath::Clamp(Stamina - DeltaStamina, 0.0f, MaxStamina);
	}
}

void UStaminaComponent::DrainStamina(FTimerHandle StaminaRegenTimer,float deltaTime)
{
	if (StaminaRegenDelegate.IsBound())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Delegate bound"));
		StaminaRegenDelegate.Unbind();
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimer);
	}

	SetStamina(StaminaUsageRate * deltaTime);

	if (Stamina == 0)
	{
		bIsExhausted = true;
	}
}

void UStaminaComponent::RegenStamina(FTimerHandle StaminaRegenTimer, float deltaTime)
{
	if (!bIsExhausted)
	{
		if (!StaminaRegenDelegate.IsBound())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Delegate not bound"));
			StaminaRegenDelegate.BindUFunction(this, FName("SetStamina"), -StaminaRegenRate * deltaTime);
		}
		GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimer, StaminaRegenDelegate, StaminaRegenDelay, false);
	}
	else
		SetStamina(-StaminaRegenRateSlow * deltaTime);

	if (Stamina == MaxStamina)
	{
		bIsExhausted = false;
	}
}

float UStaminaComponent::GetStamina()
{
	return Stamina;
}

bool UStaminaComponent::CanSprint()
{
	return (Stamina > 0);
}

