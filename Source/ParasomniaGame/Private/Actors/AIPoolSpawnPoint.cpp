// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AIPoolSpawnPoint.h"


AAIPoolSpawnPoint::AAIPoolSpawnPoint() :
					SpawnChance(75),
					CanSpawn(true),
					MaxSpawnAmount(1)
{
}

bool AAIPoolSpawnPoint::SetSpawnCheck()
{
	FRandomStream Stream = FRandomStream(FMath::Rand());
	int Check = Stream.RandRange(1,100);

	return CanSpawn = (SpawnChance >= Check);
}

bool AAIPoolSpawnPoint::GetSpawnCheck() const
{
	return CanSpawn;
}

int AAIPoolSpawnPoint::GetCurrSpawnAmt() const
{
	return CurrSpawnAmount;
}

void AAIPoolSpawnPoint::Spawned()
{
	CurrSpawnAmount++;
}

void AAIPoolSpawnPoint::Reset()
{
	CurrSpawnAmount = 0;
	CanSpawn = true;
}
