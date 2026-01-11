// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHPWidget::UpdateHP(float InValue, float MaxValue)
{
	MaxHP->SetText(FText::AsNumber(FMath::RoundToInt(MaxValue)));
	CurrentHP->SetText(FText::AsNumber(FMath::RoundToInt(InValue)));
	HPBar->SetPercent(InValue / MaxValue);
}