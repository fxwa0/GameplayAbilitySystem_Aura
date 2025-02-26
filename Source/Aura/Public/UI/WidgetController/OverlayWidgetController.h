// Copyright Druid Mechanics
//具体的叠加层控件器，处理属性变化（如生命值、法力值变化）。需要解释委托和事件如何在属性变化时更新UI。
/*1.初始化阶段：
游戏启动时，HUD创建OverlayWidget和OverlayWidgetController。
控制器调用BroadcastInitialValues，发送初始生命值和最大生命值到UI。
2.UI绑定阶段：
HealthGlobe控件的Event Widget Controller Set事件触发。
在蓝图中将OnHealthChanged和OnMaxHealthChanged委托绑定到更新UI的函数。
3.运行时更新：
当玩家生命值变化时（如受到伤害），UAuraAttributeSet更新属性值。
控制器监听到属性变化，触发OnHealthChanged.Broadcast(NewHealth)。
HealthGlobe控件中绑定的函数被调用，更新UI显示。

控制器（UOverlayWidgetController） 就像一名通讯员，负责监听游戏数据（如生命值）的变化，并大声通知所有关心的人（UI控件）。
UI控件（HealthGlobe） 就像一块电子显示屏，收到通知后立刻更新显示内容。
委托（OnHealthChanged） 是通讯员手中的喇叭，通过它喊出“生命值变了！现在是XX！”。
蓝图绑定 就是把显示屏的更新按钮连接到通讯员的喇叭，确保每次喊话都能自动刷新显示。
*/

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
//当**生命值（Health）**变化时触发，携带新的生命值（float NewHealth）。
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature,float,NewHealth);
//当**最大生命值（MaxHealth）**变化时触发，携带新的最大生命值（float NewMaxHealth）
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);

UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	//广播初始属性值到UI。
	virtual void BrodcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;
	//公开的委托实例，允许蓝图为这些委托绑定回调函数。
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
