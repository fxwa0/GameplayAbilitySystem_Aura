// Copyright Druid Mechanics
//继承自 AHUD，管理游戏界面（HUD），负责创建和初始化UI控件及其控制器。
//这是游戏的HUD类，负责管理叠加层UI（如血条、法力条）。代码中创建了OverlayWidget和OverlayWidgetController，并初始化它们。需要解释HUD的作用，控件器的创建过程，以及如何将UI元素添加到视口。
/**
*3.1 初始化阶段
1.游戏启动
AAuraHUD::BeginPlay() 被调用，但此处未实现具体逻辑（可能由其他类触发初始化）。
2.调用 InitOverlay
在其他类（如 PlayerController）中调用 AAuraHUD::InitOverlay，传入 PlayerController、PlayerState 等组件。
3.创建UI控件
使用 OverlayWidgetClass 配置的蓝图类创建 UAuraUserWidget 实例。
将实例赋值给 OverlayWidget 成员变量。
4.构造控制器参数
将传入的组件封装到 FWidgetControllerParams 结构体。
5.获取控制器实例
调用 GetOverlayWidgetController，若控制器未创建则动态生成（基于 OverlayWidgetControllerClass 配置的蓝图类）。
通过 SetWidgetControllerParams 注入参数。
6.绑定与显示
将控制器绑定到UI控件（OverlayWidget->SetWidgetController）。
将UI控件添加到视口（AddToViewport）。
3.2 运行时数据交互
1.UI更新：
UOverlayWidgetController 监听 AbilitySystemComponent 或 AttributeSet 的数据变化（如生命值更新），通过事件驱动UI刷新。
2.用户输入：
PlayerController 处理输入事件，通过控制器修改游戏状态（如释放技能）。

1.玩家被攻击 → 属性系统（GAS）更新血量值（例如从100→80）
2.OverlayWidgetController 监听到血量变化 → 触发OnHealthChanged事件
3.血条UI 通过蓝图绑定了这个事件 → 动态调整血条长度到80%
4.玩家看到血条缩短 → 视觉反馈受伤效果

游戏启动
│
├── AuraHUD 初始化
│   ├── 创建血条UI（OverlayWidget）
│   └── 创建控制器（OverlayWidgetController）
│       ├── 绑定玩家数据（控制器知道该管谁）
│       ├── 读取初始血量（显示满血）
│       └── 监听血量变化（准备实时更新）
│
└── 血条UI（蓝图）
	├── 图片控件（显示血条长度）
	└── 文本控件（显示"HP: 100"）
		│
		└── 当控制器绑定后（WidgetControllerSet事件）
			├── 获取初始血量 → 设置血条长度
			└── 绑定OnHealthChanged事件 → 血量变化时更新

1.AuraHUD 是总导演，负责生成血条UI和它的管家（控制器）。
2.OverlayWidgetController 是管家，时刻盯着玩家的血量变化，并通知UI更新。
3.血条UI（蓝图） 是演员，根据管家的指令调整自己的外观。
4.属性系统（GAS） 是后台数据，管家通过它获取最新血量。

整个过程就像：
导演（HUD）雇了一个管家（Controller）和一个演员（UI）。
管家每天盯着后台数据（GAS），如果发现玩家受伤（血量变化），立刻打电话给演员："快把血条缩短！"
演员接到电话后，马上调整自己的外观。

*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	// 覆盖UI控件实例（血条、蓝条所在的UI容器）
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	// 获取或创建控制器（获取管理血条逻辑的"控制器")
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	// 初始化UI系统(初始化血条UI（比如玩家进入游戏时显示血条）)
	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);
protected:
	virtual void BeginPlay() override;
private:
	// 可配置的覆盖UI蓝图类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	// 覆盖UI的逻辑控制器实例
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	// 可配置的控制器蓝图类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
