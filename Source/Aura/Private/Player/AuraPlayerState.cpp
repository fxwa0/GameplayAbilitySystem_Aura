// Copyright Druid Mechanics


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	//CreateDefaultSubobject 是Unreal Engine中的一个函数，用于在对象的构造函数中创建默认的子对象（Subobject）。子对象是附加到父对象（通常是Actor或Component）上的组件或对象。
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//设置这个 AbilitySystemComponent 为可复制的（Replicated），意味着在多玩家游戏中，这个组件会在服务器和客户端之间同步。
	AbilitySystemComponent->SetIsReplicated(true);
	//设置复制模式为Minimal，表示只复制必要的数据以减少网络流量。
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	//创建并初始化AttributeSet。
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	//设置网络更新频率为100次每秒。
	NetUpdateFrequency = 100.f;
	
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
