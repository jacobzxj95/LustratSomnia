// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnPointSceneComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "AI/BaseAI.h"
#include "Actors/BasePickup.h"
#include "Components/SpawnPoolComponent.h"
#include "Widgets/SlideInStunHint.h"
#include "Utility/BaseGameInstance.h"
#include "RandHouse.generated.h"

UCLASS()
class PARASOMNIAGAME_API ARandHouse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandHouse();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<USpawnPointSceneComponent*> SpawnPointsWithin;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "AI")
	TArray<AActor*> SuddenTeleportPt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<ABasePickup*> PickupArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ABasePickup> PickupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class USlideInStunHint* HintHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<USlideInStunHint> HintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBaseGameInstance* GameInstance;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void Spawning();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY()
	ACharacter* Player;
	
	UPROPERTY()
	TArray<ABaseAI*> SpawnedAIArray;

	UPROPERTY()
	USpawnPoolComponent* SpawnPoolComponent;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	TMap<USpawnPointSceneComponent*,USpawnPoolComponent*> PointPoolMap;

};
