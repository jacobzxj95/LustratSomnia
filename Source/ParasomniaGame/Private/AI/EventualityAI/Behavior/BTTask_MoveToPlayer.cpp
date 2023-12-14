#include "AI/EventualityAI/Behavior/BTTask_MoveToPlayer.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = OwnerController->GetPawn();
	return ReceiveExecuteAI(OwnerController, ControlledPawn);
}

EBTNodeResult::Type UBTTask_MoveToPlayer::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	OwnerController->MoveToActor((AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	return EBTNodeResult::Succeeded;
}