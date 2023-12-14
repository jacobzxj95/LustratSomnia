#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include <AI/EventualityAI/Utility/AIControllerEventuality.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "EventualityAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API AEventualityAI : public ABaseAI
{
	GENERATED_BODY()
	
public:
	AEventualityAI();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void GotLight() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void Delay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		int DodgedByPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float StunDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		USoundBase* UpdateSound;
};
