// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NightSpawnPoint.h"

#include "Actors/BaseChar.h"
#include "AI/BaseAIController.h"
#include "Components/SpawnPoolComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

ANightSpawnPoint::ANightSpawnPoint() :
					SpawnRate(12.0f),
					SpawnDelay(7.5f)
{
}

void ANightSpawnPoint::SpawnNightAI()
{
	if(GetCurrSpawnAmt() < MaxSpawnAmount)
	{
		ABaseAI* Spawn = AssignedPool->PoolSpawnFromActor(this);
		FRandomStream Stream = FRandomStream(FMath::Rand());
		int Check = Stream.RandRange(1,100);
		if (Spawn && Check > 50)
		{
			Spawned();
			Cast<ABaseAIController>(Spawn->GetController())->ToggleBoolValue();
		}
	}
}

void ANightSpawnPoint::StartSpawn()
{
	FTimerHandle SpawnTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ANightSpawnPoint::SpawnNightAI, SpawnRate, true, SpawnDelay);
}

void ANightSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	ABaseChar* Player = Cast<ABaseChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	//get spawn pool form game mode
	TArray<USpawnPoolComponent*> SpawnPoolComponents; 
	UGameplayStatics::GetGameMode(this)->GetComponents<USpawnPoolComponent>(SpawnPoolComponents);
	//assign correct pool to point
	for (USpawnPoolComponent* PoolComponent : SpawnPoolComponents)
	{
		if(PoolComponent->SpawnPoolClass->IsChildOf(SpawnClass))
		{
			AssignedPool = PoolComponent;
			Player->OnNightfall.AddUniqueDynamic(this,&ANightSpawnPoint::StartSpawn);
			break;
		}
	}
}
