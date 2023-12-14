#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/DollAI/DollAI.h"
#include "AI/AuditoryDistractionAI/AuditoryDistractionAI.h"
#include "Widgets/DollJumpScare.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include "BTTask_MovePlayerToDistractionAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_MovePlayerToDistractionAI : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		FName PlayerInRoomKey = "PlayerInRoom";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float InterpSpeed;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		class UDollJumpScare* ScareScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		TSubclassOf<UDollJumpScare> ScareScreenClass;*/

private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);
	
};
