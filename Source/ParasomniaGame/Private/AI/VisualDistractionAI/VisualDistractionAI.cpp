#include "AI/VisualDistractionAI/VisualDistractionAI.h"

void AVisualDistractionAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bGotLit)
		GotLight();
}