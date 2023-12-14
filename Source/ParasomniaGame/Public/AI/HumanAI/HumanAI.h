#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include "Widgets/WBP_PickupTextDisplay.h"
#include "GameFramework/Character.h"
#include <AI/HumanAI/Utility/AIControllerHuman.h>
#include "Widgets/HumanInteraction.h"
#include "HumanAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API AHumanAI : public ABaseAI
{
	GENERATED_BODY()

public:

	AHumanAI();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
		void ToggleBool();

	UFUNCTION(BlueprintCallable)
		void Delay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UHumanInteraction* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UHumanInteraction> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInteractedByPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsFarEnough;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bSoundIsPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<USoundBase*> HelpSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<USoundBase*> ThanksSounds;
};
