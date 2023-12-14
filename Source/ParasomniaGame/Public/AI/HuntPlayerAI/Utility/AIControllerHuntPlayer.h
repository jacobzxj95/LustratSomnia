#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIControllerHuntPlayer.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerHuntPlayer : public ABaseAIController
{
	GENERATED_BODY()

		AAIControllerHuntPlayer();

	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
			UBehaviorTree* BT;

	protected:

		virtual void BeginPlay() override;
};
