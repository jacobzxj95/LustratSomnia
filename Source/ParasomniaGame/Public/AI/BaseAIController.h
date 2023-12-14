#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionTypes.h>
#include <Kismet/GameplayStatics.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>
#include <Perception/AISenseConfig_Touch.h>
#include <Perception/AISenseConfig_Prediction.h>
#include <Perception/AISenseConfig.h>
#include <Perception/AISense.h>
#include <Perception/AISense_Sight.h>
#include <Perception/AISense_Hearing.h>
#include <Perception/AISense_Touch.h>
#include <Perception/AISense_Prediction.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "GameFramework/Character.h"
#include "BaseAIController.generated.h"

UCLASS()
class PARASOMNIAGAME_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ABaseAIController();

	UFUNCTION()
		virtual void HandleSightCode(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
		virtual void HandleHearingCode(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
		virtual void HandleTouchCode(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
		virtual void HandlePredictionCode(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
		void ToggleBoolValue();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float PredictTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		bool IsByPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
		class AActor* Player;
};