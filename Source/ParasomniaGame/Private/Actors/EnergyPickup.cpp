// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EnergyPickup.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

float AEnergyPickup::Pickup()
{
	Super::Pickup();

	UE_LOG(LogTemp, Warning, TEXT("Energy Pickup"));

	UGameplayStatics::PlaySound2D(GetWorld(), PickupSound);

	return EnergyAmmount;
}
