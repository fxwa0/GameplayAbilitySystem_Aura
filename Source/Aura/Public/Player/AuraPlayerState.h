// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//返回AttributeSet，用于获取角色的属性集。
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
protected:
	//UAbilitySystemComponent 是Unreal Engine中用于管理游戏能力系统（Gameplay Ability System, GAS）的核心组件，负责处理技能、效果、属性等。
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//UAttributeSet 是GAS中用于定义和管理角色属性的组件，通常包含生命值、法力值、攻击力等属性。
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
