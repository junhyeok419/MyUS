#pragma once

#include "GameObject/GameObject.h"


// 블러드마크의 크기는 텍스쳐마다 다르므로 마크를 생성하는 블러드에서 설정한다. 

class CBloodMark :
	public CGameObject
{
	friend class CScene;

protected:
	CBloodMark();
	CBloodMark(const CBloodMark& Obj);
	virtual ~CBloodMark();

private:
	CSharedPtr<class CEffect>	m_Effect;
	float	m_Time;   
public:
	CEffect* GetEffect();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBloodMark* Clone()    const;
};
