#include "AI/WeepingAngel/Utility/AIControllerWeepingAngel.h"

void AAIControllerWeepingAngel::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerWeepingAngel::HandleSightCode);
}

void AAIControllerWeepingAngel::HandleSightCode(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type.Name.Compare(UAISense_Sight::StaticClass()->GetFName()))
	{
		if (Actor == Player)
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				GetBlackboardComponent()->SetValueAsObject("TargetActor", Actor);
			}
			else
			{
				GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
			}
		}
	}
}