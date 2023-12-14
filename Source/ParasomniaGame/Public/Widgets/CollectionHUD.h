// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CollectionHUD.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class PARASOMNIAGAME_API UCollectionHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Objective Text", meta = (BindWidget))
		UTextBlock* EnergyGoal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Objective Text", meta = (BindWidget))
		UTextBlock* CurrentEnergyObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Objective Text", meta = (BindWidget))
		UTextBlock* RationsGoal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Objective Text", meta = (BindWidget))
		UTextBlock* CurrentRationsObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Objective Text", meta = (BindWidget))
		UTextBlock* PeopleGoal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Objective Text", meta = (BindWidget))
		UTextBlock* CurrentPeopleObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Checks")
		bool bEnergyGoalComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Checks")
		bool bRationsGoalComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objectives|Checks")
		bool bPeopleGoalComplete;

	UFUNCTION()
		bool CheckForCompletion();

protected:

	virtual void NativeConstruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABasePlayer* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABasePlayer> PlayerClass;

};
