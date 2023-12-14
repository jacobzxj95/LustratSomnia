#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "AI/AuditoryDistractionAI/AuditoryDistractionAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/DollJumpScare.h"
#include <GameFramework/Character.h>
#include <AI/DollAI/Utility/AIControllerDoll.h>
#include "DollAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API ADollAI : public ABaseAI
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TArray<AAuditoryDistractionAI*> AudioEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TArray<class USoundBase*> DollSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		bool bPushedByDoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float InterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float TimeBeforePushed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		class UDollJumpScare* ScareScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TSubclassOf<UDollJumpScare> ScareScreenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		USoundBase* JumpscareSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TArray<USoundBase*> StunSounds;

protected:

	virtual void BeginPlay() override;

public:

	ADollAI();

	virtual void Tick(float DeltaTime) override;

	void GotLight() override;

	UFUNCTION()
		void ChangeBools();

	UFUNCTION()
		void JumpScare();

	UFUNCTION()
		void RemoveJumpScare();

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
