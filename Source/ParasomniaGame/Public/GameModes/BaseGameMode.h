// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual bool AllowCheats(APlayerController* P) override;
	
};
