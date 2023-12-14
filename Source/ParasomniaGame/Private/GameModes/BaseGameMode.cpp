// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BaseGameMode.h"

bool ABaseGameMode::AllowCheats(APlayerController* P)
{
	return Super::AllowCheats(P);
}
