#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAIController.h"
#include "AIC_AuditoryDistraction.generated.h"

UCLASS()
class PARASOMNIAGAME_API AAIC_AuditoryDistraction : public ABaseAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UBehaviorTree* BT;

protected:

	virtual void BeginPlay() override;

};
