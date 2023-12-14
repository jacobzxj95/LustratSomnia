// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AI/ObjectiveBasedAI/ObjectiveBasedAI.h"
#include "AI/ObjectiveBasedLargeAI/ObjectiveBasedLargeAI.h"
#include "Actors/BaseSentry.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

	CollisionComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseProjectile::DestroyProjectile, 1.0f, false);

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnOverlapEvent);

	UGameplayStatics::PlaySoundAtLocation(this,FiringSound,this->GetActorLocation());
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::DestroyProjectile()
{
	CollisionComp->SetRelativeScale3D(CollisionSize);
	K2_DestroyActor();
}

void ABaseProjectile::OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(ABaseSentry::StaticClass()) && OtherActor != this)
	{
		CollisionComp->SetWorldScale3D(CollisionSize);
		MeshComp->SetVisibility(false);
		ProjectileMovementComp->Velocity = FVector(0, 0, 0);
		UGameplayStatics::SpawnEmitterAtLocation(this, BulletHitEffect, this->GetActorLocation(), FRotator::ZeroRotator, CollisionSize);
		DealDamage(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void ABaseProjectile::DealDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AObjectiveBasedAI::StaticClass()))
	{
		Cast<AObjectiveBasedAI>(OtherActor)->Dead();
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseProjectile::K2_DestroyActor, 0.5f, false);
}

