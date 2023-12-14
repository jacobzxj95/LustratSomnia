#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIControllerSuddenness.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIControllerSuddenness : public ABaseAIController
{
	GENERATED_BODY()

		public:

			void BeginPlay() override;

			UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
			class UBehaviorTree* BT;
};
