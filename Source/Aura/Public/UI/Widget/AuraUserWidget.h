// Copyright Druid Mechanics
//将UI与逻辑控制器（WidgetController）绑定。
//用户控件基类，设置控件器并触发事件。需要解释WidgetController的作用，以及如何在蓝图中响应事件。
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// 声明一个蓝图可调用的方法，用于设置WidgetController - 血条UI收到控制器后，触发蓝图事件
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	// 存储WidgetController的引用（通过UObject泛型类型）
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	// 受保护的蓝图可实现事件，用于控制器设置后的初始化逻辑 - 蓝图里可以在这里绑定血条图片和数值
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
