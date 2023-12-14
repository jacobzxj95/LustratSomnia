#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include <Kismet/GameplayStatics.h>
#include "ObjectiveBasedAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API AObjectiveBasedAI : public ABaseAI
{
	GENERATED_BODY()
	
		public:

			AObjectiveBasedAI();

			virtual void Tick(float DeltaTime) override;

			void Dead() override;

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				class UStaticMeshComponent* ShootingSpot;

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				TSubclassOf<class AActor> ObjectiveClass;

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				 AActor* Objective;

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				float InterpSpeed;

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				TArray<USoundBase*> StunSounds;
};
