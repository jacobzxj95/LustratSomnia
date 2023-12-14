#include "AI/HuntPlayerAI/Behavior/BTTask_ClearBlackBoardValue.h"

EBTNodeResult::Type UBTTask_ClearBlackBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn *Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_ClearBlackBoardValue::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	OwnerController->GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}