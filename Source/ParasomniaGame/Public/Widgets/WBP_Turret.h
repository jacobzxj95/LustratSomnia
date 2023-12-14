// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WBP_Turret.generated.h"

/**
 * 
 */
UCLASS()
class PARASOMNIAGAME_API UWBP_Turret : public UUserWidget
{
	GENERATED_BODY()
public:
	// Functions
	UWBP_Turret(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* EnergyBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* ChurchBar;

protected:
	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABaseSentry* SentryRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseSentry> SentryClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AAIObjective* TreeRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AAIObjective> TreeClass;

	UPROPERTY()
		bool bValidHit;

	UPROPERTY()
		FVector EndPoint;

	UPROPERTY()
		FVector HitLocation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* CrosshairImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor DangerColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor SafeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ColorKey;

	UPROPERTY(BlueprintReadOnly)
		class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector WorldPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector WorldDir;

	// Functions
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetColor(FLinearColor Color);

public:
	// Functions
	UFUNCTION(BlueprintCallable)
		virtual void SetEnergy(float percent);

	UFUNCTION(BlueprintCallable)
		virtual void SetChurch(float percent);

	UFUNCTION(BlueprintCallable)
		bool GetEnd(FVector& _Hit, FVector& _EndPoint) const;

	UFUNCTION(BlueprintCallable)
		void SetDangerColor();

	UFUNCTION(BlueprintCallable)
		void SetSafeColor();
};
