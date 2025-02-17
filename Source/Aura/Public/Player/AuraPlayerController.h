// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//通常用于处理玩家输入、管理玩家状态等。
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	//用于设置输入组件
	virtual void SetupInputComponent() override;
private:
	//UInputMappingContext用于定义输入映射上下文。表示一组输入动作的映射关系，将输入设备（如键盘、鼠标、手柄）与 UInputAction 关联。可以定义多个输入映射上下文，并根据游戏状态动态切换。
	//TObjectPtr是智能指针，用于安全地引用 UObject 派生类，安全、节能、清晰。
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	//UInputAction用于定义输入动作。表示一个具体的输入动作，例如“移动”、“跳跃”、“攻击”等。可以绑定到具体的输入设备（如键盘、鼠标、手柄）。
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	//FInputActionValue：这是一个结构体，表示输入动作的值（如按键的按下状态、摇杆的输入方向等）。
	//值传递，创建副本，开销较大（尤其是复杂对象），不会修改原始数据，小型数据类型（如 int、float、bool），或需要独立副本的场景（如果函数需要对参数进行修改，但不希望影响原始数据）。
	//引用传递，无需副本，开销较小，必须通过 const 引用保证不修改原始数据，复杂对象（如 FVector、FTransform、FInputActionValue），或需要直接操作原始数据的场景。
	void Move(const FInputActionValue& InputActionValue);

	//用于处理光标下的物体追踪和高亮逻辑。这个函数会在每帧调用，检查光标下的物体，并根据情况高亮或取消高亮物体。
	void CursorTrace();

	//存储上一帧光标下的物体。
	IEnemyInterface* LastActor;
	//存储当前帧光标下的物体。通过记录上一帧和当前帧的光标下的物体，可以判断是否需要取消高亮上一帧的物体，或者高亮当前帧的物体。
	IEnemyInterface* ThisActor;
};
