#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIControllerDoll.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerDoll : public ABaseAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		class UBehaviorTree* BehaviorTree;

protected:

	virtual void BeginPlay() override;

};
