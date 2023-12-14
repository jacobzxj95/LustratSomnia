#include "AI/ObjectiveBasedAI/Utility/AIControllerObjectiveBased.h"

void AAIControllerObjectiveBased::BeginPlay() {
	RunBehaviorTree(BT);
	Super::BeginPlay();
}