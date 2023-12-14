#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include <AI/HumanAI/HumanAI.h>
#include "AIController.h"
#include "BTTask_BeingSaved.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_BeingSaved : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DistanceFromPlayerToDespawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DistanceFromObjectiveToDespawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* Objective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> ObjectiveClass;
};
