#include "AI/HumanAI/Utility/AIControllerHuman.h"

void AAIControllerHuman::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
}