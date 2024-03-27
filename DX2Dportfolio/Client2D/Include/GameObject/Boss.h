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
    CSharedPtr<class CColliderBox2D>	m_Body;					// ������Ʈ���� �浹�Ǵ� �浹ü 
    CSharedPtr<class CColliderBox2D>	m_HitCollider;			// ���ظ� �޴� �浹ü 
    CSharedPtr<class CColliderSphere2D>	m_RangeCollider;		// ���Ÿ� ���Ͽ� �浹ü
    CSharedPtr<class CColliderSphere2D>	m_MeleeCollider;		// �ٰŸ� ���Ͽ� �浹ü
    CSharedPtr<class CColliderBox2D>	m_AttackCollider;		// ���� �浹ü
private:
    float m_HP;
    EObjectDir m_PrevAnimDir;			// �ִϸ��̼��� ó�� ����� ��� ���� 
    EObjectDir m_AnimDir;				// �ִϸ��̼� ����
    EObjectDir m_PlayerDir;				// �÷��̾ ���ϴ� ����
private:
    bool m_Die;							// ���� ���� 
    bool m_Hit;							// �ǰ� ����
    bool m_Range;						// ���Ÿ� ���� (�÷��̾� ���� �� ����)
    bool m_StompAttack;					// ������ ���� ��
    std::vector<bool> m_StompReady;					// ������ �غ� ����
    Vector3 m_StompPos;                   // ������ �غ��߿� �����ϴ� ������ ��ġ 
    bool m_RushAttack;                  // ���� ���� ��
    bool m_RushReady;                   // ���� �غ� ���� 
    bool m_PunchAttack;
    bool m_Guard;
    bool m_Dash;
    float m_BlockTime;					// ���� ���� ��, �з����� �ð� 
    float m_HitTime;					// �ǰ� ���� 
    float m_ActionTime;					// ���� ���� �ð� 
    float m_AttackColliderLifeTime;		// ���� �浹ü �����ִ� �ð� 
    bool m_GuardBreak;					// ����극��ũ ���� 
    bool m_Bigkilled;					// ī���ͷ� ���� ��ų
    bool m_Target;						// ��ų Ÿ�� 
    bool m_AfterAttack;					// ���� �� ������ �뽬�ϰ� ����� ���� 
    bool m_SuperArmor;
    EBossRangePattern m_RangePattern;		// �⺻ ����
    EBossMeleePattern m_MeleePattern;		// ��� ����
    float m_IsShowIntro;
    float m_PlayIntroTime;
    float m_DieTime;
public:
    // �ݵ�� ������Ʈ ���� ���� ȣ��
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
    // ��Ƽ���� 
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
    // �浹 
    void CollisionBeginCognition(const CollisionResult& result);
    void CollisionEndCognition(const CollisionResult& result);
    void CollisionBeginObject(const CollisionResult& result);
    void CollisionEndObject(const CollisionResult& result);
    void CollisionBeginAttack(const CollisionResult& result);
};

