// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CubeType.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GAME_API UCubeType : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> _CubeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector _CubeSize = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _CubeMass = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> _CubeMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName UniqueID;
};
