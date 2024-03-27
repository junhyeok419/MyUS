#pragma once

#include "GameObject/GameObject.h"


// ���帶ũ�� ũ��� �ؽ��ĸ��� �ٸ��Ƿ� ��ũ�� �����ϴ� ���忡�� �����Ѵ�. 

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
