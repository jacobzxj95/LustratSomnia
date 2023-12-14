// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class PARASOMNIAGAME_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Damage")
		float EnergyCost = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Damage")
		FVector CollisionSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Damage")
		USoundBase* FiringSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Damage")
		UParticleSystem* BulletHitEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting|Recharge")
		float RechargeTimer = 1.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void DestroyProjectile();

	UFUNCTION()
		virtual void OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
