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
		� ����Ʈ �ִϸ��̼��̵�, ������
		���� �Լ�(AnimationEnd)�� ȣ��Ǿ� ������ �� �ֵ��� �Ѵ�.
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

	// ����ƮŸ���� 'Once'�� ���, �ִϸ��̼� ���� �� ����Ʈ�� �����Ѵ�.
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

	// ����Ʈ Ÿ�Կ� ���� �ٸ� ������Ʈ ó���� �ؾ��Ѵ�.

	/*
		����Ʈ Ÿ���� Duration(����)�� ��� �ð� üũ�� �Ͽ�,
		���� �ð��� �ʰ��� ��쿡 �����Ѵ�.
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
