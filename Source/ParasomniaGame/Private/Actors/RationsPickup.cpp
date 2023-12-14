// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RationsPickup.h"
#include <Kismet/GameplayStatics.h>

float ARationsPickup::Pickup()
{
	Super::Pickup();

	UGameplayStatics::PlaySound2D(GetWorld(), PickupSound);

	return (float)RationsAmount;
}
