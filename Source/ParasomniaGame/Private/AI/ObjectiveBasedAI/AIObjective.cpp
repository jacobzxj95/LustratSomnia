#include "AI/ObjectiveBasedAI/AIObjective.h"

AAIObjective::AAIObjective()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	Capsule->SetupAttachment(RootComponent);
}



void AAIObjective::BeginPlay()
{
	Super::BeginPlay();
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AAIObjective::OnBeginOverlap);
	SentryRef = Cast<ABaseSentry>(UGameplayStatics::GetActorOfClass(GetWorld(), SentryClass));
	PlayerRef = Cast<ABasePlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), PlayerClass));

	CurrentHealth = MaxHealth;
}

void AAIObjective::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool FromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass() == BulletClass)
	{
		CurrentHealth--;

		if (SentryRef->TurretHUD)
		{
			SentryRef->TurretHUD->ChurchBar->SetPercent(CurrentHealth / MaxHealth);
		}

		if (CurrentHealth == 0)
		{
			DeathRef = CreateWidget<UWBP_LoseMenu>(GetWorld(), DeathClass);
			DeathRef->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), DeathRef, EMouseLockMode::LockAlways);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;

			SentryRef->SetActorTickEnabled(false);
			PlayerRef->SetActorTickEnabled(false);

		}
	}
}

