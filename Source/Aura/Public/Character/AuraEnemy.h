// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	
	//AEnemy 类实现了 IEnemyInterface 接口，并提供了 HighlightActor 和 UnHighlightActor 的具体实现。
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
protected:
	virtual void BeginPlay() override;
};
