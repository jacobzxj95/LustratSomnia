// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CollectionHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BasePlayer.h"

bool UCollectionHUD::CheckForCompletion()
{
	return bEnergyGoalComplete && bRationsGoalComplete && bPeopleGoalComplete;
}

void UCollectionHUD::NativeConstruct()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, FoundActors);
	PlayerRef = Cast<ABasePlayer>(FoundActors[0]);

	bEnergyGoalComplete = false;
	bRationsGoalComplete = false;
	bPeopleGoalComplete = false;
}
