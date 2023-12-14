#include "AI/AuditoryDistractionAI/Utility/AIC_AuditoryDistraction.h"

void AAIC_AuditoryDistraction::BeginPlay()
{
	RunBehaviorTree(BT);
	Super::BeginPlay();
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_AuditoryDistraction::HandleSightCode);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_AuditoryDistraction::HandleHearingCode);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC_AuditoryDistraction::HandlePredictionCode);
}