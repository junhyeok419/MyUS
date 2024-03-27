#pragma once

#include "GameObject/GameObject.h"
#include "Component/Effect.h"

enum class EPlayerSkills
{
	None,
	ThreeSequenceSlash,	// 삼연참
	DoubleEdge,			// 양날베기
	DashAttack,			// 돌진찌르기
	CounterAttack,		// 반격
	GhostMove,			// 귀신달리기
	GhostSlash,			// 귀신베기
	End
};

enum class EPlayerHitTypeByBoss
{
    None,
    Punch,      // 피격시:기본 / 가드시:기본 / 저스트가드 : 가능  
    Stomp,      // 피격시:제자리 / 가드시:기본 / 저스트가드:불가  
    Rush,       // 피격시:매우멀리 / 가드시 : 멀리 / 저스트가드 : 가능
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
	CSharedPtr<class CColliderBox2D>	m_Body;				// 오브젝트끼리 충돌되는 충돌체 
	CSharedPtr<class CColliderBox2D>	m_HitCollider;		// 피해를 받는 충돌체 
	CSharedPtr<class CColliderBox2D>	m_AttackCollider;   // 공격 충돌체 (닿는 몬스터는 모두 타격)
	CSharedPtr<class CColliderBox2D>	m_AttackSingleCollider; // 단일 공격 충돌체 (전용 스킬에서만)

	//CSharedPtr<class CNavigationAgent>	m_NavAgent;
private:
	float m_HP;
    float m_Stamina;
private:
	EPlayerSkills m_UseSkill;	// 현재 사용중인 기술 
	bool m_AutoMove;		// (대쉬 등에 의한)자동 이동 상태인지 
	bool m_Attack;			// 공격중인지
	float m_MoveAttack;		// 이동 중 공격중인지 판단 및 0.2초 셈
	int m_AttackCount;		// 삼연참 횟수
	float m_AttackTime;		// 삼연참 연타 가능시간 ( 최소 0.4초 지나야 연타 가능 )
private:
	bool m_PressUpKey;		// 이동 키 눌렸는지 
	bool m_PressDownKey;
	bool m_PressRightKey;
	bool m_PressLeftKey;
	bool m_PressSpaceBar;   // 스페이스바 눌렸는지 
	bool m_PressAttackKey;  // 공격 키 눌렸는지 
	// 설계 잘못해서 급하게 만든 변수들 
	bool m_PressUpKeyForGhostMove;
	bool m_PressDownKeyForGhostMove;
	bool m_PressRightKeyForGhostMove;
	bool m_PressLeftKeyForGhostMove;
private:
	bool m_DiagonalMove;	// 대각 이동인지 
	bool m_Dash;			// 대쉬 중인지 판단 
	float m_DashTime;		// 대쉬중 및 1초 셈
	bool m_Chain;			// 체인 가능한 타이밍인지 
	float m_ChainTime;      // 체인 타이밍에 노랗게 깜빡임
	bool m_Guard;			// 가드중인지 
	float m_BlockTime;		// 가드 성공시 정지시간
	bool m_DoubleEdge;		// 양날베기중인지 
	float m_AttackColliderLifeTime;		// 공격충돌체 사라지는 시간 
	float m_AttackSingleColliderLifeTime;		// 공격충돌체 사라지는 시간 
	bool m_ObjectCollision;	// 오브젝트끼리 충돌해서 밀려날 때 이동량에 따른 애니메이션 못바꾸게 하기 위함 
	float m_HitTime;		// 피격 상태 및 시간
	float m_JustGuardTime;  // 저스트가드 발동 가능 타이머
	bool m_JustGuard;		// 저스트가드 성공
	float m_CounterTime;	// 카운터 발동 가능 타이머 
	float m_CounterAttackTime;  // 카운터 어택 시간 
	bool m_CounterAttack;		// 카운터어택중인지
	float m_Invincible;		// 현재 무적시간  
	float m_MoveSoundTime;   // 발소리 갱신시간
	int m_GhostSlashCount;   // 귀신베기 횟수. max 4
	float m_GhostSlashUsable; // 귀신베기 발동 가능한 시간. 첫 타격을 시작한 이후 1초안에 이어나가야 한다. 그렇지않으면 취소됨  
	float m_GhostSlashTime;   // 귀신베기 사용 시간. 이것으로 돌진을 구현한다. 
	bool m_GhostSlashReady;
	bool m_GhostSlashSwipe;  // 이펙트 출력해야 하는지 
    EPlayerHitTypeByBoss m_HitTypeByBoss;         // 보스한테 맞았는지, 맞았다면 얼만큼 세기인지. 왜냐면 더 멀리 밀려나거나, 대미지 조정해야 하는 등의 이유 / 0은일반몹, 1~3에따라 달라짐 / 1은 제자리 / 2는 중간 / 3은 멀리 
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
	// 키리셋
	void ResetUpKey();
	void ResetDownKey();
	void ResetRightKey();
	void ResetLeftKey();
	void ResetAttackKey();
	void ResetGuardKey();

public:
	// 노티파이 
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
	// 애니메이션 앤드 
	void AttackEnd();
	void DashEnd();
public:
    float GetHP();
    float GetST();
private:
	// 충돌
	void CollisionBeginAttack(const CollisionResult& result);
	void CollisionBeginObject(const CollisionResult& result);
	void CollisionEndObject(const CollisionResult& result);
};

