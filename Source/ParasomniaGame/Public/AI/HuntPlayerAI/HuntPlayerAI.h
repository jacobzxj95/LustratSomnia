#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "AI/HuntPlayerAI/Utility/AIControllerHuntPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "HuntPlayerAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API AHuntPlayerAI : public ABaseAI
{
	GENERATED_BODY()

public:
	AHuntPlayerAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		UAudioComponent* AudioComponent;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void Delay();

	void GotLight() override;

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StunDuration;
};
