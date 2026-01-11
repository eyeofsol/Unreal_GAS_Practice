// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "HPWidget.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	HPWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HPWidget->SetupAttachment(RootComponent);
	HPWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("AttributeSet"));
}

void AEnemyActor::TestUpdateHP()
{
	EnemyAttributeSet->SetHealth(50.0f);
}

void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent && EnemyAttributeSet)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			EnemyAttributeSet->GetHealthAttribute()).AddUObject(this, &AEnemyActor::OnHealthChange);

		if (HPWidget->GetUserWidgetObject())
		{
			TObjectPtr<UHPWidget> Widget = Cast<UHPWidget>(HPWidget->GetUserWidgetObject());
			Widget->UpdateHP(EnemyAttributeSet->GetHealth(), EnemyAttributeSet->GetMaxHealth());
		}
	}
}

void AEnemyActor::OnHealthChange(const FOnAttributeChangeData& Data)
{
	if (HPWidget && EnemyAttributeSet)
	{
		TObjectPtr<UHPWidget> Widget = Cast<UHPWidget>(HPWidget->GetUserWidgetObject());
		Widget->UpdateHP(EnemyAttributeSet->GetHealth(), EnemyAttributeSet->GetMaxHealth());
	}
}