// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Utility/BaseGameInstance.h"
#include "BaseChar.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UEnergyComponent;
class UUserWidget;
class UWBP_HUD;
class UWBP_TestHUD;
class UWBP_TestTurretHUD;
class UWBP_PausingMenu;
class UTimerText;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNightfallSignature);

UCLASS()
class PARASOMNIAGAME_API ABaseChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseChar();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Energy")
		UEnergyComponent* EnergyComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* PlayerInputContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_Interaction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_PrototypeHUDAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_PauseNavDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_PauseNavUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_PauseAccept;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* IA_PauseReturn;

	UPROPERTY(BlueprintReadOnly, Category = "Hud")
		UWBP_TestHUD* ControlsHUD;

	UPROPERTY(BlueprintReadOnly, Category = "Hud")
		UWBP_TestTurretHUD* TurretControlsHUD;

	UPROPERTY(BlueprintReadOnly, Category = "Hud")
		UWBP_PausingMenu* PausingMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		UTimerText* TimerMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		bool bIsPaused;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		int Seconds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		bool bIsHalfTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		bool bIsHudVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer|Daytime")
		int DayMinutes = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer|Daytime")
		int DaySeconds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer|Nighttime")
		int NightMinutes = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer|Nighttime")
		int NightSeconds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mode")
		bool bDayTimeEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode")
		bool bNightTimeEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mode")
		bool bNightTimeMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sentry")
		bool bIsSentryMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
		bool SkippedToNight;

	bool PressedOnce;

	//bool SkipNightTime;

	//make an array of text for different objectives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective|Text")
		TArray<FString> ObjectiveText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective|Goals")
		TArray<int32> EnergyCollectionGoals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective|Goals")
		TArray<int32> RationCollectionGoals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective|Goals")
		TArray<int32> PeopleGoals;

#pragma region Energy Collection Variables
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentCellsGoal;

	UPROPERTY(BlueprintReadOnly)
		int32 CellsCollected;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objective|Indices")
		int CellIndex;
#pragma endregion

#pragma region Ration Collection Variables
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentRationsGoal;

	UPROPERTY(BlueprintReadOnly)
		int RationsCollected;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objective|Indices")
		int RationIndex;

#pragma endregion

#pragma region People Collection Variables
	UPROPERTY(BlueprintReadOnly)
		int32 CurrentPeopleGoal;

	UPROPERTY(BlueprintReadOnly)
		int PeopleSaved;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Objective|Indices")
		int PeopleIndex;
#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		TSubclassOf<UWBP_HUD> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		TSubclassOf<UWBP_TestHUD> ControllerHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		TSubclassOf<UWBP_TestTurretHUD> TurretControlsHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		TSubclassOf<UWBP_PausingMenu> PausingMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hud")
		TSubclassOf<UTimerText> TimerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Save")
		UBaseGameInstance* GameInstance;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveAction(const FInputActionValue& Value);

	virtual void CameraAction(const FInputActionValue& Value);

	virtual void Action(const FInputActionValue& Value);

	virtual void InteractionAction(const FInputActionValue& Value);

	virtual void PauseAction(const FInputActionValue& Value);

	void CheckIfPaused() const;

	virtual void ControllerHUDActionHeld(const FInputActionValue& Value);

	void DelayForTimer();

	void PauseNavMoveDown(const FInputActionValue& Value);

	void PauseNavMoveUp(const FInputActionValue& Value);

	void PauseNavAccept(const FInputActionValue& Value);

	void PauseNavReturn(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
		void CountdownTimer();
	
	UPROPERTY()
		FOnNightfallSignature OnNightfall;

	UPROPERTY()
		FTimerHandle OpacityTimerHandle; 


	/*TEST VARIABLES*/

	//bool IPRESSEDIT;


};
