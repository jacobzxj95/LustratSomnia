// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/BasePlayer.h"
#include "BaseLadder.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class PARASOMNIAGAME_API ABaseLadder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseLadder();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ladder")
		UStaticMeshComponent* LadderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ladder")
		UBoxComponent* LadderBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ladder")
		UArrowComponent* LadderArrow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex);

};
