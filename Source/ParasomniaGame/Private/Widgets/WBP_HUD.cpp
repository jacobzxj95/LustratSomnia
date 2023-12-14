// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_HUD.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Actors/BasePlayer.h"
#include "Kismet/GameplayStatics.h"

UWBP_HUD::UWBP_HUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWBP_HUD::NativeConstruct()
{
	//tarray of actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);

	PlayerRef = Cast<ABasePlayer>(FoundActors[0]);

}

void UWBP_HUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}
