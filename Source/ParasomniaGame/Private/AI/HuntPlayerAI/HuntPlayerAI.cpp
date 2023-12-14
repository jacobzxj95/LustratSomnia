#include "AI/HuntPlayerAI/HuntPlayerAI.h"

AHuntPlayerAI::AHuntPlayerAI()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHuntPlayerAI::OnOverlapBegin);
}

void AHuntPlayerAI::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->Deactivate();
}

void AHuntPlayerAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	UAISense_Touch::ReportTouchEvent(GetWorld(), this, OtherActor, OtherActor->GetActorLocation());
}

void AHuntPlayerAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bGotLit)
		GotLight();
	if (Cast<AAIControllerHuntPlayer>(GetController())->IsByPlayer)
	{
		AudioComponent->Activate();
	}
}	

void AHuntPlayerAI::GotLight()
{
	GetCharacterMovement()->StopMovementImmediately();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AHuntPlayerAI::Delay, StunDuration, false);
}

void AHuntPlayerAI::Delay()
{
	bGotLit = false;
}