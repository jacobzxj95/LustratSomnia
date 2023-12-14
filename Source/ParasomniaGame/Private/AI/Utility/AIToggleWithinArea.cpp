#include "AI/Utility/AIToggleWithinArea.h"

#include "AI/DollAI/DollAI.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpawnPoolComponent.h"
#include "Actors/BasePickup.h"
#include "Widgets/SlideInStunHint.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/BaseGameInstance.h"
#include "GameFramework/GameModeBase.h"

AAIToggleWithinArea::AAIToggleWithinArea()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(RootComponent);
}

void AAIToggleWithinArea::BeginPlay()
{
	Super::BeginPlay();
	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAIToggleWithinArea::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AAIToggleWithinArea::OnOverlapEnd);
	GameInstance = Cast<class UBaseGameInstance>(GetGameInstance());
	HintHud = CreateWidget<USlideInStunHint>(GetWorld(), HintClass);
	
	//get spawn pool form game mode
	TArray<USpawnPoolComponent*> SpawnPoolComponents; 
	UGameplayStatics::GetGameMode(this)->GetComponents<USpawnPoolComponent>(SpawnPoolComponents);
	//update map to assign correct pool to point
	for (AAIPoolSpawnPoint* Point : SpawnPointsWithin)
	{
		for (USpawnPoolComponent* PoolComponent : SpawnPoolComponents)
		{
			
			if(PoolComponent->SpawnPoolClass->IsChildOf(Point->SpawnClass))
			{
				PointPoolMap.Emplace(Point,PoolComponent);
			}
		}
	}
}

void AAIToggleWithinArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
                                         AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	if (OtherActor == Player && OtherComp->IsA<UCapsuleComponent>())
	{
		TArray<AActor*> OverlappingActors;

		// Set chance check on spawn pt based on spawn chance
		for (const auto& Spawn : PointPoolMap)
		{
			Spawn.Key->SetSpawnCheck();
		}

		GetOverlappingActors(OverlappingActors, PickupClass);

		for (AActor* Actor : OverlappingActors)
		{
			ABasePickup* Pickup = Cast<ABasePickup>(Actor);
			if (Pickup)
			{
				Pickup->PickupMesh->SetVisibility(true);
			}
		}
		
		// Hint Hud
		if (GameInstance->bHintHUD == false)
		{
			HintHud->AddToViewport();
			GameInstance->bHintHUD = true;
		}

		// Call spawning function
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AAIToggleWithinArea::Spawning, 1.0f, true);
	}
}

void AAIToggleWithinArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player && OtherComp->IsA<UCapsuleComponent>())
	{
		for (const auto& Spawn : PointPoolMap)
		{
			Spawn.Key->Reset();
		}
		for (const ABaseAI* AI : SpawnedAIArray)
		{
			if(AI && AI->GetController())
			{
				Cast<ABaseAIController>(AI->GetController())->ToggleBoolValue();
			}
		}

		TArray<AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors, PickupClass);

		for (AActor* Actor : OverlappingActors)
		{
			ABasePickup* Pickup = Cast<ABasePickup>(Actor);
			if (Pickup)
			{
				Pickup->PickupMesh->SetVisibility(false);
			}
		}

		// Hint Hud
		if (GameInstance->bHintHUD == true)
		{
			HintHud->RemoveFromParent();
		}

		SpawnedAIArray.Empty();
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void AAIToggleWithinArea::Spawning()
{
	for (const auto& Spawn : PointPoolMap)
	{
		if(Spawn.Key->GetCurrSpawnAmt() >= Spawn.Key->MaxSpawnAmount ||
			Spawn.Key->GetSpawnCheck() == false)
		{
			continue;
		}
		
		if (ABaseAI* SpawnedAI = Spawn.Value->PoolSpawnFromActor(Spawn.Key))
		{
			Spawn.Key->Spawned();
			SpawnedAIArray.Add(SpawnedAI);
			Cast<ABaseAIController>(SpawnedAI->GetController())->ToggleBoolValue();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Spawn Failed!"));
		}
	}

	
	TArray<ADollAI*> DollArray;
	TArray<AAuditoryDistractionAI*> AudiArray;
	
	//populate any doll ai with audio ai data
	for (const auto& AI : SpawnedAIArray)
	{
		if(ADollAI* DollAI = Cast<ADollAI>(AI))
		{
			DollArray.Emplace(DollAI);
		}
		if(AAuditoryDistractionAI* AudiAI = Cast<AAuditoryDistractionAI>(AI))
		{
			AudiArray.Emplace(AudiAI);
		}
	}

	for (auto& DollAI : DollArray)
	{
		DollAI->AudioEnemies = AudiArray;
	}
}