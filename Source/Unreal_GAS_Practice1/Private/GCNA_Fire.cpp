// Fill out your copyright notice in the Description page of Project Settings.


#include "GCNA_Fire.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AGCNA_Fire::AGCNA_Fire()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Fireball"));
    bAutoDestroyOnRemove = true;
}

bool AGCNA_Fire::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    if (MyTarget)
    {
        FVector HitLocation = MyTarget->GetActorLocation();

        const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
        if (HitResult)
        {
            HitLocation = HitResult->ImpactPoint;
        }

        if (SpawnedVFX.IsValid())
        {
            SpawnedVFX->SetWorldLocation(HitLocation);
            SpawnedVFX->Activate(true);
        }
        else
        {
            SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                FireVFX,
                HitLocation,
                MyTarget->GetActorRotation()
            );
        }
        return true;
    }
    return false;
}

bool AGCNA_Fire::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedVFX.IsValid())
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}
	return true;
}
