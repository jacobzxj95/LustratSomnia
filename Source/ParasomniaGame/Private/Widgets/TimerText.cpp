// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TimerText.h"
#include "Actors/BasePlayer.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UTimerText::NativeConstruct()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);
	PlayerRef = Cast<ABasePlayer>(FoundActors[0]);
}

void UTimerText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}


