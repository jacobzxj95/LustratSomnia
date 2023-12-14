#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include <GameFramework/Character.h>
#include <Kismet/KismetMathLibrary.h>
#include "BTTask_VisualDistraction.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_VisualDistraction : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float InterpSpeed;
};
