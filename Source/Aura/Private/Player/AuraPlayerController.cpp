// Copyright Druid Mechanics


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//bReplicates 是 AActor 类的一个布尔属性，用于控制该 Actor 是否在网络游戏中复制
	//当 bReplicates 设置为 true 时，该 Actor 会在服务器和客户端之间同步。
	//通过复制，PlayerController 的状态和属性可以在服务器和客户端之间同步，确保所有玩家看到相同的游戏世界。。
    //例如，玩家的输入、状态变化（如生命值、位置等）都需要通过网络同步。
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	//FHitResult 是 UE 中的一个结构体，用于存储光线检测（Line Trace）或碰撞检测的结果信息。bBlockingHit：是否检测到了阻挡（即是否命中物体）。GetActor()：返回命中的 AActor 对象（即被检测到的物体）。其他信息：如命中位置、法线、碰撞组件等。
	FHitResult CursorHit;
	//从光标位置发射一条射线，检测光标下的物体，结果存储在 CursorHit 中。ECC_Visibility：碰撞通道（Collision Channel），这里使用 Visibility 通道，表示检测可见的物体。false：是否忽略复杂的碰撞检测（false 表示不忽略）。CursorHit：存储检测结果的 FHitResult 变量。
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	//如果射线没有检测到物体（！bBlockingHit 为 false），则直接返回，不进行后续处理。
	if (!CursorHit.bBlockingHit) return;

	//将 ThisActor 的值赋给 LastActor，记录上一帧的光标下的物体。
	LastActor = ThisActor;
	//将当前帧光标下的物体转换为 IEnemyInterface 类型，并赋值给 ThisActor。
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/**
	 * Line trace from cursor.There are several scenarios:
	 * A.LastActor is null && ThisActor is null
	 *   - Do nothing
	 * B.LastActor is null && ThisActor is valid
	 *   - Highlight ThisActor
	 * C.LastActor is valid && ThisActor is null
	 *   - UnHighlight LastActor
	 * D.Both actors are valid, but LastActor != ThisActor
	 *   - UnHighlight LastActor, and Highlight ThisActor
	 * E.Both actors are valid , and are the same actor
	 *   - Do nothing
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Case B 表示上一帧没有物体，当前帧有物体，高亮当前帧的物体。
			ThisActor->HighlightActor();
		}
		else
		{
			//Case A 表示上一帧和当前帧光标下都没有物体，不做任何处理。
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C 表示上一帧有物体，当前帧没有物体，取消高亮上一帧的物体。
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D LastActor 和 ThisActor 都不为 nullptr，且不是同一个物体，表示光标从一个物体移动到另一个物体，取消高亮上一个物体，高亮当前物体。
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E LastActor 和 ThisActor 都不为 nullptr，且是同一个物体，表示光标仍然在同一个物体上，不做任何处理。
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//check() 是一个用于调试的宏，主要用于验证某个条件是否为真。如果条件为假，check() 会触发断言（Assertion），导致程序崩溃并输出错误信息
	//它帮助开发者在开发阶段快速发现和定位问题，遵循“快速失败”原则。
	//使用 check() 可以提高代码的健壮性和可读性，避免隐藏错误。
    //在发布版本中，check() 通常会被禁用，因此它不会影响最终产品的性能。
    check(AuraContext);

	//GetLocalPlayer()：这是一个函数，返回当前 ULocalPlayer 对象的指针。
	//ULocalPlayer 是 Unreal Engine 中表示本地玩家的类，通常用于管理玩家相关的数据和子系统。
	//ULocalPlayer::GetSubsystem<T>()：这是一个模板函数，用于从 ULocalPlayer 中获取指定类型的子系统实例。
	//UEnhancedInputLocalPlayerSubsystem：这是 Unreal Engine 的增强输入系统（Enhanced Input System）的一部分，用于管理本地玩家的输入映射和输入动作。获取该子系统后，可以注册输入映射、绑定输入动作等。
	//子系统是引擎的一部分，提供了一种结构化的方式来访问和管理特定功能模块，而无需手动创建或管理这些模块的生命周期。
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	//将一个输入映射上下文（Input Mapping Context）添加到增强输入子系统（Enhanced Input Subsystem）中，并指定其优先级。
	//在游戏运行时，可以根据需要动态添加或移除输入映射上下文。例如，在角色进入战斗状态时，添加战斗相关的输入映射；在角色退出战斗状态时，移除战斗相关的输入映射。
	//优先级是一个整数值，用于决定多个输入映射上下文的生效顺序。数值越小，优先级越高。如果多个输入映射上下文对同一个输入设备有冲突的映射，优先级高的上下文会覆盖优先级低的上下文。
	Subsystem->AddMappingContext(AuraContext,0);

	//显示鼠标光标。APlayerController 类的一个布尔属性。通常在需要鼠标交互的界面（如菜单、UI）中启用。
	bShowMouseCursor = true;
	//设置默认的鼠标光标样式（通常是箭头）。APlayerController 类的一个属性，类型为 EMouseCursor 枚举。
	DefaultMouseCursor = EMouseCursor::Default;

	//创建一个 FInputModeGameAndUI 对象，用于配置输入模式。FInputModeGameAndUI 是一个结构体，表示“游戏和UI”输入模式。这种输入模式允许同时处理游戏输入（如角色移动）和UI输入（如点击按钮）。当游戏需要同时支持游戏操作和UI交互时使用。
	FInputModeGameAndUI InputModeData;
	//设置鼠标是否锁定到视口（Viewport）。EMouseLockMode::DoNotLock 表示不锁定鼠标到视口，允许鼠标自由移动。当需要鼠标可以自由移动到屏幕外时使用。其他可选值包括：LockAlways：始终锁定鼠标到视口。LockOnCapture：仅在捕获输入时锁定鼠标。
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//设置是否在捕获输入时隐藏鼠标光标。当设置为 false 时，即使在捕获输入（如点击UI按钮）时，鼠标光标也不会隐藏。当需要鼠标光标始终可见时使用。
	InputModeData.SetHideCursorDuringCapture(false);
	//SetInputMode() 是 APlayerController 类的一个成员函数，用于设置当前的输入模式。将配置好的输入模式应用到玩家控制器。
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//UInputComponent 是一个基类组件，用于处理玩家输入。负责绑定输入事件（如按键、鼠标、手柄）到具体的游戏逻辑。
	//UEnhancedInputComponent 是 UInputComponent 的子类，专为增强输入系统设计。提供更灵活的输入处理方式，支持输入动作（UInputAction）和输入映射上下文（UInputMappingContext）。支持上下文敏感的输入、输入修饰键（如 Shift、Ctrl）等高级功能。
	//通过类型转换，确保使用增强输入系统的功能。
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    //将 MoveAction 输入动作绑定到 AAuraPlayerController::Move 函数。ETriggerEvent::Triggered 表示当输入动作触发时（如按下按键）调用 Move 函数。
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	
}

//当玩家触发 "Move" 输入（如按下 WASD 键或移动手柄摇杆）时，增强输入系统会将输入值封装为 FInputActionValue 并传递给 Move 函数。
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//从 InputActionValue 中获取二维向量（FVector2D），表示输入的方向。例如，W 键对应 (0, 1)，S 键对应 (0, -1)。
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	//获取玩家控制器的旋转角度（FRotator），用于确定角色的朝向，控制器的旋转通常表示玩家视角的方向（如摄像机的朝向）。
	const FRotator Rotation = GetControlRotation();
	//创建一个只包含 Yaw（偏航角）的旋转角度，忽略 Pitch（俯仰角）和 Roll（翻滚角）。玩家移动通常是基于水平旋转的，而不需要考虑视角的上下倾斜（Pitch）。例如，玩家看向天空时，"前进" 仍然是沿着地面的前方方向。
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	//根据 Yaw 旋转角度计算角色前进方向（FVector）。FRotationMatrix 将旋转角度转换为旋转矩阵，GetUnitAxis(EAxis::X) 获取 X 轴的单位向量（即前进方向）。
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//根据 Yaw 旋转角度计算角色右移方向（FVector）。GetUnitAxis(EAxis::Y) 获取 Y 轴的单位向量（即右方向）。
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//获取当前由该控制器控制的 Pawn（通常是玩家角色）。
	//将输入方向应用到角色上，使其移动。ForwardDirection 和 RightDirection 是移动方向，InputAxisVector.Y 和 InputAxisVector.X 是输入强度。
	//AddMovementInput 是 APawn 的内置方法，用于将输入向量添加到 Pawn 的移动组件中（如 CharacterMovementComponent）。
	//通过将输入值（InputAxisVector）乘以方向向量，玩家的输入会根据控制器的旋转方向转换为实际的移动方向。
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}
