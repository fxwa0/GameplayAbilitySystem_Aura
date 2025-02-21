// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	//OverlappedComponent: 当前 Actor 的碰撞体组件。OtherActor: 与之发生重叠的其他 Actor。OtherComp: 其他 Actor 的碰撞体组件。OtherBodyIndex: 其他碰撞体的索引。bFromSweep: 是否由扫掠检测触发。SweepResult: 扫掠检测的结果（包含碰撞点、法线等信息）。
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh;
	
};
