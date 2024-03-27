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
	EEffectType 	m_EffectType;	// 이펙트 타입
	float			m_Duration;		// 이펙트 지속시간
	float			m_Time;			// 시간 체크 변수(축적용)

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

