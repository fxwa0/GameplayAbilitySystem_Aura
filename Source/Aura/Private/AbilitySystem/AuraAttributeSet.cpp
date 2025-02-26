// Copyright Druid Mechanics


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	//该函数用于指定哪些属性需要在网络中进行复制。
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    //通过 DOREPLIFETIME_CONDITION_NOTIFY 宏，将 Health 属性标记为需要复制的属性。
	//UAuraAttributeSet: 当前类。Health: 需要复制的属性。COND_None: 复制条件，COND_None 表示无条件复制。REPNOTIFY_Always: 表示每次属性变化时都会触发通知（即使值没有变化）。
	//在多人游戏中，服务器需要将角色的属性同步到客户端。通过 GetLifetimeReplicatedProps，可以明确指定哪些属性需要同步，以及同步的条件和方式。
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//当 Health 属性在客户端复制时，该函数会被调用。通过 GAMEPLAYATTRIBUTE_REPNOTIFY 宏，触发属性变化的通知。
	//在客户端，当 Health 属性从服务器复制过来时，可能需要执行一些逻辑（如更新 UI、播放音效等）。通过 OnRep_Health，可以在属性变化时触发这些逻辑。
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana);
}


