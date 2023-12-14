#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIControllerObjectiveBased.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerObjectiveBased : public ABaseAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BT;
};
