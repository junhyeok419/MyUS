#pragma once

#include "GameObject/GameObject.h"

class CAfterimage :
	public CGameObject
{
	friend class CScene;

protected:
	CAfterimage();
	CAfterimage(const CAfterimage& Obj);
	virtual ~CAfterimage();

private:
	CSharedPtr<class CEffect>	m_Effect;
	float m_Time;
public:
	CEffect* GetEffect();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CAfterimage* Clone()    const;
};
