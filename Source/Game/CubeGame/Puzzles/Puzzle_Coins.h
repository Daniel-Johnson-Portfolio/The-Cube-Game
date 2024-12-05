#pragma once

#include "CoreMinimal.h"
#include "Game/CubeGame/CubeType.h"
#include "Game/CubeGame/PuzzleInterface.h"
#include "GameFramework/Actor.h"
#include "Puzzle_Coins.generated.h"

class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCoinCollectedSignature);

UCLASS()
class GAME_API APuzzle_Coins : public AActor, public IPuzzleInterface
{
	GENERATED_BODY()

public:
	APuzzle_Coins();

	UPROPERTY(BlueprintAssignable)
	FCoinCollectedSignature OnCoinCollected;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SetupActor")
	TObjectPtr<UStaticMeshComponent> _StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="SetupActor")
	TObjectPtr<USphereComponent> _Collider;

	FTimerHandle SpinTimer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="SetupActor")
	UCubeType* _CoinType;

	UFUNCTION(BlueprintNativeEvent, DisplayName= "OnCoinCollected")
	void OnCoinCollectedHook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual APuzzle_Coins* GetCoin_Implementation() override;

	void CoinSpin();

	UFUNCTION()
	void CoinPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
