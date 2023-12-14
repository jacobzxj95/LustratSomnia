#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIControllerWeepingAngel.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerWeepingAngel : public ABaseAIController
{
	GENERATED_BODY()

		public:

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				class UBehaviorTree* BT;

			virtual void HandleSightCode(AActor* Actor, FAIStimulus Stimulus) override;

		protected:

			virtual void BeginPlay() override;
};
