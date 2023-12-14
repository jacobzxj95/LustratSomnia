#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI/EventualityAI/EventualityAI.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BTTask_UpdateCounter.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_UpdateCounter : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);
};
