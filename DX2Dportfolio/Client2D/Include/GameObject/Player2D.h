#pragma once

#include "GameObject/GameObject.h"
#include "Component/Effect.h"

enum class EPlayerSkills
{
	None,
	ThreeSequenceSlash,	// �￬��
	DoubleEdge,			// �糯����
	DashAttack,			// �������
	CounterAttack,		// �ݰ�
	GhostMove,			// �ͽŴ޸���
	GhostSlash,			// �ͽź���
	End
};

enum class EPlayerHitTypeByBoss
{
    None,
    Punch,      // �ǰݽ�:�⺻ / �����:�⺻ / ����Ʈ���� : ����  
    Stomp,      // �ǰݽ�:���ڸ� / �����:�⺻ / ����Ʈ����:�Ұ�  
    Rush,       // �ǰݽ�:�ſ�ָ� / ����� : �ָ� / ����Ʈ���� : ����
    End
};

class CPlayer2D :
    public CGameObject
{
	friend class CScene;

protected:
	CPlayer2D();
	CPlayer2D(const CPlayer2D& Obj);
	virtual ~CPlayer2D();

private:
	CSharedPtr<class CSpriteComponent>	m_Sprite;
	//CSharedPtr<class CSceneComponent>	m_RightChild;
	//CSharedPtr<class CSpriteComponent>	m_SpriteChild;
	CSharedPtr<class CCameraComponent>	m_Camera;
	CSharedPtr<class CTargetArm>		m_Arm;
	CSharedPtr<class CColliderBox2D>	m_Body;				// ������Ʈ���� �浹�Ǵ� �浹ü 
	CSharedPtr<class CColliderBox2D>	m_HitCollider;		// ���ظ� �޴� �浹ü 
	CSharedPtr<class CColliderBox2D>	m_AttackCollider;   // ���� �浹ü (��� ���ʹ� ��� Ÿ��)
	CSharedPtr<class CColliderBox2D>	m_AttackSingleCollider; // ���� ���� �浹ü (���� ��ų������)

	//CSharedPtr<class CNavigationAgent>	m_NavAgent;
private:
	float m_HP;
    float m_Stamina;
private:
	EPlayerSkills m_UseSkill;	// ���� ������� ��� 
	bool m_AutoMove;		// (�뽬 � ����)�ڵ� �̵� �������� 
	bool m_Attack;			// ����������
	float m_MoveAttack;		// �̵� �� ���������� �Ǵ� �� 0.2�� ��
	int m_AttackCount;		// �￬�� Ƚ��
	float m_AttackTime;		// �￬�� ��Ÿ ���ɽð� ( �ּ� 0.4�� ������ ��Ÿ ���� )
private:
	bool m_PressUpKey;		// �̵� Ű ���ȴ��� 
	bool m_PressDownKey;
	bool m_PressRightKey;
	bool m_PressLeftKey;
	bool m_PressSpaceBar;   // �����̽��� ���ȴ��� 
	bool m_PressAttackKey;  // ���� Ű ���ȴ��� 
	// ���� �߸��ؼ� ���ϰ� ���� ������ 
	bool m_PressUpKeyForGhostMove;
	bool m_PressDownKeyForGhostMove;
	bool m_PressRightKeyForGhostMove;
	bool m_PressLeftKeyForGhostMove;
private:
	bool m_DiagonalMove;	// �밢 �̵����� 
	bool m_Dash;			// �뽬 ������ �Ǵ� 
	float m_DashTime;		// �뽬�� �� 1�� ��
	bool m_Chain;			// ü�� ������ Ÿ�̹����� 
	float m_ChainTime;      // ü�� Ÿ�ֿ̹� ����� ������
	bool m_Guard;			// ���������� 
	float m_BlockTime;		// ���� ������ �����ð�
	bool m_DoubleEdge;		// �糯���������� 
	float m_AttackColliderLifeTime;		// �����浹ü ������� �ð� 
	float m_AttackSingleColliderLifeTime;		// �����浹ü ������� �ð� 
	bool m_ObjectCollision;	// ������Ʈ���� �浹�ؼ� �з��� �� �̵����� ���� �ִϸ��̼� ���ٲٰ� �ϱ� ���� 
	float m_HitTime;		// �ǰ� ���� �� �ð�
	float m_JustGuardTime;  // ����Ʈ���� �ߵ� ���� Ÿ�̸�
	bool m_JustGuard;		// ����Ʈ���� ����
	float m_CounterTime;	// ī���� �ߵ� ���� Ÿ�̸� 
	float m_CounterAttackTime;  // ī���� ���� �ð� 
	bool m_CounterAttack;		// ī���;���������
	float m_Invincible;		// ���� �����ð�  
	float m_MoveSoundTime;   // �߼Ҹ� ���Žð�
	int m_GhostSlashCount;   // �ͽź��� Ƚ��. max 4
	float m_GhostSlashUsable; // �ͽź��� �ߵ� ������ �ð�. ù Ÿ���� ������ ���� 1�ʾȿ� �̾���� �Ѵ�. �׷��������� ��ҵ�  
	float m_GhostSlashTime;   // �ͽź��� ��� �ð�. �̰����� ������ �����Ѵ�. 
	bool m_GhostSlashReady;
	bool m_GhostSlashSwipe;  // ����Ʈ ����ؾ� �ϴ��� 
    EPlayerHitTypeByBoss m_HitTypeByBoss;         // �������� �¾Ҵ���, �¾Ҵٸ� ��ŭ ��������. �ֳĸ� �� �ָ� �з����ų�, ����� �����ؾ� �ϴ� ���� ���� / 0���Ϲݸ�, 1~3������ �޶��� / 1�� ���ڸ� / 2�� �߰� / 3�� �ָ� 
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CPlayer2D* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
public:
	virtual EHitState InflictDamage(int Damage, int IsBoss = 0);
public:
	// Ű����
	void ResetUpKey();
	void ResetDownKey();
	void ResetRightKey();
	void ResetLeftKey();
	void ResetAttackKey();
	void ResetGuardKey();

public:
	// ��Ƽ���� 
	void MoveUp();
	void MoveDown();
	void Rotation();
	void RotationInv();
	void Fire();
	void MoveClick();
	void Dash();
	void Guard();
	void DoubleEdge_Pre();
	void DoubleEdge();
	void GhostMove();
	void GhostSlash();
	void ChainInactive();
	void ChainActive();
public:
	void Attack();
private:
	void Afterimage();
	void DashAttack();
private:
	// �ִϸ��̼� �ص� 
	void AttackEnd();
	void DashEnd();
public:
    float GetHP();
    float GetST();
private:
	// �浹
	void CollisionBeginAttack(const CollisionResult& result);
	void CollisionBeginObject(const CollisionResult& result);
	void CollisionEndObject(const CollisionResult& result);
};

