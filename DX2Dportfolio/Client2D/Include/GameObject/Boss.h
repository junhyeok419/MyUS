#pragma once

#include "GameObject/GameObject.h"
#include "Component/Effect.h"
#include "Zombie.h"

enum class EBossRangePattern
{
    None,
    Ready,
    Move,      // 30%
    Stomp,     // 30%
    Rush,      // 40%
    End
};

enum class EBossClosePattern
{
    None,
    Ready,
    End
};

enum class EBossMeleePattern
{
    None,
    Ready,
    Guard,          // 25%
    Punch,          // 40%
    Stomp,          // 35%
    End
};

class CBoss :
    public CGameObject
{
    friend class CScene;
protected:
    CBoss();
    CBoss(const CBoss& Obj);
    virtual ~CBoss();

private:
    CSharedPtr<class CSpriteComponent>	m_Sprite;
    CSharedPtr<class CColliderBox2D>	m_Body;					// 오브젝트끼리 충돌되는 충돌체 
    CSharedPtr<class CColliderBox2D>	m_HitCollider;			// 피해를 받는 충돌체 
    CSharedPtr<class CColliderSphere2D>	m_RangeCollider;		// 원거리 패턴용 충돌체
    CSharedPtr<class CColliderSphere2D>	m_MeleeCollider;		// 근거리 패턴용 충돌체
    CSharedPtr<class CColliderBox2D>	m_AttackCollider;		// 공격 충돌체
private:
    float m_HP;
    EObjectDir m_PrevAnimDir;			// 애니메이션이 처음 실행될 당시 방향 
    EObjectDir m_AnimDir;				// 애니메이션 방향
    EObjectDir m_PlayerDir;				// 플레이어를 향하는 방향
private:
    bool m_Die;							// 죽은 상태 
    bool m_Hit;							// 피격 상태
    bool m_Range;						// 원거리 상태 (플레이어 방향 등 감지)
    bool m_StompAttack;					// 스톰프 공격 중
    std::vector<bool> m_StompReady;					// 스톰프 준비 여부
    Vector3 m_StompPos;                   // 스톰프 준비중에 결정하는 스톰프 위치 
    bool m_RushAttack;                  // 돌진 공격 중
    bool m_RushReady;                   // 돌진 준비 여부 
    bool m_PunchAttack;
    bool m_Guard;
    bool m_Dash;
    float m_BlockTime;					// 가드 성공 시, 밀려나는 시간 
    float m_HitTime;					// 피격 상태 
    float m_ActionTime;					// 패턴 실행 시간 
    float m_AttackColliderLifeTime;		// 공격 충돌체 남아있는 시간 
    bool m_GuardBreak;					// 가드브레이크 상태 
    bool m_Bigkilled;					// 카운터로 인한 빅킬
    bool m_Target;						// 빅킬 타겟 
    bool m_AfterAttack;					// 공격 후 무조건 대쉬하게 만드는 변수 
    bool m_SuperArmor;
    EBossRangePattern m_RangePattern;		// 기본 패턴
    EBossMeleePattern m_MeleePattern;		// 경계 패턴
    float m_IsShowIntro;
    float m_PlayIntroTime;
    float m_DieTime;
public:
    // 반드시 오브젝트 생성 직후 호출
    void ShowIntro();
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CBoss* Clone()    const;
    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
public:
    virtual EHitState InflictDamage(int Damage, int IsBoss);
public:
    void MoveUp();
    void MoveDown();
    void Rotation();
    void RotationInv();
public:
    // 노티파이 
    void Stomp();
    void Rush();
    void Attack();
    void Afterimage();
public:
    void AttackEnd();
    void RushEnd();
    void Die();
    void Intro2();
    void PlaySound_FallDown();
public:
    // 충돌 
    void CollisionBeginCognition(const CollisionResult& result);
    void CollisionEndCognition(const CollisionResult& result);
    void CollisionBeginObject(const CollisionResult& result);
    void CollisionEndObject(const CollisionResult& result);
    void CollisionBeginAttack(const CollisionResult& result);
};

