// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Widgets/WBP_PickupTextDisplay.h"


// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	OutlineMesh = CreateDefaultSubobject<UStaticMeshComponent>("OutlineMesh");
	PickupCollision = CreateDefaultSubobject<USphereComponent>("PickupCollision");
	OutlineCollision = CreateDefaultSubobject<USphereComponent>("OutlineCollision");

	PickupCollision->SetupAttachment(PickupMesh);
	OutlineMesh->SetupAttachment(PickupMesh);
	OutlineCollision->SetupAttachment(PickupMesh);

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	OutlineCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OutlineStartOverlap);
	OutlineCollision->OnComponentEndOverlap.AddDynamic(this, &ABasePickup::OutlineEndOverlap);

	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::PickupStartOverlap);
	PickupCollision->OnComponentEndOverlap.AddDynamic(this, &ABasePickup::PickupEndOverlap);

	OutlineMesh->SetVisibility(false);

	PickupHUD = CreateWidget<UWBP_PickupTextDisplay>(GetWorld(), PickupHUDClass);
	PickupHUD->AddToViewport();
	PickupHUD->SetVisibility(ESlateVisibility::Hidden);
}

void ABasePickup::OutlineStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OutlineMesh->SetVisibility(true);
}

void ABasePickup::OutlineEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OutlineMesh->SetVisibility(false);
}

void ABasePickup::PickupStartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PickupHUD->SetVisibility(ESlateVisibility::Visible);
}

void ABasePickup::PickupEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PickupHUD->SetVisibility(ESlateVisibility::Hidden);
}

float ABasePickup::Pickup()
{
	Destroy();
	return 0.0f;
}

