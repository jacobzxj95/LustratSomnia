// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RationsComponent.h"

// Sets default values for this component's properties
URationsComponent::URationsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URationsComponent::BeginPlay()



{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URationsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URationsComponent::AddRations(int Amount)
{
	RationAmount+= Amount;
}

void URationsComponent::RemoveRations(int Amount)
{
	RationAmount-= Amount;
}

int URationsComponent::GetRations()
{
	return RationAmount;
}

void URationsComponent::SetRations(int Amount)
{
	RationAmount = Amount;
}

void URationsComponent::CheckRations()
{
	if (RationAmount < MinimumGoal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You didn't get enough rations for the night!"));
	}
	else if (RationAmount >= MinimumGoal && RationAmount < SuperGoal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You got enough rations for the night!"));
	}
	else if (RationAmount >= SuperGoal)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You got MORE than enough rations for the night!"));
	}
}

