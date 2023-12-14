#include "AI/EventualityAI/EventualityAI.h"

AEventualityAI::AEventualityAI()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AEventualityAI::BeginPlay()
{
	Super::BeginPlay();
	DodgedByPlayer = 0;
	AudioComponent->Deactivate();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEventualityAI::OnOverlapBegin);
}

void AEventualityAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bGotLit)
		GotLight();
	if (Cast<AAIControllerEventuality>(GetController())->IsByPlayer)
	{
		AudioComponent->Activate();
	}
}

void AEventualityAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		DodgedByPlayer++;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), UpdateSound, GetMesh()->GetComponentLocation());
	}
}

void AEventualityAI::GotLight()
{
	GetCharacterMovement()->StopMovementImmediately();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEventualityAI::Delay, StunDuration, false);
}

void AEventualityAI::Delay()
{
	bGotLit = false;
}