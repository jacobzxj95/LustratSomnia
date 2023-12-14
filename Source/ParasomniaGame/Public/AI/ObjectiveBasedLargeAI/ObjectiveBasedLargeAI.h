#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Actors/BaseProjectile.h>
#include "ObjectiveBasedLargeAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API AObjectiveBasedLargeAI : public ABaseAI
{
	GENERATED_BODY()

public:

	AObjectiveBasedLargeAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UStaticMeshComponent* ShootingSpot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UChildActorComponent* ChildActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class AActor* Objective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<AActor> ObjectiveClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float InterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float WeaknessDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		int WeaknessHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		int HitsToDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool WeaknessSpawned;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<USoundBase*> StunSounds;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void WeaknessSpawn();

	UFUNCTION()
		void MoveWeakness();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Dead() override;
};