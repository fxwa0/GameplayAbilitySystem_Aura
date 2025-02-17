// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//纯虚函数，子类必须实现。
	//多态性：通过接口类，可以统一调用不同类的相同函数。例如，AEnemy 和 ABoss 都可以实现 IEnemyInterface，但它们的高亮逻辑可以不同。
	//解耦：AAuraPlayerController 不需要知道具体的类（如 AEnemy），只需要知道它们实现了 IEnemyInterface 接口。
	//扩展性：如果需要增加新的敌人类型，只需要让新类实现 IEnemyInterface，而不需要修改 AAuraPlayerController 的代码。
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
