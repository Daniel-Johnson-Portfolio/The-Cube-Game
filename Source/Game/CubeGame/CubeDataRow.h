#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" // Required for data table functionality
#include "CubeType.h"    // Include CubeDataAsset reference here
#include "CubeDataRow.generated.h"

USTRUCT(BlueprintType)
struct GAME_API FCubeDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Property to hold a reference to a CubeDataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cube Data")
	UCubeType* CubeDataAsset;
};