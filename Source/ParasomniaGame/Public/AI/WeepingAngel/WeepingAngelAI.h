#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"
#include <Perception/AISense_Touch.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Widgets/WBP_LoseMenu.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "WeepingAngelAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API AWeepingAngelAI : public ABaseAI
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;
};
