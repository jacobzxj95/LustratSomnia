// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePickup.h"
#include "RationsPickup.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API ARationsPickup : public ABasePickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		int RationsAmount;

public:

	float Pickup() override;
	
};
