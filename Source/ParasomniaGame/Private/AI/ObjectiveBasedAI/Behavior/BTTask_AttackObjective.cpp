#include "AI/ObjectiveBasedAI/Behavior/BTTask_AttackObjective.h"

EBTNodeResult::Type UBTTask_AttackObjective::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_AttackObjective::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = ControlledPawn;
	if (ControlledPawn->GetClass() == ObjectiveAIClass) {
		GetWorld()->SpawnActor<AAIBullet>(BulletClass, Cast<AObjectiveBasedAI>(ControlledPawn)->ShootingSpot->GetComponentTransform(), SpawnParams);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, ControlledPawn->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	else if (ControlledPawn->GetClass() == ObjectiveLargeAIClass) {
		GetWorld()->SpawnActor<AAIBullet>(BulletClass, Cast<AObjectiveBasedLargeAI>(ControlledPawn)->ShootingSpot->GetComponentTransform(), SpawnParams);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, ControlledPawn->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}