#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "SuddennessAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API ASuddennessAI : public ABaseAI
{
	GENERATED_BODY()
	
public:

	ASuddennessAI();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void GotLight() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void TeleportPlayer();

	UFUNCTION()
		void DetachTPPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UStaticMeshComponent* Cube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class ACharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		USoundBase* StunSound;
};
