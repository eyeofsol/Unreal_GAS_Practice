// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"


class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class UNREAL_GAS_PRACTICE1_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateHP(float InValue, float MaxValue);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentHP = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxHP = nullptr;
};
