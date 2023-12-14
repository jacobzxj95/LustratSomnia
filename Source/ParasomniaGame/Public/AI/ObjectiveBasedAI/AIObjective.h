#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Widgets/WBP_Turret.h"
#include "AI/ObjectiveBasedAI/AIBullet.h"
#include "Actors/BaseSentry.h"
#include "Actors/BasePlayer.h"
#include <Kismet/GameplayStatics.h>
#include "Components/ProgressBar.h"
#include "Widgets/WBP_LoseMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "AIObjective.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIObjective : public AActor
{
	GENERATED_BODY()

public:

	AAIObjective();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABaseSentry* SentryRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseSentry> SentryClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ABasePlayer* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABasePlayer> PlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AAIBullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWBP_LoseMenu* DeathRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UWBP_LoseMenu> DeathClass;

	UFUNCTION()
		virtual void BeginPlay() override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);
};
