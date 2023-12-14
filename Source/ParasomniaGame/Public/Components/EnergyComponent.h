// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnergyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARASOMNIAGAME_API UEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy")
		float EnergyAmount;

public:	

	UFUNCTION(BlueprintCallable, Category = "Energy")
		void AddEnergy(float _EnergyAmount);

	UFUNCTION(BlueprintCallable, Category = "Energy")
		void RemoveEnergy(float _EnergyAmount);

	UFUNCTION(BlueprintCallable, Category = "Energy")
		float GetEnergyAmount();

	UFUNCTION(BlueprintCallable, Category = "Energy")
		void SetEnergyAmount(float _EnergyAmount);

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
