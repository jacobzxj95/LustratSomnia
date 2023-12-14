#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AIBullet.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIBullet : public AActor
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:	

	AAIBullet();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float DespawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float RotateRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float ScaleRate;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void DestroyAfterTimer();
};
