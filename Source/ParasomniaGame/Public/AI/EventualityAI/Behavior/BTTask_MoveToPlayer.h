#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include "BTTask_MoveToPlayer.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_MoveToPlayer : public UBTTaskNode
{
	GENERATED_BODY()

	protected:

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

		EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);
};
