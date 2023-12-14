// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_ItemDisplay.h"
#include "Widgets/WBP_HUD.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BasePlayer.h"

void UWBP_ItemDisplay::NativeConstruct()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);

	PlayerRef = Cast<ABasePlayer>(FoundActors[0]);
}
