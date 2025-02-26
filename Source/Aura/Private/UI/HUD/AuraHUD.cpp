// Copyright Druid Mechanics


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
// 获取或创建OverlayWidgetController（单例模式）
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		// 动态创建控制器实例（基于配置的蓝图类）
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		// 注入依赖参数
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

// 初始化覆盖UI系统
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// 检查配置是否有效（防止编辑器未配置导致崩溃）- 检查是否在蓝图里设置了血条UI的模板
	checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized,please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget Controller Class uninitialized,please fill out BP_AuraHUD"))
	// 创建UI控件实例 - 创建血条UI实例（类似把预制体生成到游戏中）
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	// 构造控制器参数并获取控制器实例 - 把玩家控制器、属性系统等传给控制器（让控制器知道该管谁的血条）
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	// 将控制器绑定到血条UI（告诉血条："你的数据由这个控制器提供"）
	OverlayWidget->SetWidgetController(WidgetController);
	
	WidgetController->BrodcastInitialValues();
	// 把血条显示到屏幕上
	Widget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}
