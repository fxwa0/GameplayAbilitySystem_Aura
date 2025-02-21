// Copyright Druid Mechanics


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	//设置网格体（Mesh）对特定碰撞通道（Collision Channel）的响应方式。ECC_Visibility：碰撞通道，表示“可见性”通道。通常用于光线检测（Line Trace）或可见性检测。ECR_Block：碰撞响应方式，表示“阻挡”（Block）。当碰撞发生时，射线会被阻挡，并返回命中结果。
	//这意味着，当有射线（如光标检测射线）使用 ECC_Visibility 通道时，如果射线碰到这个网格体，射线会被阻挡，并返回命中结果。
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	//CreateDefaultSubobject 是Unreal Engine中的一个函数，用于在对象的构造函数中创建默认的子对象（Subobject）。子对象是附加到父对象（通常是Actor或Component）上的组件或对象。
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//设置这个 AbilitySystemComponent 为可复制的（Replicated），意味着在多玩家游戏中，这个组件会在服务器和客户端之间同步。
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
	//启用或禁用网格体的自定义深度渲染.通常用于需要高亮显示物体轮廓的场景，例如选中敌人、交互物体等。
	GetMesh()->SetRenderCustomDepth(true);
	//设置网格体的自定义深度模板值
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
