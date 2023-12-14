#include "AI/HuntPlayerAI/Utility/AIControllerHuntPlayer.h"

AAIControllerHuntPlayer::AAIControllerHuntPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	PredictTime = 1.0f;
}

void AAIControllerHuntPlayer::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerHuntPlayer::HandleSightCode);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerHuntPlayer::HandleHearingCode);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerHuntPlayer::HandlePredictionCode);
}