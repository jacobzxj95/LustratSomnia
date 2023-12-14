// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerText.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UTimerText : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABasePlayer* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABasePlayer> PlayerClass;

	// Functions
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	// Variables
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Minutes;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Seconds;
};
