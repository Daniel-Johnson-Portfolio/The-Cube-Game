﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget_Hud.h"
#include "Components/Button.h"
#include "HUD_Cube.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UHUD_Cube : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void EnableWinText();
	void DisableWinText();
	void ToggleAiFollow();
	void DefaultHintText();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> _WinText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> _CubeAiButton;

	UPROPERTY()
	bool bCubesFollowing = true;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> _PuzzleHintText;

protected:
	void NativeOnInitialized() override;
};