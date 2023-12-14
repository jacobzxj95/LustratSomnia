// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_HUD.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UWBP_HUD : public UUserWidget
{
	GENERATED_BODY()
public:
	// Functions
	UWBP_HUD(const FObjectInitializer& ObjectInitializer);

protected:	
	// Varaibles
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABasePlayer* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABasePlayer> PlayerClass;
	
	// Functions
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
