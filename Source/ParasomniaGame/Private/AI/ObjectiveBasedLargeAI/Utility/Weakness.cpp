#include "AI/ObjectiveBasedLargeAI/Utility/Weakness.h"

AWeakness::AWeakness()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SceneComponent->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(SceneComponent);
}