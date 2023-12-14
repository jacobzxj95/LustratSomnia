// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTreeLight.generated.h"

class UPointLightComponent;
class USpotLightComponent;

UCLASS()
class PARASOMNIAGAME_API ABaseTreeLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTreeLight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
		USpotLightComponent* PointLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
