#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIControllerVisualDistraction.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerVisualDistraction : public ABaseAIController
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BT;
};