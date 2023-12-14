#include "AI/SuddennessAI/SuddennessAI.h"

ASuddennessAI::ASuddennessAI()
{
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportPoint"));
	Cube->SetupAttachment(RootComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
}

void ASuddennessAI::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Cube->OnComponentBeginOverlap.AddDynamic(this, &ASuddennessAI::OnOverlapBegin);
}

void ASuddennessAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bGotLit)
	{
		GotLight();
	}
	if (this->GetDistanceTo(PlayerCharacter) < 75.0f && !bGotLit)
	{
		TeleportPlayer();
	}
}

void ASuddennessAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == PlayerCharacter)
	{
		TeleportPlayer();
	}
}

void ASuddennessAI::TeleportPlayer()
{
	if (PlayerCharacter) 
	{
		PlayerCharacter->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		//5 tries for getting correct teleport location
		//TODO: setup EQS to accurately get nodes of location teleport
		for(int i = 0; i < 5; i++)
		{
			if(PlayerCharacter->TeleportTo(Cube->GetRelativeLocation(),PlayerCharacter->GetActorRotation()))
			{
				break;
			}
		}
		PlayerCharacter->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		Destroy();
	}
}

void ASuddennessAI::DetachTPPoint()
{
	Cube->SetWorldLocation(UKismetMathLibrary::RandomPointInBoundingBox
	(BoxCollision->GetComponentLocation(), BoxCollision->GetScaledBoxExtent()));
	Cube->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void ASuddennessAI::GotLight()
{
	Super::GotLight();
	UGameplayStatics::PlaySoundAtLocation(this, StunSound, GetActorLocation());
}