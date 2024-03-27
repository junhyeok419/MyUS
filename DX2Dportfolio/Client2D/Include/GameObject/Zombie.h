#pragma once

#include "GameObject/GameObject.h"
#include "Component/Effect.h"

enum class EBasicPattern
{
	None,		// ��Ȱ��ȭ 
	Ready,		// ��ɴ�� 
	Stand,		// ����
	End
};

enum class EAlertPattern
{
	None,		// ��Ȱ��ȭ
	Ready,		// ��ɴ�� 
	Stand,		// ����
	Move,		// �̵� 
	End
};

enum class ECombatPattern
{
	None,		// ��Ȱ��ȭ
	Ready,		// ��ɴ�� 
	Stand,		// ����
	Dash,		// �뽬
	Guard,		// ����
	Attack,		// ���� 
	End
};

class CZombie :
	public CGameObject
{
	friend class CScene;

protected:
	CZombie();
	CZombie(const CZombie& Obj);
	virtual ~CZombie();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	CSharedPtr<class CColliderBox2D>	m_Body;					// ������Ʈ���� �浹�Ǵ� �浹ü 
	CSharedPtr<class CColliderBox2D>	m_HitCollider;			// ���ظ� �޴� �浹ü 
	CSharedPtr<class CColliderSphere2D>	m_AlertCollider;		// ��� �浹ü
	CSharedPtr<class CColliderSphere2D>	m_CombatCollider;		// ���� �浹ü
	CSharedPtr<class CColliderBox2D>	m_AttackCollider;		// ���� �浹ü
private:
	float m_HP;
	EObjectDir m_PrevAnimDir;			// �ִϸ��̼��� ó�� ����� ��� ���� 
	EObjectDir m_AnimDir;				// �ִϸ��̼� ����
	EObjectDir m_PlayerDir;				// �÷��̾ ���ϴ� ����
private:
	bool m_Die;							// ���� ���� 
	bool m_Hit;							// �ǰ� ����
	bool m_Alert;						// ��� ���� (�÷��̾� ���� �� ����)
	bool m_Attack;						// ���� ��
	bool m_Slash;						// ���� ���⵿����
	bool m_Dash;
	float m_BlockTime;					// ���� ���� ��, �з����� �ð� 
	float m_HitTime;					// �ǰ� ���� 
	float m_ActionTime;					// ���� ���� �ð� 
	float m_AttackColliderLifeTime;		// ���� �浹ü �����ִ� �ð� 
	bool m_GuardBreak;					// ����극��ũ ���� 
	bool m_Bigkilled;					// ī���ͷ� ���� ��ų
	bool m_Target;						// ��ų Ÿ�� 
	EBasicPattern m_BasicPattern;		// �⺻ ����
	EAlertPattern m_AlertPattern;		// ��� ����
	ECombatPattern m_CombatPattern;		// ���� ���� 
    bool m_Clean;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CZombie* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
public:
    virtual EHitState InflictDamage(int Damage, int IsBoss = 0);
public:
	void MoveUp();
	void MoveDown();
	void Rotation();
	void RotationInv();
public:
	// ��Ƽ���� 
	void Slash();
	void Attack();
	void Afterimage();
public:
	void AttackEnd();
	void DashEnd();
	void Die();
public:
	// �浹 
	void CollisionBeginCognition(const CollisionResult& result);
	void CollisionEndCognition(const CollisionResult& result);
	void CollisionBeginObject(const CollisionResult& result);
	void CollisionEndObject(const CollisionResult& result);
	void CollisionBeginAttack(const CollisionResult& result);
};

