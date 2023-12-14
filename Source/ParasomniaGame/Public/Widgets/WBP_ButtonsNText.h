// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_ButtonsNText.generated.h"

/**
 * 
 */
// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonWidget);
UCLASS()
class PARASOMNIAGAME_API UWBP_ButtonsNText : public UUserWidget
{
	GENERATED_BODY()
protected:
	// Functions
	virtual void NativeConstruct() override;

public:
	// Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "ButtonsNText|Delegate")
		FButtonWidget OnClicked;

	// Variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ButtonsNText|Variable")
		FText Info;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* ButtonText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* BackgroundButton;

	// Functions
	UFUNCTION()
		void OnClickedBackground();

#if WITH_EDITOR
	void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
#endif
	
};
