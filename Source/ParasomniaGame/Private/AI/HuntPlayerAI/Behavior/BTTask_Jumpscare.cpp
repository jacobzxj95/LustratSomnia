#include "AI/HuntPlayerAI/Behavior/BTTask_Jumpscare.h"

EBTNodeResult::Type UBTTask_Jumpscare::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController->GetPawn();
	return ReceiveExecuteAI(AIController, Pawn);
}

EBTNodeResult::Type UBTTask_Jumpscare::ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	AActor* PlayerActor = Cast<AActor>(Player);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (ControlledPawn->GetDistanceTo(PlayerActor) <= 100.0f && !Cast<ABasePlayer>(Player)->bDayTimeEnd && !bIsPlayerDead) {
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation
		(UKismetMathLibrary::FindLookAtRotation(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(), ControlledPawn->GetActorLocation()));
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ControlledPawn->GetActorLocation());
		bIsPlayerDead = true;
		Player->DisableInput(PlayerController);
        FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_Jumpscare::CallHUD, HitSound->Duration, false);
		TimerHandle.Invalidate();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UBTTask_Jumpscare::CallHUD()
{
	DeathScreen = CreateWidget<UWBP_LoseMenu>(GetWorld(), DeathScreenClass);
	DeathScreen->AddToViewport();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController,
				DeathScreen, EMouseLockMode::LockAlways);
	PlayerController->bShowMouseCursor = true;
}