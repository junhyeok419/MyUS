#pragma once

#include "SpriteComponent.h"
class CEffect :
	public CSpriteComponent
{
	friend class CGameObject;
	friend class CScene;

protected:
	CEffect();
	CEffect(const CEffect& component);
	virtual ~CEffect();

private:
	EEffectType 	m_EffectType;	// ����Ʈ Ÿ��
	float			m_Duration;		// ����Ʈ ���ӽð�
	float			m_Time;			// �ð� üũ ����(������)

public:
	EEffectType GetEffectType() const;
	void SetEffectType(EEffectType Type);
	void SetDuration(float Duration);

private:
	void AnimationEnd();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CEffect* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

