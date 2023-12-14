#include "AI/SuddennessAI/Utility/AIControllerSuddenness.h"

void AAIControllerSuddenness::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
}