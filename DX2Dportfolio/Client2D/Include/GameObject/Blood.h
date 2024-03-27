#pragma once

#include "GameObject/GameObject.h"

// 피는 뿌려질 때 움직여야 하므로, 업데이트에서 피 방향에 따라 자동으로 움직이도록 한다. 

// 혈흔을 남기기 위해 혈흔 오브젝트를 생성하도록 한다. 

enum class EBloodLevel
{
	None,
	Low,			// 삼연참 1-2타
	Middle,			// 삼연참 3타, 양날베기, 돌진베기,	 플레이어피격			
	High,			// 반격, 귀신베기									
	End
};

class CBlood :
	public CGameObject
{
	friend class CScene;

protected:
	CBlood();
	CBlood(const CBlood& Obj);
	virtual ~CBlood();

private:
	CSharedPtr<class CEffect>	m_Effect;
	EBloodLevel m_BloodLevel;
	int		m_MarkCount;		// 혈흔의 개수, 생성될 때 세팅하도록 한다. 
	int		m_SmallMarkCount;		
	int		m_MidiumMarkCount;
	int		m_BigMarkCount;
	float	m_MarkTime;         // 각 혈흔이 뿌려질 때 시간차. 0.1초 정도
	Vector2	m_AreaLT;		
	Vector2 m_AreaRB;
public:
	CEffect* GetEffect();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CBlood* Clone()    const;
public:
	void SetBloodLevel(EBloodLevel Level); 
	void CreateBloodArea(Vector3 Pos, Vector2 Offset);
private:
	void CreateMark();
};
