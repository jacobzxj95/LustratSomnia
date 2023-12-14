#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Actors/BasePlayer.h>
#include <GameFramework/Character.h>
#include "GameFramework/PlayerController.h"
#include <AudioDevice.h>
#include <Widgets/WBP_LoseMenu.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "Blueprint/UserWidget.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include "BTTask_Jumpscare.generated.h"

UCLASS()
class PARASOMNIAGAME_API UBTTask_Jumpscare : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBTNodeResult::Type ReceiveExecuteAI(AAIController* OwnerController, APawn* ControlledPawn);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UWBP_LoseMenu* DeathScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<UWBP_LoseMenu> DeathScreenClass;

	UFUNCTION()
		void CallHUD();

	bool bIsPlayerDead = false;
};
