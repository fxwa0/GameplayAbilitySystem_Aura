// Copyright Druid Mechanics


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	// 保存控制器引用
	WidgetController = InWidgetController;
	// 触发事件（由蓝图实现） - 比如更新血条图片的宽度
	WidgetControllerSet();
}
