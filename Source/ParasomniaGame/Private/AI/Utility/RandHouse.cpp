// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Utility/RandHouse.h"

#include "AI/DollAI/DollAI.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpawnPoolComponent.h"
#include "Actors/BasePickup.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/BaseGameInstance.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
ARandHouse::ARandHouse()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ProxEnableBox"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARandHouse::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ARandHouse::OnOverlapEnd);
	RootComponent = SceneComponent;
	BoxComponent->SetupAttachment(RootComponent);

}
// Called when the game starts or when spawned
void ARandHouse::BeginPlay()
{
	Super::BeginPlay();

	Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	GameInstance = Cast<UBaseGameInstance>(GetGameInstance());
	
	//get spawn pool from game mode
	TArray<USpawnPoolComponent*> SpawnPoolComponents; 
	UGameplayStatics::GetGameMode(this)->GetComponents<USpawnPoolComponent>(SpawnPoolComponents);
	//populate SpawnPointsWithin with GetChildComponents
	GetComponents<USpawnPointSceneComponent>(SpawnPointsWithin);
	//update map to assign correct pool to point
	for (auto& Point : SpawnPointsWithin)
	{
		for (auto& PoolComponent : SpawnPoolComponents)
		{
			if(PoolComponent->SpawnPoolClass->IsChildOf(Point->SpawnClass))
			{
				PointPoolMap.Emplace(Point,PoolComponent);
			}
		}
	}
}

void ARandHouse::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player && OtherComp->IsA<UCapsuleComponent>())
	{
		TArray<AActor*> OverlappingActors;

		// Set chance check on spawn pt based on spawn chance
		for (const auto& Spawn : PointPoolMap)
		{
			Spawn.Key->SetSpawnCheck();
		}
		
		// Call spawning function
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ARandHouse::Spawning, 1.0f, true);
	}
}

void ARandHouse::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
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
			if (const ABasePickup* Pickup = Cast<ABasePickup>(Actor))
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

void ARandHouse::Spawning()
{
	for (const auto& Spawn : PointPoolMap)
	{
		if(Spawn.Key->GetCurrSpawnAmt() >= Spawn.Key->MaxSpawnAmount ||
			Spawn.Key->GetSpawnCheck() == false)
		{
			continue;
		}
		
		if (ABaseAI* SpawnedAI = Spawn.Value->PoolSpawnFromComponent(Spawn.Key))
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

	for (const auto& DollAI : DollArray)
	{
		DollAI->AudioEnemies = AudiArray;
	}
}



