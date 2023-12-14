#include "AI/SuddennessAI/Behavior/BTTask_RunToPlayer.h"
#include <AI/SuddennessAI/SuddennessAI.h>

EBTNodeResult::Type UBTTask_RunToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = OwnerController->GetPawn();
	return ReceiveExecuteAI(OwnerController, ControlledPawn);
}

EBTNodeResult::Type UBTTask_RunToPlayer::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	if (ControlledPawn->GetDistanceTo((const AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) > DistanceToEngage)
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		Cast<ASuddennessAI>(ControlledPawn)->DetachTPPoint();
		OwnerController->MoveToActor((AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}