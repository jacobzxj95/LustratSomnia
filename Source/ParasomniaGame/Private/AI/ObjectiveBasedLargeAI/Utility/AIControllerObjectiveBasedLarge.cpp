#include "AI/ObjectiveBasedLargeAI/Utility/AIControllerObjectiveBasedLarge.h"

void AAIControllerObjectiveBasedLarge::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
}