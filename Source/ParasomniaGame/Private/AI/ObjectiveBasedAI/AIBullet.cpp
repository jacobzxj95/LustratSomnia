#include "AI/ObjectiveBasedAI/AIBullet.h"

AAIBullet::AAIBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	Sphere->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(Sphere);

	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void AAIBullet::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAIBullet::OnOverlapBegin);
}

void AAIBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += DeltaTime * RotateRate;
	SetActorRotation(NewRotation);
	Mesh->SetWorldScale3D(Mesh->GetComponentScale() + DeltaTime * ScaleRate);
	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AAIBullet::DestroyAfterTimer, DespawnDelay, false);
	UnusedHandle.Invalidate();
}

void AAIBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {
	Destroy();
}

void AAIBullet::DestroyAfterTimer() {
	Destroy();
}