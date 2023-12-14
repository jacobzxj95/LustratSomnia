// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weakness.generated.h"

UCLASS()
class PARASOMNIAGAME_API AWeakness : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeakness();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UStaticMeshComponent* Mesh;
};
