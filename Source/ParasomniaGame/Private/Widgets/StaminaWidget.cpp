// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StaminaWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BasePlayer.h"

void UStaminaWidget::NativeConstruct()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);
	PlayerRef = Cast<ABasePlayer>(FoundActors[0]);
}
