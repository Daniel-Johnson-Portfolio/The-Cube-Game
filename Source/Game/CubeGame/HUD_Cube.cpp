// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_Cube.h"
#include "Components/TextBlock.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"

void UHUD_Cube::NativeConstruct()
{
	Super::NativeConstruct();

	if(_WinText)
	{
		_WinText->SetText(FText::FromString("Won"));
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
	_PuzzleHintText->SetText(FText::FromString("Stack the Cubes on the platform"));
}


void UHUD_Cube::NativeOnInitialized()
{
	DisableWinText();
	_CubeAiButton->SetBackgroundColor(FLinearColor::Green);
	Super::NativeOnInitialized();
}
