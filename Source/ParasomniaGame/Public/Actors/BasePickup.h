// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PickupInterface.h"
#include "BasePickup.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UPrimitiveComponent;
class AActor;
class UWBP_PickupTextDisplay;

UCLASS()
class PARASOMNIAGAME_API ABasePickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		UStaticMeshComponent* OutlineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		USphereComponent* PickupCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		USphereComponent* OutlineCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<UWBP_PickupTextDisplay> PickupHUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hud")
		UWBP_PickupTextDisplay* PickupHUD;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void OutlineStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void OutlineEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void PickupStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void PickupEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual float Pickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		USoundBase* PickupSound;

};
