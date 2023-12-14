#include "AI/AuditoryDistractionAI/Behavior/BTTask_PlayAudioDistraction.h"

EBTNodeResult::Type UBTTask_PlayAudioDistraction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_PlayAudioDistraction::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	UBlackboardComponent* BlackboardComp = OwnerController->GetBlackboardComponent();

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	AActor* PlayerActor = Cast<AActor>(Player);
	float distance = ControlledPawn->GetDistanceTo(PlayerActor);
	if (distance >= 10.0f && distance <= 200.0f) {
		UGameplayStatics::PlaySoundAtLocation(this, CloseSound[FMath::RandRange(0, CloseSound.Num() - 1)], BlackboardComp->GetValueAsVector("TargetLocation"));
		return EBTNodeResult::Succeeded;
	}
	else if (distance >= 200.3f && distance <= 612.0f) {
		UGameplayStatics::PlaySoundAtLocation(this, MediumSound[FMath::RandRange(0, MediumSound.Num() - 1)], BlackboardComp->GetValueAsVector("TargetLocation"));
		return EBTNodeResult::Succeeded;
	}
	else if (distance >= 612.3f && distance <= 1100.0f) {
		UGameplayStatics::PlaySoundAtLocation(this, FarSound[FMath::RandRange(0, FarSound.Num() - 1)], BlackboardComp->GetValueAsVector("TargetLocation"));
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}