#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BTTask_ClearBlackBoardValue.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_ClearBlackBoardValue : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
		FBlackboardKeySelector BlackboardKey;
};
