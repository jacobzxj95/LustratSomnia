#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include <AI/ObjectiveBasedAI/ObjectiveBasedAI.h>
#include <AI/ObjectiveBasedLargeAI/ObjectiveBasedLargeAI.h>
#include <Kismet/GameplayStatics.h>
#include <AI/ObjectiveBasedAI/AIBullet.h>
#include "BTTask_AttackObjective.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_AttackObjective : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
			TSubclassOf<class AActor> ObjectiveAIClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
			TSubclassOf<class AActor> ObjectiveLargeAIClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
			TSubclassOf<class AActor> BulletClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
			USoundBase* AttackSound;
};
