// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "EnergyPickup.generated.h"

/**
 * 
 */

class USoundBase;

UCLASS()
class PARASOMNIAGAME_API AEnergyPickup : public ABasePickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float EnergyAmmount;
	
public:

	float Pickup() override;


};
