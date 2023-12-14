#include "AI/DollAI/Utility/AIControllerDoll.h"

void AAIControllerDoll::BeginPlay()
{
	RunBehaviorTree(BehaviorTree);
	Super::BeginPlay();
}