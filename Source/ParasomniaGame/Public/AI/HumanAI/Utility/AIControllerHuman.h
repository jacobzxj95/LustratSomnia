#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIControllerHuman.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerHuman : public ABaseAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BT;
};
