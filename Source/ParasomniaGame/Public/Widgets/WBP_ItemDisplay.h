// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_ItemDisplay.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UWBP_ItemDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABasePlayer* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABasePlayer> PlayerClass;

	// Functions
	virtual void NativeConstruct() override;

};
