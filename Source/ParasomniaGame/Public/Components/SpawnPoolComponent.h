// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "Components/ActorComponent.h"
#include "SpawnPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARASOMNIAGAME_API USpawnPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoolComponent();

	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
	ABaseAI* PoolSpawnFromActor(AActor* SpawnPoint);
	
	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
	ABaseAI* PoolSpawnFromComponent(USceneComponent* SpawnPoint);

	UFUNCTION()
	void OnDespawn(ABaseAI* AIActor);

	UFUNCTION()
	void GetSpawnPool(TArray<ABaseAI*>& OutSpawnPool) const;
	
	UPROPERTY(EditAnywhere, Category = "SpawnPool")
	TSubclassOf<ABaseAI> SpawnPoolClass;
	
	UPROPERTY(EditAnywhere, Category = "SpawnPool")
	int PoolSize;

	

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<ABaseAI*> SpawnPool;
	
	UPROPERTY()
	TMap<int, ABaseAI*> SpawnedActive;
};
