// Fill out your copyright notice in the Description page of Project Settings.


#include "FiraballProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AFiraballProjectile::AFiraballProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(30.0f);
	Collision->OnComponentHit.AddDynamic(this, &AFiraballProjectile::OnHit);
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = Collision;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
}

// Called when the game starts or when spawned
void AFiraballProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFiraballProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetInstigator());

		if (TargetASC && SourceASC)
		{
			FGameplayTag BurnTag = FGameplayTag::RequestGameplayTag(FName("State.Burn"));
			bool bBurning = TargetASC->HasMatchingGameplayTag(BurnTag);

			if (FireballEffect)
			{
				FGameplayEffectSpecHandle DamageSpec = SourceASC->MakeOutgoingSpec(FireballEffect, 1.0f, SourceASC->MakeEffectContext());

				float FinalDamage = Damage;
				if (bBurning)
					FinalDamage *= 2.0f;

				DamageSpec.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Ability.Fireball.Damage")), -FinalDamage);

				SourceASC->ApplyGameplayEffectSpecToTarget(*DamageSpec.Data.Get(), TargetASC);
			}

			if (BurnEffect)
			{
				FGameplayEffectContextHandle BurnContext = SourceASC->MakeEffectContext();
				BurnContext.AddHitResult(Hit);

				FGameplayEffectSpecHandle BurnSpec = SourceASC->MakeOutgoingSpec(BurnEffect, 1.0f, BurnContext);
				SourceASC->ApplyGameplayEffectSpecToTarget(*BurnSpec.Data.Get(), TargetASC);
			}
		}
	}
	Destroy(); // 부딪히면 파괴
}

