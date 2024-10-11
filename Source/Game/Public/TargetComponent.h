// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"

class UHealthComponent;//Forward declare as we dont need any info about it
class UTargetComponent; //Forward declares itself so the delegate can be above the class and below the includes

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetRegisterdSignature, UTargetComponent*, target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTargetDestroyedSignature, UTargetComponent*, target, AController*, destroyer, int, targetValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTargetComponent();
	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnDestroyed; //Decarling signature, has to be public so it can be accessed and passed

	static inline FTargetRegisterdSignature OnTargetRegisterd;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _PointsValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _Health;


private:
	UFUNCTION()
	void Handle_GameRuleRequestTarget();
	UFUNCTION()
	void Handle_HealthDead(AController* causer); //Need to know who caused death
	
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
