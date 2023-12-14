#include "AI/EventualityAI/Behavior/BTTask_UpdateCounter.h"

EBTNodeResult::Type UBTTask_UpdateCounter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = OwnerController->GetPawn();
	return ReceiveExecuteAI(OwnerController, ControlledPawn);
}

EBTNodeResult::Type UBTTask_UpdateCounter::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	AEventualityAI* EventualityAI = Cast<AEventualityAI>(ControlledPawn);
	OwnerController->GetBlackboardComponent()->SetValueAsInt("DodgedByPlayer", EventualityAI->DodgedByPlayer);
	return EBTNodeResult::Succeeded;
}