// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Cube.h"

#include <string>

#include "Components/TextBlock.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"

void UHUD_Cube::NativeConstruct()
{
	Super::NativeConstruct();

	if(_WinText)
	{
		_WinText->SetText(FText::FromString(_LevelCompleteText));
	}
	if(_PuzzleHintText)
	{
		DefaultHintText();
	}
}

void UHUD_Cube::EnableWinText()
{
	_WinText->SetIsEnabled(true);
	_WinText->SetRenderOpacity(1.0f);
}
void UHUD_Cube::DisableWinText()
{
	_WinText->SetIsEnabled(false);
	_WinText->SetRenderOpacity(0.0f);
}

void UHUD_Cube::ToggleAiFollow()
{
	if (_CubeAiButton->GetBackgroundColor() == FLinearColor::Green)
	{
		_CubeAiButton->SetBackgroundColor(FLinearColor::Red);
	}
	else
	{
		_CubeAiButton->SetBackgroundColor(FLinearColor::Green);
	}
}

void UHUD_Cube::DefaultHintText()
{
	_PuzzleHintText->SetText(FText::FromString(_DefaultHintText));
}

void UHUD_Cube::EndLevelHintText()
{
	_PuzzleHintText->SetText(FText::FromString(_EndLevelHintText));
}

void UHUD_Cube::UpdateCoinsText(int coins)
{
	if (_CurrentCoinsText)
	{
		FString CoinsString = FString::Printf(TEXT("%s %d"), *_CurrentCoinText, coins);
		_CurrentCoinsText->SetText(FText::FromString(CoinsString));
	}
}


void UHUD_Cube::NativeOnInitialized()
{
	DisableWinText();
	_CubeAiButton->SetBackgroundColor(FLinearColor::Green);
	Super::NativeOnInitialized();
}
