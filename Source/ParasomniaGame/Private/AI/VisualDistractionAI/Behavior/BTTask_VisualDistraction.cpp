#include "AI/VisualDistractionAI/Behavior/BTTask_VisualDistraction.h"

EBTNodeResult::Type UBTTask_VisualDistraction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_VisualDistraction::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn) {
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(FMath::RInterpTo(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation(),
		UKismetMathLibrary::FindLookAtRotation(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(), ControlledPawn->GetActorLocation())
		, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), InterpSpeed));
	return EBTNodeResult::Succeeded;
}