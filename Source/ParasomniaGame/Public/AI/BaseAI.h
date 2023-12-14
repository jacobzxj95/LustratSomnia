#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include <Art/EnemyAnimInstance.h>
#include <AI/BaseAIController.h>
#include "BaseAI.generated.h"

UCLASS()
class PARASOMNIAGAME_API ABaseAI : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool bGotLit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		USkeletalMeshComponent* OutlineMesh;

	UFUNCTION()
		virtual void GotLight();

	UFUNCTION(BlueprintCallable)
		virtual void Dead();
};