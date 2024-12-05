#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "CubeType.h"   
#include "CubeDataRow.generated.h"

USTRUCT(BlueprintType)
struct GAME_API FCubeDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cube Data")
	UCubeType* CubeDataAsset;
};