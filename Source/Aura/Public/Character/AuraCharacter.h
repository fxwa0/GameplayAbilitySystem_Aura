// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	//重写PossessedBy方法，用于处理角色被控制器控制时的逻辑。
	virtual void PossessedBy(AController* NewController) override;
	//重写OnRep_PlayerState方法，用于处理玩家状态复制时的逻辑。
	virtual void OnRep_PlayerState() override;
private:
	//void InitAbilityActorInfo();: 初始化技能Actor信息的方法。
	void InitAbilityActorInfo();
};
