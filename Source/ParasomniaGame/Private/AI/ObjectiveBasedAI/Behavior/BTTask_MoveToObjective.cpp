#include "AI/ObjectiveBasedAI/Behavior/BTTask_MoveToObjective.h"

EBTNodeResult::Type UBTTask_MoveToObjective::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_MoveToObjective::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	Objective = UGameplayStatics::GetActorOfClass(GetWorld(), ObjectiveClass);
	float Distance = (Objective->GetDistanceTo(ControlledPawn)) - 100;
	if (Distance > AcceptanceRadius) {
		OwnerController->MoveToActor(Objective, AcceptanceRadius);
	}
	else
	{
		if (Distance <= AcceptanceRadius)
		{
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}