// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseChar.h"
#include "InputActionValue.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
class UPlayerAnimInstance;
class UStaminaComponent;
class USpotLightComponent;
class URationsComponent;
class ABasePickup;
class UWBP_HUD;
class UWBP_PickupTextDisplay;
class UStaminaWidget;
class UFlashWidget;
class UCollectionHUD;
class UBoxComponent;
class USoundBase;
class UTimerText;
//forward declare color

UCLASS()
class PARASOMNIAGAME_API ABasePlayer : public ABaseChar
{
	GENERATED_BODY()
private:
	FTimerHandle EndTimerHandle;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lighting")
		USpotLightComponent* SpotLightComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lighting")
		USpotLightComponent* SecondLightComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Lighting")
		UBoxComponent* LightHitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
		UStaminaComponent* StaminaComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rations")
		URationsComponent* RationsComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		bool bMovedIntoPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		FLinearColor DefaultHUDColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		FLinearColor UpdatePickupHUDColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		bool bUpdatedPickupHUD;

protected:
	ABasePlayer();

	virtual void BeginPlay() override;

	UPlayerAnimInstance* PlayerAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_Sprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_ToggleSprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_Crouch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_ToggleCrouch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		TSubclassOf<ABasePickup> PickupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		TArray<USoundBase*> CoolDownSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
		FLinearColor LightColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
		FLinearColor AttackLightColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<UWBP_PickupTextDisplay> PickupHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<UCollectionHUD> CollectionHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<UStaminaWidget> StaminaHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		TSubclassOf<UFlashWidget> FlashHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float CrouchSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float FlashCoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hud")
		float PickupHUDTimer;

public:
	// call the setup input function override
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//call the tick function
	virtual void Tick(float DeltaTime) override;

	void OnAttack();

	void OnEndAttack();
	
	void MoveAction(const FInputActionValue& Value) override;

	void SprintAction(const FInputActionValue& Value);
	void ReleaseSprintAction(const FInputActionValue& Value);
	void SprintFunctionality(bool isPressed);
	void ToggleSprint(const FInputActionValue& Value);

	void StartSprint();
	void StopSprint();

	void CrouchFunctionality(const FInputActionValue& Value);
	void CrouchAction(const FInputActionValue& Value);
	void ReleaseCrouchAction(const FInputActionValue& Value);

	void LightAction(const FInputActionValue& Value);

	void InteractionAction(const FInputActionValue& Value) override;

	void Action(const FInputActionValue& Value) override;

	void ControllerHUDActionHeld(const FInputActionValue& Value) override;

	void SetMesh(USkeletalMesh* Mesh);

	void ChangeFlashColor();

	void ResetHUDColor();

	// Variables
	UPROPERTY(BlueprintReadWrite, Category = "Hud")
		UUserWidget* TestHUD;

	UPROPERTY(BlueprintReadWrite, Category = "Hud")
		UWBP_HUD* DefaultHUD;

	UPROPERTY(BlueprintReadWrite, Category = "Hud")
		UWBP_TestHUD* ControllerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mode")
		bool bIsNearSentry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
		bool bLightOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
		bool bOnCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bCanClimb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bOnLadder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bToggleCrouch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bToggleSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bIsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bIsSprinting;

	UPROPERTY(BlueprintReadWrite, Category = "Hud")
		UWBP_PickupTextDisplay* PickupHUD;

	UPROPERTY(BlueprintReadWrite, Category = "Hud")
		UCollectionHUD* CollectionHUD;

	UPROPERTY(BlueprintReadWrite, Category = "Hud")
		UStaminaWidget* StaminaHUD;

	UPROPERTY(BlueprintReadWrite, Category = "Hud")
		UFlashWidget* FlashHUD;

	FTimerHandle CountdownTimerHandle;
};
