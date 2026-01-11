// Fill out your copyright notice in the Description page of Project Settings.


#include "PracticeCharacter.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.h"

// Sets default values
APracticeCharacter::APracticeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

// Called when the game starts or when spawned
void APracticeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);	// 어빌리티 시스템 컴포넌트 초기화

		if (FireballClass)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(
					FireballClass,
					1,
					-1,
					this
				)
			);
		}
	}
}

// Called every frame
void APracticeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APracticeCharacter::OnAttack()
{
	if (AbilitySystemComponent && FireballClass)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(FireballClass);
	}
}

