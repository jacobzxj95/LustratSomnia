// Fill out your copyright notice in the Description page of Project Settings.


#include "Art/PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"
#include "KismetAnimationLibrary.h"


void UPlayerAnimInstance::IsRunning(bool value)
{
	bIsSprinting = value;
}

void UPlayerAnimInstance::IsCrouching(bool value)
{
	bIsCrouching = value;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner(); 
	if (Pawn) 
	{
		Speed = Pawn->GetVelocity().Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
	}
}
