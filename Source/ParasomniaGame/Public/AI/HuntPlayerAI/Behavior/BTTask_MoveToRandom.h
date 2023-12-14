#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <NavigationSystem.h>
#include <NavMesh/RecastNavMesh.h>
#include "BTTask_MoveToRandom.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_MoveToRandom : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Radius")
		float SearchRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Radius")
		FBlackboardKeySelector BlackboardKey;
};
