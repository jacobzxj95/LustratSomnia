#include "AI/HumanAI/HumanAI.h"

AHumanAI::AHumanAI()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(RootComponent);

}

void AHumanAI::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AHumanAI::OnBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &AHumanAI::OnEndOverlap);
	OutlineMesh->SetVisibility(false);
}

void AHumanAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsFarEnough)
	{
		Destroy();
	}
	if (!bSoundIsPlaying) 
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HelpSounds[FMath::RandRange(0, HelpSounds.Num() - 1)], GetActorLocation());
		bSoundIsPlaying = true;
		FTimerHandle DelayTimer;
		GetWorldTimerManager().SetTimer(DelayTimer, this, &AHumanAI::Delay, FMath::RandRange(10.f, 50.f), false);
	}
}

void AHumanAI::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player)
	{
		OutlineMesh->SetVisibility(true);
		HUD = CreateWidget<UHumanInteraction>(GetWorld(), HUDClass);
		HUD->AddToViewport();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ThanksSounds[FMath::RandRange(0, ThanksSounds.Num() - 1)], GetActorLocation());
	}
}

void AHumanAI::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player)
	{
		if (HUD)
		{
			OutlineMesh->SetVisibility(false);
			HUD->RemoveFromParent();
		}
	}
}

void AHumanAI::ToggleBool()
{
	bInteractedByPlayer = !bInteractedByPlayer;
	Cast<AAIControllerHuman>(GetController())->GetBlackboardComponent()->SetValueAsBool("InteractedByPlayer", bInteractedByPlayer);
}

void AHumanAI::Delay()
{
	bSoundIsPlaying = false;
}