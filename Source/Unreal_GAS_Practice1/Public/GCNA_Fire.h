// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GCNA_Fire.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_GAS_PRACTICE1_API AGCNA_Fire : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
public:
	AGCNA_Fire();

	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TObjectPtr<class UNiagaraSystem> FireVFX = nullptr;

private:
	TWeakObjectPtr<class UNiagaraComponent> SpawnedVFX = nullptr;
};
