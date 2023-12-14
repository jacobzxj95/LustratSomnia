// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FlashWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BasePlayer.h"

void UFlashWidget::NativeConstruct()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);
	PlayerRef = Cast<ABasePlayer>(FoundActors[0]);
}
