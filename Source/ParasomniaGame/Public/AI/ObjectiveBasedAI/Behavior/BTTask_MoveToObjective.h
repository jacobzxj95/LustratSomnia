#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include "BTTask_MoveToObjective.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_MoveToObjective : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<class AActor> ObjectiveClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		AActor* Objective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AcceptanceRadius;
};
