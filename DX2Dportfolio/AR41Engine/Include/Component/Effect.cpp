#include "Effect.h"
#include "../GameObject/GameObject.h"

CEffect::CEffect()
	: m_EffectType(EEffectType::Once)
	, m_Duration(0.f)
	, m_Time(0.f)
{
	SetTypeID<CEffect>();

	m_ComponentTypeName = "Effect";

}

CEffect::CEffect(const CEffect& component)
		: CSpriteComponent(component)
{
}

CEffect::~CEffect()
{
}

EEffectType CEffect::GetEffectType() const
{
	return m_EffectType;
}

void CEffect::SetEffectType(EEffectType Type)
{
	m_EffectType = Type;

	/*
		어떤 이펙트 애니메이션이든, 끝나면
		같은 함수(AnimationEnd)가 호출되어 지워줄 수 있도록 한다.
	*/
    if(m_Animation)
	    m_Animation->SetCurrentEndFunction(m_Animation->GetCurrentAnimationName("sdsd"), this, &CEffect::AnimationEnd);
}

void CEffect::SetDuration(float Duration)
{
	m_Duration = Duration;
}

void CEffect::AnimationEnd()
{

	// 이펙트타입이 'Once'일 경우, 애니메이션 종료 시 이펙트를 제거한다.
	if (m_EffectType == EEffectType::Once)
	{
		Destroy();
	}
}

void CEffect::Start()
{
	CSpriteComponent::Start();
}

bool CEffect::Init()
{
	CSpriteComponent::Init();

	return true;
}

void CEffect::Update(float DeltaTime)
{
	CSpriteComponent::Update(DeltaTime);

	// 이펙트 타입에 따라서 다른 업데이트 처리를 해야한다.

	/*
		이펙트 타입이 Duration(지속)일 경우 시간 체크를 하여,
		지속 시간을 초과할 경우에 제거한다.
	*/
	if (m_EffectType == EEffectType::Duration)
	{
		m_Time += DeltaTime;

		if (m_Time >= m_Duration)
			Destroy();
	}
}

void CEffect::PostUpdate(float DeltaTime)
{
	CSpriteComponent::PostUpdate(DeltaTime);
}

void CEffect::Render()
{
	CSpriteComponent::Render();
}

CEffect* CEffect::Clone() const
{
	return nullptr;
}

void CEffect::Save(FILE* File)
{
}

void CEffect::Load(FILE* File)
{
}
