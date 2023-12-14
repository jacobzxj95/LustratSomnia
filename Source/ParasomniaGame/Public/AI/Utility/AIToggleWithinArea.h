#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "AI/BaseAI.h"
#include "Actors/AIPoolSpawnPoint.h"
#include "Components/SpawnPoolComponent.h"
#include "Widgets/SlideInStunHint.h"
#include "Utility/BaseGameInstance.h"
#include "AIToggleWithinArea.generated.h"

class ABasePickup;

UCLASS()
class PARASOMNIAGAME_API AAIToggleWithinArea : public AActor
{
	GENERATED_BODY()
	
public:	

	AAIToggleWithinArea();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<AAIPoolSpawnPoint*> SpawnPointsWithin;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "AI")
		TArray<AActor*> SuddenTeleportPt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TArray<ABasePickup*> PickupArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<ABasePickup> PickupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USlideInStunHint* HintHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<USlideInStunHint> HintClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBaseGameInstance* GameInstance;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void Spawning();

protected:
	
	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
		ACharacter* Player;
	
	UPROPERTY()
		TArray<ABaseAI*> SpawnedAIArray;

	UPROPERTY()
		USpawnPoolComponent* SpawnPoolComponent;

	UPROPERTY()
		FTimerHandle SpawnTimerHandle;

	UPROPERTY()
		TMap<AAIPoolSpawnPoint*,USpawnPoolComponent*> PointPoolMap;
	
};
