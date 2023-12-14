// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseChar.h"
#include "BaseSentry.generated.h"

/**
 * 
 */

class UBoxComponent;
class UPrimitiveComponent;
class AActor;
class UInputAction;
class ABaseProjectile;
class ABasePlayer;
class UMountTurretText;
class UWBP_Turret;
class APlayerController;
class USoundBase;

UCLASS()
class PARASOMNIAGAME_API ABaseSentry : public ABaseChar
{
	GENERATED_BODY()
	
public:

	ABaseSentry();

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Functions")
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		FName BarrelSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		FName TurretRotationSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Box")
		UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		TArray<TSubclassOf<ABaseProjectile>> ProjectileClassArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		int ProjectileIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
		TArray<FVector> PlayerPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
		ABasePlayer* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		UMountTurretText* MountHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<UMountTurretText> MountHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		UWBP_Turret* TurretHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<UWBP_Turret> TurretHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputAction* IA_BulletSwap;

	float RechargeTime;
	bool bCanShoot;

	int LocationIndex;

	float previousPlayerX;
	float previousPlayerY;
	float previousPlayerZ;

	bool bIsMovingRight;
	bool bIsMovingLeft;
	bool bStartMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		bool bMovedIntoSentry;

	APlayerController* PlayerController;

	float CurrMaxEnergy;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
		USoundBase* ReloadSound;

public:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void MoveAction(const FInputActionValue& Value) override;

	void CameraAction(const FInputActionValue& Value) override;

	void Action(const FInputActionValue& Value) override;

	void InteractionAction(const FInputActionValue& Value) override;

	void MoveSentry(float DeltaTime, bool rightMovement, bool leftMovement);

	void ChangeBullet();

	void ControllerHUDActionHeld(const FInputActionValue& Value) override;

	/*virtual FRotator GetBaseAimRotation() const override;*/

	void ResetShoot();
};
