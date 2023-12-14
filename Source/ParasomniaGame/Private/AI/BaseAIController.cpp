#include "AI/BaseAIController.h"

ABaseAIController::ABaseAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	PredictTime = 1.7f;
	IsByPlayer = false;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Blackboard)
	{
		GetBlackboardComponent()->SetValueAsBool("IsByPlayer", IsByPlayer);
	}
	AIPerceptionComponent->Deactivate();
}

void ABaseAIController::HandleSightCode(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type.Name.Compare(UAISense_Sight::StaticClass()->GetFName()))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			if (Actor == Player)
			{
				GetBlackboardComponent()->SetValueAsObject("TargetActor", Actor);
			}
			else
			{
				GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
			}
		}
		else
		{
			GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
			UAISense_Prediction::RequestPawnPredictionEvent(GetPawn(), Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0)), PredictTime);
		}
	}
}

void ABaseAIController::HandleHearingCode(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type.Name.Compare(UAISense_Hearing::StaticClass()->GetFName()))
	{
		GetBlackboardComponent()->SetValueAsVector("TargetLocation", Stimulus.StimulusLocation);
	}
}

void ABaseAIController::HandleTouchCode(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type.Name.Compare(UAISense_Touch::StaticClass()->GetFName()))
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

void ABaseAIController::HandlePredictionCode(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.Type.Name.Compare(UAISense_Prediction::StaticClass()->GetFName()))
	{
		GetBlackboardComponent()->SetValueAsVector("LastKnownLocation", Stimulus.StimulusLocation);
	}
}

void ABaseAIController::ToggleBoolValue()
{
	IsByPlayer = !IsByPlayer;
	GetBlackboardComponent()->SetValueAsBool("IsByPlayer", IsByPlayer);
}