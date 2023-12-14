#include "AI/HumanAI/Behavior/BTTask_BeingSaved.h"

EBTNodeResult::Type UBTTask_BeingSaved::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* OwnerController = OwnerComp.GetAIOwner();
	APawn* ControlledPawn = OwnerController->GetPawn();
	return ReceiveExecuteAI(OwnerController, ControlledPawn);
}

EBTNodeResult::Type UBTTask_BeingSaved::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	AHumanAI* HumanAI = Cast<AHumanAI>(ControlledPawn);
	Objective = UGameplayStatics::GetActorOfClass(GetWorld(), ObjectiveClass);
	float Distance = (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetDistanceTo(ControlledPawn)) - 100;
	float DistaceToObjective = Objective->GetDistanceTo(ControlledPawn);
	if (Distance < DistanceFromPlayerToDespawn)
	{
		OwnerController->MoveToActor(Objective);
		if (DistaceToObjective <= DistanceFromObjectiveToDespawn)
		{
			ControlledPawn->Destroy();
		}
		return EBTNodeResult::Succeeded;
	}
	else
	{
		if (Distance > DistanceFromPlayerToDespawn)
		{
			HumanAI->bIsFarEnough = true;
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}