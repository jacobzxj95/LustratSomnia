#include "AI/HuntPlayerAI/Behavior/BTTask_MoveToRandom.h"

EBTNodeResult::Type UBTTask_MoveToRandom::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn *Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_MoveToRandom::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	FVector Point;
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	NavSystem->K2_GetRandomReachablePointInRadius(GetWorld(), ControlledPawn->GetActorLocation(), Point, SearchRadius);
	OwnerController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Point);
	return EBTNodeResult::Succeeded;
}