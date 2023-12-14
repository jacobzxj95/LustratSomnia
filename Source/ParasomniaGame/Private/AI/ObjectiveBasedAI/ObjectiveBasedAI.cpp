#include "AI/ObjectiveBasedAI/ObjectiveBasedAI.h"
#include <Kismet/KismetMathLibrary.h>
#include <AI/ObjectiveBasedAI/Utility/AIControllerObjectiveBased.h>

AObjectiveBasedAI::AObjectiveBasedAI()
{
	PrimaryActorTick.bCanEverTick = true;
	ShootingSpot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootingSpot"));
	ShootingSpot->SetupAttachment(GetMesh());
}

void AObjectiveBasedAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Objective = UGameplayStatics::GetActorOfClass(GetWorld(), ObjectiveClass);
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), 
		Objective->GetActorLocation()), DeltaTime, InterpSpeed));
}

void AObjectiveBasedAI::Dead()
{
	Super::Dead();
	Cast<AAIControllerObjectiveBased>(GetController())->GetBlackboardComponent()->SetValueAsBool("IsDead", true);
	UGameplayStatics::PlaySoundAtLocation(this, StunSounds[FMath::RandRange(0, StunSounds.Num() - 1)], GetActorLocation());

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AObjectiveBasedAI::K2_DestroyActor, 5.0f, false);
}