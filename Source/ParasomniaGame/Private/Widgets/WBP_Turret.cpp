// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WBP_Turret.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Actors/BaseSentry.h"
#include "AI/ObjectiveBasedAI/AIObjective.h"
#include "Blueprint/SlateBlueprintLibrary.h"

UWBP_Turret::UWBP_Turret(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWBP_Turret::NativeConstruct()
{
	TArray<AActor*> FoundActors;
	TArray<AActor*> FoundActors2;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SentryClass, FoundActors);
	SentryRef = Cast<ABaseSentry>(FoundActors[0]);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TreeClass, FoundActors2);
	TreeRef = Cast<AAIObjective>(FoundActors2[0]);

	DynamicMaterial = CrosshairImage->GetDynamicMaterial();

	CrosshairImage->SetBrushFromMaterial(DynamicMaterial);

	SetSafeColor();
}

void UWBP_Turret::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector2D PixelPos;
	FVector2D ViewportPos;

	FGeometry CachedGeometry = CrosshairImage->GetCachedGeometry();

	FVector2D AbsoluteSize = CachedGeometry.GetAbsoluteSize();
	AbsoluteSize *= 0.5f;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), CachedGeometry, FVector2D(0, 0), PixelPos, ViewportPos);

	PixelPos += AbsoluteSize;

	GetOwningPlayer()->DeprojectScreenPositionToWorld(PixelPos.X, PixelPos.Y, WorldPos, WorldDir);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwningPlayerPawn());

	EndPoint = WorldPos + (WorldDir * 100000);

	FHitResult HitResult;

	bValidHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), WorldPos, EndPoint, ObjectTypes,
		false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true); //THIS HAS THE FOR DURATION I WAS LOOKING FOR

	if (bValidHit)
	{
		HitLocation = HitResult.Location;
		APawn* Pawn = Cast<APawn>(HitResult.GetActor());

		if (Pawn)
		{
			SetDangerColor();
		}
		else
		{
			SetSafeColor();
		}
	}
	else
	{
		SetSafeColor();
	}

	/*if (CrosshairImage->IsVisible())
	{
		CrosshairImage->SetVisibility(ESlateVisibility::Collapsed);
	}*/

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("Hit: %s"), bValidHit ? TEXT("True") : TEXT("False")));
}

void UWBP_Turret::SetColor(FLinearColor Color)
{
	DynamicMaterial->SetVectorParameterValue(ColorKey, Color);
}

void UWBP_Turret::SetEnergy(float percent)
{
	EnergyBar->SetPercent(percent);
}

void UWBP_Turret::SetChurch(float percent)
{
	ChurchBar->SetPercent(percent);
}

bool UWBP_Turret::GetEnd(FVector& _Hit, FVector& _EndPoint) const
{
	_Hit = HitLocation;
	_EndPoint = EndPoint;
	return bValidHit;
}

void UWBP_Turret::SetDangerColor()
{
	SetColor(DangerColor);
}

void UWBP_Turret::SetSafeColor()
{
	SetColor(SafeColor);
}
