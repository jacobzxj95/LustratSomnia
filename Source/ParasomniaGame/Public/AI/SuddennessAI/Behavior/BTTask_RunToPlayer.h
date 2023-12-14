#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include "BTTask_RunToPlayer.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_RunToPlayer : public UBTTaskNode
{
	GENERATED_BODY()

		public:

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
				float DistanceToEngage;

		protected:

			virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
			EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);
};
