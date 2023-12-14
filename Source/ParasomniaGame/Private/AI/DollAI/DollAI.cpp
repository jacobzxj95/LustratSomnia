#include "AI/DollAI/DollAI.h"

#include "Blueprint/UserWidget.h"

ADollAI::ADollAI()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->SetupAttachment(RootComponent);
}

void ADollAI::BeginPlay()
{
	Super::BeginPlay();
	bPushedByDoll = false;
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ADollAI::OnBeginOverlap);
}

void ADollAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bGotLit) {
		GotLight();
	}
}

void ADollAI::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	AActor* PlayerActor = Cast<AActor>(Player);
	if (OtherActor == PlayerActor && !bPushedByDoll) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DollSounds[FMath::RandRange(0, DollSounds.Num() - 1)], GetActorLocation());
		ScareScreen = CreateWidget<UDollJumpScare>(GetWorld(), ScareScreenClass);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADollAI::ChangeBools, TimeBeforePushed, false);
		TimerHandle.Invalidate();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADollAI::JumpScare, TimeBeforePushed, false);
		TimerHandle.Invalidate();
	}
}

void ADollAI::ChangeBools()
{
	bPushedByDoll = !bPushedByDoll;
}

void ADollAI::JumpScare()
{
	ScareScreen->AddToViewport();
	UGameplayStatics::PlaySoundAtLocation(this, JumpscareSound, GetActorLocation());
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADollAI::RemoveJumpScare, 0.25f, false);
	TimerHandle.Invalidate();
}

void ADollAI::RemoveJumpScare()
{
	ScareScreen->RemoveFromParent();
}

void ADollAI::GotLight()
{
	Super::GotLight();
	UGameplayStatics::PlaySoundAtLocation(this, StunSounds[FMath::RandRange(0, StunSounds.Num()-1)], GetActorLocation());
}