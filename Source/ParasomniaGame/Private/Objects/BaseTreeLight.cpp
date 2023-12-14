

// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/BaseTreeLight.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ABaseTreeLight::ABaseTreeLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("PointLight"));

}

// Called when the game starts or when spawned
void ABaseTreeLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTreeLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

