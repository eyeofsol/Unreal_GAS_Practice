// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "FiraballProjectile.generated.h"

UCLASS()
class UNREAL_GAS_PRACTICE1_API AFiraballProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFiraballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Fireball")
	TObjectPtr<class USphereComponent> Collision = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Fireball")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Fireball")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fireball")
	TSubclassOf<UGameplayEffect> BurnEffect = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fireball")
	TSubclassOf<UGameplayEffect> FireballEffect = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fireball")
	float Damage = 10.0f;
};
