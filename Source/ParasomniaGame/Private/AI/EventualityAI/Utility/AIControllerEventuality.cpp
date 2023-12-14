#include "AI/EventualityAI/Utility/AIControllerEventuality.h"

void AAIControllerEventuality::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
}