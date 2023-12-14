#include "AI/VisualDistractionAI/Utility/AIControllerVisualDistraction.h"

void AAIControllerVisualDistraction::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerVisualDistraction::HandleSightCode);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerVisualDistraction::HandleHearingCode);
}