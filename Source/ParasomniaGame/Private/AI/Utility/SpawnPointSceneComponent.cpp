// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Utility/SpawnPointSceneComponent.h"

// Sets default values for this component's properties
USpawnPointSceneComponent::USpawnPointSceneComponent() :
					SpawnChance(75),
					CanSpawn(true),
					MaxSpawnAmount(1)
{}

bool USpawnPointSceneComponent::SetSpawnCheck()
{
	FRandomStream Stream = FRandomStream(FMath::Rand());
	int Check = Stream.RandRange(1,100);

	return CanSpawn = (SpawnChance >= Check);
}

bool USpawnPointSceneComponent::GetSpawnCheck() const
{
	return CanSpawn;
}

int USpawnPointSceneComponent::GetCurrSpawnAmt() const
{
	return CurrSpawnAmount;
}

void USpawnPointSceneComponent::Spawned()
{
	CurrSpawnAmount++;
}

void USpawnPointSceneComponent::Reset()
{
	CurrSpawnAmount = 0;
	CanSpawn = true;
}



