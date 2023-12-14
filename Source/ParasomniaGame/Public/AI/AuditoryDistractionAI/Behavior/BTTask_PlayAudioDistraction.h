#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include "BTTask_PlayAudioDistraction.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_PlayAudioDistraction : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Radius")
		TArray<USoundBase*> CloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Radius")
		TArray<USoundBase*> MediumSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search Radius")
		TArray<USoundBase*> FarSound;

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);
};
