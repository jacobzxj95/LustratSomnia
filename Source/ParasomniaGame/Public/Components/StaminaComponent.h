// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARASOMNIAGAME_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStaminaComponent(); 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		float StaminaRegenRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		float StaminaRegenRateSlow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		float StaminaUsageRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		float StaminaRegenDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		float StaminaRegenDelaySlow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		bool bIsExhausted;

	FLatentActionInfo LatentInfo;

	/*FTimerHandle StaminaRegenTimer;*/
	FTimerDelegate StaminaRegenDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Function")
		void SetStamina(float DeltaStamina);

	UFUNCTION(BlueprintCallable, Category = "Function")
		void DrainStamina(FTimerHandle StaminaRegenTimer, float delta);

	UFUNCTION(BlueprintCallable, Category = "Function")
		void RegenStamina(FTimerHandle StaminaRegenTimer, float delta);

	UFUNCTION(BlueprintCallable, Category = "Function")
		float GetStamina();

	UFUNCTION(BlueprintCallable, Category = "Function")
		bool CanSprint();
};
