// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void IsRunning(bool value);

	UFUNCTION(BlueprintCallable)
		void IsCrouching(bool value);

protected:

	//call the update animation function
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float Direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		bool bIsCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		bool bIsSprinting;
	
};
