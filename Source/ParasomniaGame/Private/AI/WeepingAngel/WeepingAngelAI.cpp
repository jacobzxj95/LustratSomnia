#include "AI/WeepingAngel/WeepingAngelAI.h"

void AWeepingAngelAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (WasRecentlyRendered(0.1f)) {
		GetCharacterMovement()->StopMovementImmediately();
	}
}