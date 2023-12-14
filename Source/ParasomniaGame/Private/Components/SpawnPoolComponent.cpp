// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpawnPoolComponent.h"

#include "AI/BaseAIController.h"

// Sets default values for this component's properties
USpawnPoolComponent::USpawnPoolComponent()
{
}

ABaseAI* USpawnPoolComponent::PoolSpawnFromActor(AActor* SpawnPoint)
{
	for (ABaseAI* Spawn : SpawnPool)
	{
		if (Spawn->IsValidLowLevel())
		{
			AController* Controller = Spawn->GetController();
			ABaseAIController* BaseAIC = Cast<ABaseAIController>(Controller);
			if(BaseAIC && BaseAIC->IsByPlayer == false)
			{
				Spawn->TeleportTo(SpawnPoint->GetActorLocation(),SpawnPoint->GetActorRotation());
				Spawn->SetActorHiddenInGame(false);
				Spawn->SetActorEnableCollision(true);
				Spawn->SetActorTickEnabled(true);

				return Spawn;
			}
		}
	}
	
	return nullptr;
}

ABaseAI* USpawnPoolComponent::PoolSpawnFromComponent(USceneComponent* SpawnPoint)
{
	for (ABaseAI* Spawn : SpawnPool)
	{
		if (Spawn->IsValidLowLevel())
		{
			AController* Controller = Spawn->GetController();
			ABaseAIController* BaseAIC = Cast<ABaseAIController>(Controller);
			if(BaseAIC && BaseAIC->IsByPlayer == false)
			{
				Spawn->TeleportTo(SpawnPoint->GetComponentLocation(),SpawnPoint->GetComponentRotation());
				Spawn->SetActorHiddenInGame(false);
				Spawn->SetActorEnableCollision(true);
				Spawn->SetActorTickEnabled(true);

				return Spawn;
			}
		}
	}
	
	return nullptr;
}

void USpawnPoolComponent::OnDespawn(ABaseAI* AIActor)
{
}

void USpawnPoolComponent::GetSpawnPool(TArray<ABaseAI*>& OutSpawnPool) const
{
	OutSpawnPool = SpawnPool;
}

// Called when the game starts
void USpawnPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (SpawnPoolClass != nullptr)
	{
		UWorld* World = GetWorld();
		
		for (int i = 0; i <= PoolSize; i++)
		{
			ABaseAI* SpawnedActor = World->SpawnActor<ABaseAI>(SpawnPoolClass, FVector(100,0,100), FRotator().ZeroRotator);

			if(SpawnedActor != nullptr)
			{
				SpawnedActor->SetActorHiddenInGame(true);
				SpawnedActor->SetActorEnableCollision(false);
				SpawnedActor->SetActorTickEnabled(false);
				SpawnPool.Emplace(SpawnedActor);
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Invalid Spawn Class for Spawn Component!"));
	}
	
}


