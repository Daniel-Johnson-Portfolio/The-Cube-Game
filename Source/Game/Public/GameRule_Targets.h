// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Targets.generated.h"

class UTargetComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGRTargetsRequestTragetSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME_API UGameRule_Targets : public UGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRule_Targets();

	static inline FGRTargetsRequestTragetSignature OnRequestTargets;
	virtual void Init() override;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTargetComponent>> _Targets;

	int AmountRemaining; 

private:
	UFUNCTION()
	void Handle_TargetRegistered(UTargetComponent* target);
	UFUNCTION()
	void Handle_TargetDestoryed(UTargetComponent* target, AController* causer, int targetValue);
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
