#include "AI/ObjectiveBasedLargeAI/ObjectiveBasedLargeAI.h"
#include <AI/ObjectiveBasedLargeAI/Utility/AIControllerObjectiveBasedLarge.h>

AObjectiveBasedLargeAI::AObjectiveBasedLargeAI()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetMesh()->SetWorldLocation(FVector3d(0.0f, 0.0f, -90.0f));
	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	ShootingSpot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShootingSpot"));
	ChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	ShootingSpot->SetupAttachment(RootComponent);
	Box->SetupAttachment(RootComponent);
	ChildActor->SetupAttachment(RootComponent);
	Sphere->SetupAttachment(ChildActor);
}

void AObjectiveBasedLargeAI::BeginPlay()
{
	Super::BeginPlay();
	ShootingSpot->SetVisibility(false);
	ChildActor->SetVisibility(false);
	GetCapsuleComponent()->Deactivate();
	HitsToDie = FMath::RandRange(2, 6);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AObjectiveBasedLargeAI::OnOverlapBegin);
}

void AObjectiveBasedLargeAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Objective = UGameplayStatics::GetActorOfClass(GetWorld(), ObjectiveClass);
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Objective->GetActorLocation()),
		DeltaTime, InterpSpeed));
	if (WeaknessHit >= HitsToDie)
		Dead();
	else
		MoveWeakness();
}

void AObjectiveBasedLargeAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (Cast<ABaseProjectile>(OtherActor))
	{
		ChildActor->SetVisibility(false);
		WeaknessHit++;
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AObjectiveBasedLargeAI::WeaknessSpawn, WeaknessDelay, false);
		UnusedHandle.Invalidate();
	}
}

void AObjectiveBasedLargeAI::WeaknessSpawn()
{
	WeaknessSpawned = false;
}

void AObjectiveBasedLargeAI::MoveWeakness()
{
	if (!WeaknessSpawned)
	{
		ChildActor->SetWorldLocation(UKismetMathLibrary::RandomPointInBoundingBox(Box->GetComponentLocation(), Box->GetScaledBoxExtent()) - FVector(150.0f, 0.0f, 0.0f));
		ChildActor->SetVisibility(true);
		WeaknessSpawned = true;
	}
}

void AObjectiveBasedLargeAI::Dead()
{
	Super::Dead();
	Cast<AAIControllerObjectiveBasedLarge>(GetController())->GetBlackboardComponent()->SetValueAsBool("IsDead", true);
	UGameplayStatics::PlaySoundAtLocation(this, StunSounds[FMath::RandRange(0, StunSounds.Num() - 1)], GetActorLocation());

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AObjectiveBasedLargeAI::K2_DestroyActor, 5.0f, false);
}