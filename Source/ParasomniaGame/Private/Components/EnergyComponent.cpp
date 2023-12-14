// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnergyComponent.h"

// Sets default values for this component's properties
UEnergyComponent::UEnergyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEnergyComponent::AddEnergy(float _EnergyAmount)
{
	EnergyAmount += _EnergyAmount;
}

void UEnergyComponent::RemoveEnergy(float _EnergyAmount)
{
	EnergyAmount -= _EnergyAmount;
}

float UEnergyComponent::GetEnergyAmount()
{
	return EnergyAmount;
}

void UEnergyComponent::SetEnergyAmount(float _EnergyAmount)
{
	EnergyAmount = _EnergyAmount;
}


//// Called every frame
//void UEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

