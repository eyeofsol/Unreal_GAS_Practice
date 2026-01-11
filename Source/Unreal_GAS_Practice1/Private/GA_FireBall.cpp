// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_FireBall.h"
#include "FiraballProjectile.h"

UGA_FireBall::UGA_FireBall()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_FireBall::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* Owner = ActorInfo->AvatarActor.Get();
	if (Owner)
	{
		FVector SpawnLocation = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.0f;
		FRotator SpawnRotation = Owner->GetActorRotation();

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Owner;
		SpawnParams.Instigator = Cast<APawn>(Owner);
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (Fireball)
			GetWorld()->SpawnActor<AFiraballProjectile>(
				Fireball,
				SpawnLocation,
				SpawnRotation,
				SpawnParams
			);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
