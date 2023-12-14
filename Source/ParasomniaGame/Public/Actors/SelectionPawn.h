// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Utility/BaseGameInstance.h"

#include "SelectionPawn.generated.h"

class USkeletalMeshComponent;
class UBaseGameInstance;
class UMaterialInstance;

UCLASS()
class PARASOMNIAGAME_API ASelectionPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASelectionPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")
		USkeletalMeshComponent* SkeletalMeshComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection")

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void SetMesh(USkeletalMesh* Mesh);

	UFUNCTION()
		USkeletalMesh* GetMesh();

	UFUNCTION()
		void SetMaterial(UMaterial* Material);

	UFUNCTION()
		void SetMaterialInstance(UMaterialInstance* MaterialInstance);

	UFUNCTION()
		UMaterialInstance* GetMaterialInstance();

};
