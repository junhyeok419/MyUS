#pragma once

#include "GameObject/GameObject.h"
#include "Component/Effect.h"

enum class EBasicPattern
{
	None,		// 비활성화 
	Ready,		// 명령대기 
	Stand,		// 정지
	End
};

enum class EAlertPattern
{
	None,		// 비활성화
	Ready,		// 명령대기 
	Stand,		// 정지
	Move,		// 이동 
	End
};

enum class ECombatPattern
{
	None,		// 비활성화
	Ready,		// 명령대기 
	Stand,		// 정지
	Dash,		// 대쉬
	Guard,		// 가드
	Attack,		// 공격 
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
	CSharedPtr<class CColliderBox2D>	m_Body;					// 오브젝트끼리 충돌되는 충돌체 
	CSharedPtr<class CColliderBox2D>	m_HitCollider;			// 피해를 받는 충돌체 
	CSharedPtr<class CColliderSphere2D>	m_AlertCollider;		// 경계 충돌체
	CSharedPtr<class CColliderSphere2D>	m_CombatCollider;		// 전투 충돌체
	CSharedPtr<class CColliderBox2D>	m_AttackCollider;		// 공격 충돌체
private:
	float m_HP;
	EObjectDir m_PrevAnimDir;			// 애니메이션이 처음 실행될 당시 방향 
	EObjectDir m_AnimDir;				// 애니메이션 방향
	EObjectDir m_PlayerDir;				// 플레이어를 향하는 방향
private:
	bool m_Die;							// 죽은 상태 
	bool m_Hit;							// 피격 상태
	bool m_Alert;						// 경계 상태 (플레이어 방향 등 감지)
	bool m_Attack;						// 공격 중
	bool m_Slash;						// 실제 베기동작중
	bool m_Dash;
	float m_BlockTime;					// 가드 성공 시, 밀려나는 시간 
	float m_HitTime;					// 피격 상태 
	float m_ActionTime;					// 패턴 실행 시간 
	float m_AttackColliderLifeTime;		// 공격 충돌체 남아있는 시간 
	bool m_GuardBreak;					// 가드브레이크 상태 
	bool m_Bigkilled;					// 카운터로 인한 빅킬
	bool m_Target;						// 빅킬 타겟 
	EBasicPattern m_BasicPattern;		// 기본 패턴
	EAlertPattern m_AlertPattern;		// 경계 패턴
	ECombatPattern m_CombatPattern;		// 전투 패턴 
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
	// 노티파이 
	void Slash();
	void Attack();
	void Afterimage();
public:
	void AttackEnd();
	void DashEnd();
	void Die();
public:
	// 충돌 
	void CollisionBeginCognition(const CollisionResult& result);
	void CollisionEndCognition(const CollisionResult& result);
	void CollisionBeginObject(const CollisionResult& result);
	void CollisionEndObject(const CollisionResult& result);
	void CollisionBeginAttack(const CollisionResult& result);
};

