#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIControllerObjectiveBasedLarge.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerObjectiveBasedLarge : public ABaseAIController
{
	GENERATED_BODY()

		protected:

			virtual void BeginPlay() override;

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				class UBehaviorTree* BT;
	
};
