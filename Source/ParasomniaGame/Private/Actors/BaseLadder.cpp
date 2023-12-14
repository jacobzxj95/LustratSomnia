// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseLadder.h"

// Sets default values
ABaseLadder::ABaseLadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LadderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LadderMesh"));
	LadderBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LadderBox"));
	LadderArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("LadderArrow"));

	LadderBox->SetupAttachment(LadderMesh);

	LadderArrow->SetupAttachment(LadderBox);

}

// Called when the game starts or when spawned
void ABaseLadder::BeginPlay()
{
	Super::BeginPlay();

	//OnActorBeginOverlap.AddDynamic(this, &ABaseLadder::ActorBeginOverlap);
	//OnActorEndOverlap.AddDynamic(this, &ABaseLadder::ActorEndOverlap);

	LadderBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseLadder::BoxBeginOverlap);
	LadderBox->OnComponentEndOverlap.AddDynamic(this, &ABaseLadder::BoxEndOverlap);
}

// Called every frame
void ABaseLadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABaseLadder::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ladder Begin Overlap"));
	ABasePlayer* Player = Cast<ABasePlayer>(OtherActor);
	if (Player)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ladder Begin Overlap"));
		Player->bOnLadder = true;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player is not Overlap"));
	}
}

void ABaseLadder::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABasePlayer* Player = Cast<ABasePlayer>(OtherActor);
	if (Player)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ladder End Overlap"));
		Player->bOnLadder = false;
		Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	else
	{

	}
}

