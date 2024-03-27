#pragma once

#include "GameObject/GameObject.h"

// �Ǵ� �ѷ��� �� �������� �ϹǷ�, ������Ʈ���� �� ���⿡ ���� �ڵ����� �����̵��� �Ѵ�. 

// ������ ����� ���� ���� ������Ʈ�� �����ϵ��� �Ѵ�. 

enum class EBloodLevel
{
	None,
	Low,			// �￬�� 1-2Ÿ
	Middle,			// �￬�� 3Ÿ, �糯����, ��������,	 �÷��̾��ǰ�			
	High,			// �ݰ�, �ͽź���									
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
	int		m_MarkCount;		// ������ ����, ������ �� �����ϵ��� �Ѵ�. 
	int		m_SmallMarkCount;		
	int		m_MidiumMarkCount;
	int		m_BigMarkCount;
	float	m_MarkTime;         // �� ������ �ѷ��� �� �ð���. 0.1�� ����
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
