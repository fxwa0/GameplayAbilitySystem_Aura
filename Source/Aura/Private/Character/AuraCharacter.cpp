// Copyright Druid Mechanics


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	//设置角色的旋转是否与移动方向对齐。当 bOrientRotationToMovement 为 true 时，角色会自动旋转以面向移动方向。
	GetCharacterMovement()->bOrientRotationToMovement=true;
	//设置角色旋转的速度。RotationRate 是一个 FRotator，表示角色在 X、Y、Z 轴上的旋转速度（单位：度/秒）。这里设置为 (0.f, 400.f, 0.f)，表示角色仅在 Yaw 轴（垂直轴，即左右旋转）上以 400 度/秒的速度旋转。限制旋转速度可以避免角色旋转过快或过慢，提供更自然的转向体验。
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	//限制角色在一个平面内移动。当 bConstrainToPlane 为 true 时，角色的移动会被限制在一个平面内。在某些游戏类型中（如 2D 横版游戏或固定视角游戏），需要限制角色的移动范围，避免角色脱离预期的游戏区域。
	GetCharacterMovement()->bConstrainToPlane = true;
	//在游戏开始时将角色对齐到指定的平面。当 bSnapToPlaneAtStart 为 true 时，角色在游戏开始时会被强制对齐到约束的平面。确保角色在游戏开始时处于正确的位置，避免因初始位置偏差导致的问题。
	GetCharacterMovement()->bSnapToPlaneAtStart =true;

	//控制角色是否跟随控制器的俯仰（Pitch）旋转。当 bUseControllerRotationPitch 为 false 时，角色的俯仰旋转不会跟随控制器的旋转。在第三人称游戏中，通常希望角色的俯仰旋转由动画或摄像机控制，而不是直接跟随控制器。
	bUseControllerRotationPitch =false;
	//控制角色是否跟随控制器的横滚（Roll）旋转。当 bUseControllerRotationRoll 为 false 时，角色的横滚旋转不会跟随控制器的旋转。横滚旋转通常不用于角色控制，关闭它可以避免不必要的旋转行为。
	bUseControllerRotationRoll =false;
	//控制角色是否跟随控制器的偏航（Yaw）旋转。当 bUseControllerRotationYaw 为 false 时，角色的偏航旋转不会跟随控制器的旋转。在第三人称游戏中，角色的偏航旋转通常由 bOrientRotationToMovement 控制，而不是直接跟随控制器。
	bUseControllerRotationYaw =false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	//这个函数从 PlayerState 中获取 AbilitySystemComponent 和 AttributeSet，并将它们赋值给角色的 AbilitySystemComponent 和 AttributeSet。
	//然后调用 InitAbilityActorInfo 来初始化 AbilitySystemComponent，传递 PlayerState 和 this（角色）作为参数。这一步确保了 AbilitySystemComponent 知道哪个 Actor 拥有它，并且可以正确地应用技能和效果。
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	//将AbilitySystemComponent赋值给当前角色的AbilitySystemComponent。
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	//将AttributeSet赋值给当前角色的AttributeSet。
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
