// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SelectionPawn.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ASelectionPawn::ASelectionPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
}

// Called when the game starts or when spawned
void ASelectionPawn::BeginPlay()
{
	Super::BeginPlay();

	UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		SetMaterialInstance(GameInstance->CharacterMaterial);
	}
}

// Called every frame
void ASelectionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASelectionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASelectionPawn::SetMesh(USkeletalMesh* Mesh)
{
	SkeletalMeshComponent->SetSkeletalMesh(Mesh);
}

USkeletalMesh* ASelectionPawn::GetMesh()
{
	return SkeletalMeshComponent->GetSkeletalMeshAsset();
}

void ASelectionPawn::SetMaterial(UMaterial* Material)
{
	SkeletalMeshComponent->SetMaterial(0, Material);
}

void ASelectionPawn::SetMaterialInstance(UMaterialInstance* MaterialInstance)
{
	SkeletalMeshComponent->SetMaterial(0, MaterialInstance);
}

UMaterialInstance* ASelectionPawn::GetMaterialInstance()
{
	UMaterialInstance* MaterialInstance = Cast<UMaterialInstance>(SkeletalMeshComponent->GetMaterial(0));
	return MaterialInstance;
}

