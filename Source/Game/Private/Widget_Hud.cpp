#include "Widget_Hud.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_Hud::NativeConstruct()
{
	Super::NativeConstruct();

	if(HealthBar)
	{
		HealthBar->SetPercent(1.0f);
	}
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString("Score: N/A"));
	}
}

void UWidget_Hud::UpdateHealth(float newHealthRatio)
{
	if(HealthBar)
	{
		
		HealthBar->SetPercent(HealthBar->Percent - newHealthRatio);
	}
}

void UWidget_Hud::UpdateScore(float newScore)
{
	if(ScoreText)
	{
	//	ScoreText->SetText(FText::FromString(FString::Printf("Score: %d", newScore)));
	}
}
