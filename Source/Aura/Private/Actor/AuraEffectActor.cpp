// Copyright Druid Mechanics


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//IAbilitySystemInterface 是 GAS 的核心接口，用于获取 AbilitySystemComponent。如果 OtherActor 实现了该接口，则将其转换为 IAbilitySystemInterface 指针。
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		//从 OtherActor 的 AbilitySystemComponent 中获取 UAuraAttributeSet 属性集。
		//GetAbilitySystemComponent() 返回 OtherActor 的 AbilitySystemComponent。GetAttributeSet(UAuraAttributeSet::StaticClass()) 获取 UAuraAttributeSet 类型的属性集。将结果转换为 UAuraAttributeSet 指针。
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		//将 const UAuraAttributeSet* 转换为非 const 指针。因为 SetHealth 函数需要修改属性值，而 const 指针不能调用非 const 成员函数。
		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth()+25.f);
		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana()-25.f);
		//销毁当前 AAuraEffectActor 实例。销毁 AAuraEffectActor，表示该效果已触发。
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::EndOverlap);
}


