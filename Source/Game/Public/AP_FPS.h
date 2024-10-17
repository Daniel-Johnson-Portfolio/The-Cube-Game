

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "GameFramework/Character.h"
#include "Weapon_Base.h"
#include "AP_FPS.generated.h"


class UHealthComponent;
class UCameraComponent;

UCLASS(Abstract)
class GAME_API AAP_FPS : public ACharacter, public IMyInterface
{
public:
	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	virtual void Input_FirePressed_Implementation() override;
	virtual void Input_FireReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;
protected:
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _WeaponRef;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
	
private:
	GENERATED_BODY()
	UFUNCTION()
	void Handle_HealthDead(AController * causer);
	UFUNCTION()
	void Handle_HealthDamaged(float current, float max, float change);

public:
	// Sets default values for this character's properties
	AAP_FPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
