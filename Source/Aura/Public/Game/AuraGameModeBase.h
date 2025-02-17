/*在虚幻引擎中，Game Mode（游戏模式）是一个核心类，用于定义游戏的规则和逻辑。
它负责管理游戏的核心行为，包括玩家如何加入游戏、游戏如何进行、胜负条件等。
Game Mode 的主要功能包括：
1.定义游戏规则：决定游戏的玩法，例如是单人游戏、多人合作还是对战。设置游戏的胜利条件和失败条件。
2.管理玩家和角色：控制玩家如何生成（Spawn）以及生成什么类型的角色（Pawn）。指定默认的玩家控制器（Player Controller）和角色类（Pawn Class）。
3.游戏状态管理：与Game State类配合，跟踪游戏的全局状态，例如分数、时间、玩家数量等。
4.关卡初始化：在关卡加载时初始化游戏相关的设置。控制游戏开始、结束和重启的逻辑。
5多人游戏支持：在多人游戏中，Game Mode 运行在服务器上，确保所有客户端遵循相同的规则。
Game Mode 的组成部分：
Default Pawn Class：玩家控制的默认角色。
Player Controller Class：玩家控制器的默认类。
HUD Class：游戏界面的默认类。
Game State Class：用于跟踪游戏状态的类。
Player State Class：用于跟踪玩家状态的类。
使用场景：
如果你在开发一个射击游戏，Game Mode 可以定义玩家如何重生、如何计算分数以及游戏何时结束。
如果你在开发一个开放世界游戏，Game Mode 可以管理玩家的初始生成位置和游戏的整体流程。
注意事项：
每个关卡可以指定一个 Game Mode，如果没有指定，则使用项目设置中的默认 Game Mode。
在多人游戏中，Game Mode 只在服务器上运行，客户端通过复制（Replication）获取游戏状态。
总结来说，Game Mode 是 UE 中管理游戏规则和逻辑的核心类，开发者可以通过它定义游戏的玩法、玩家行为和全局状态。*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
};
