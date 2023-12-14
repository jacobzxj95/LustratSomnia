#include "AI/DollAI/Behavior/BTTask_MovePlayerToDistractionAI.h"

EBTNodeResult::Type UBTTask_MovePlayerToDistractionAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_MovePlayerToDistractionAI::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	ADollAI* Doll = Cast<ADollAI>(ControlledPawn);

	if (Doll->bPushedByDoll)
	{
		AAuditoryDistractionAI* AuditoryDistraction = Doll->AudioEnemies[FMath::FRandRange(0.0f, Doll->AudioEnemies.Num() - 1.0f)];
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		//ScareScreen = CreateWidget<UDollJumpScare>(GetWorld(), ScareScreenClass);

		if (PlayerCharacter->GetDistanceTo(AuditoryDistraction) > 100.f && 
			PlayerCharacter->GetDistanceTo(ControlledPawn) < 1000.f)
		{
			//ScareScreen->AddToViewport();
			FVector DistractionLocation = AuditoryDistraction->GetActorLocation();
			FVector PlayerLocation = PlayerCharacter->GetActorLocation();

			FVector NewLocation = FMath::VInterpTo(PlayerLocation, DistractionLocation, GetWorld()->GetDeltaSeconds(), InterpSpeed);

			PlayerCharacter->SetActorLocation(NewLocation, false, (FHitResult*)nullptr, ETeleportType::TeleportPhysics);
			//ScareScreen->RemoveFromParent();
			return EBTNodeResult::Succeeded;
		}
		else
		{
			Doll->bPushedByDoll = false;
			//ScareScreen->RemoveFromParent();
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
