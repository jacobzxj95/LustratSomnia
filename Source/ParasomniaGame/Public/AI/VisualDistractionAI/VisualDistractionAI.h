#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include "VisualDistractionAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API AVisualDistractionAI : public ABaseAI
{
	GENERATED_BODY()
	
		public:

			virtual void Tick(float DeltaTime) override;
};
