#include "AI/BaseAI.h"

ABaseAI::ABaseAI()
{
	PrimaryActorTick.bCanEverTick = true;
	bGotLit = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	OutlineMesh = CreateDefaultSubobject<USkeletalMeshComponent>("OutlineMesh");
	OutlineMesh->SetupAttachment(GetMesh());

	GetMesh()->SetWorldLocation(FVector3d(0.0f, 0.0f, -90.0f));
	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void ABaseAI::GotLight()
{
	Destroy();
}

void ABaseAI::Dead()
{
	Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance())->bIsDead = true;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->Deactivate();
}