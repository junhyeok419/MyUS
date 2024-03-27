#include "Zombie.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/Effect.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Device.h"
#include "Afterimage.h"
#include "Blood.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "../Scene/MainSceneInfo.h"

CZombie::CZombie() :
	m_HP(270.f),
	m_BasicPattern(EBasicPattern::Ready),
	m_AlertPattern(EAlertPattern::None),
	m_CombatPattern(ECombatPattern::None),
	m_HitTime(0.f),
	m_AttackColliderLifeTime(0.f),
	m_Dash(false),
	m_Attack(false)
{
	SetTypeID<CZombie>();

	m_ObjectTypeName = "Zombie";


}

CZombie::CZombie(const CZombie& Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
}

CZombie::~CZombie()
{
}

void CZombie::Start()
{
	CGameObject::Start();
}

bool CZombie::Init()
{
	CGameObject::Init();

	m_Body = CreateComponent<CColliderBox2D>("Body");
	m_HitCollider = CreateComponent<CColliderBox2D>("HitCollider1");
	m_AlertCollider = CreateComponent<CColliderSphere2D>("Alert");
	m_CombatCollider = CreateComponent<CColliderSphere2D>("Combat");
	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

	m_Body->SetCollisionProfile("Object");
	m_HitCollider->SetCollisionProfile("Monster");
	m_AlertCollider->SetCollisionProfile("MonsterCognition");
	m_CombatCollider->SetCollisionProfile("MonsterCognition");

	m_Body->SetCollisionCallback<CZombie>(ECollision_Result::Collision, this, &CZombie::CollisionBeginObject);
	m_Body->SetCollisionCallback<CZombie>(ECollision_Result::Release, this, &CZombie::CollisionEndObject);
	m_AlertCollider->SetCollisionCallback<CZombie>(ECollision_Result::Collision, this, &CZombie::CollisionBeginCognition);
	m_AlertCollider->SetCollisionCallback<CZombie>(ECollision_Result::Release, this, &CZombie::CollisionEndCognition);
	m_CombatCollider->SetCollisionCallback<CZombie>(ECollision_Result::Collision, this, &CZombie::CollisionBeginCognition);
	m_CombatCollider->SetCollisionCallback<CZombie>(ECollision_Result::Release, this, &CZombie::CollisionEndCognition);

	SetRootComponent(m_HitCollider);

	m_HitCollider->AddChild(m_Body);
	m_HitCollider->AddChild(m_Sprite);
	m_HitCollider->AddChild(m_AlertCollider);
	m_HitCollider->AddChild(m_CombatCollider);

	m_HitCollider->SetBoxSize(40.f, 100.f);
	m_Body->SetBoxSize(40.f, 50.f);
	m_AlertCollider->SetRadius(500.f);
	m_CombatCollider->SetRadius(180.f);

	m_Body->AddRelativePosition(Vector2(0.f, -25.f));

	m_Sprite->SetPivot(0.5f, 0.f);
	
	m_Sprite->SetRelativePosition(0.f, -50.f);
	m_HitCollider->SetWorldPosition(1000.f, 600.f);

	m_Sprite->SetRenderLayerName("Monster");

	CMaterial* Material = m_Sprite->GetMaterial(0);

	//Material->SetRenderState("DepthDisable");

	// 애니메이션 추가
	CAnimation2D* Anim = m_Sprite->SetAnimation<CAnimation2D>("ZombieAnim");
	
	// 경계
	Anim->AddAnimation("AlertRight", "ZombieAlertRight", 1.5f);
	Anim->SetLoop("AlertRight", true);

	Anim->AddAnimation("AlertLeft", "ZombieAlertLeft", 1.5f);
	Anim->SetLoop("AlertLeft", true);

	// 정지
	Anim->AddAnimation("StandRight", "ZombieStandRight", 1.5f);
	Anim->SetLoop("StandRight", true);

	Anim->AddAnimation("StandLeft", "ZombieStandLeft", 1.5f);
	Anim->SetLoop("StandLeft", true);

	// 달리기
	Anim->AddAnimation("RunningRight", "ZombieRunningRight", 0.75f);
	Anim->SetLoop("RunningRight", true);

	Anim->AddAnimation("RunningLeft", "ZombieRunningLeft", 0.75f);
	Anim->SetLoop("RunningLeft", true);

	// 공격 준비
	Anim->AddAnimation("AttackReadyRight", "ZombieAttackReadyRight", 0.6f);
	Anim->SetLoop("AttackReadyRight", false);

	Anim->AddAnimation("AttackReadyLeft", "ZombieAttackReadyLeft", 0.6f);
	Anim->SetLoop("AttackReadyLeft", false);

	// 공격
	Anim->AddAnimation("AttackRight", "ZombieAttackRight", 1.f);
	Anim->SetLoop("AttackRight", false);
	Anim->AddCurrentNotify<CZombie>("AttackRight", "AttackRightAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackRight", "AttackRightAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackRight", "AttackRightAfterimage3", 2, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackRight", "AttackRightAfterimage4", 3, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackRight", "AttackRight", 4, this, &CZombie::Attack);


	Anim->AddAnimation("AttackLeft", "ZombieAttackLeft", 1.f);
	Anim->SetLoop("AttackLeft", false);
	Anim->AddCurrentNotify<CZombie>("AttackLeft", "AttackLeftAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackLeft", "AttackLeftAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackLeft", "AttackLeftAfterimage3", 2, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackLeft", "AttackLeftAfterimage4", 3, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("AttackLeft", "AttackLeft", 4, this, &CZombie::Attack);

	// 히트
	Anim->AddAnimation("HitByRight", "ZombieHitByRight", 0.5f);
	Anim->SetLoop("HitByRight", false);
	
	Anim->AddAnimation("HitByLeft", "ZombieHitByLeft", 0.5f);
	Anim->SetLoop("HitByLeft", false);
	

	// 사망
	Anim->AddAnimation("KilledByRight", "ZombieKilledByRight", 0.5f);
	Anim->SetLoop("KilledByRight", false);

	Anim->AddAnimation("KilledByLeft", "ZombieKilledByLeft", 0.5f);
	Anim->SetLoop("KilledByLeft", false);

	// 한방 사망
	Anim->AddAnimation("OneKilledByRight", "ZombieOneKilledByRight", 1.2f);
	Anim->SetLoop("OneKilledByRight", false);

	Anim->AddAnimation("OneKilledByLeft", "ZombieOneKilledByLeft", 1.2f);
	Anim->SetLoop("OneKilledByLeft", false);

	// 가드
	Anim->AddAnimation("GuardRight", "ZombieGuardRight", 1.f);
	Anim->SetLoop("GuardRight", true);

	Anim->AddAnimation("GuardLeft", "ZombieGuardLeft", 1.f);
	Anim->SetLoop("GuardLeft", true);

	Anim->AddAnimation("GuardUp", "ZombieGuardUp", 1.f);
	Anim->SetLoop("GuardUp", true);

	Anim->AddAnimation("GuardLeftUp", "ZombieGuardLeftUp", 1.f);
	Anim->SetLoop("GuardLeftUp", true);

	// 가드 성공 
	Anim->AddAnimation("BlockRight1", "ZombieBlockRight1", 0.3f);
	Anim->SetLoop("BlockRight1", false);
	Anim->AddCurrentNotify<CZombie>("BlockRight1", "BlockRight1Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockRight1", "BlockRight1Afterimage2", 1, this, &CZombie::Afterimage);
	
	Anim->AddAnimation("BlockRight2", "ZombieBlockRight2", 0.3f);
	Anim->SetLoop("BlockRight2", false);
	Anim->AddCurrentNotify<CZombie>("BlockRight2", "BlockRight2Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockRight2", "BlockRight2Afterimage2", 1, this, &CZombie::Afterimage);

	Anim->AddAnimation("BlockLeft1", "ZombieBlockLeft1", 0.3f);
	Anim->SetLoop("BlockLeft1", false);
	Anim->AddCurrentNotify<CZombie>("BlockLeft1", "BlockLeft1Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockLeft1", "BlockLeft1Afterimage2", 1, this, &CZombie::Afterimage);

	Anim->AddAnimation("BlockLeft2", "ZombieBlockLeft2", 0.3f);
	Anim->SetLoop("BlockLeft2", false);
	Anim->AddCurrentNotify<CZombie>("BlockLeft2", "BlockLeft2Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockLeft2", "BlockLeft2Afterimage2", 1, this, &CZombie::Afterimage);

	Anim->AddAnimation("BlockUp1", "ZombieBlockUp1", 0.3f);
	Anim->SetLoop("BlockUp1", false);
	Anim->AddCurrentNotify<CZombie>("BlockUp1", "BlockUp1Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockUp1", "BlockUp1Afterimage2", 1, this, &CZombie::Afterimage);

	Anim->AddAnimation("BlockUp2", "ZombieBlockUp2", 0.3f);
	Anim->SetLoop("BlockUp2", false);
	Anim->AddCurrentNotify<CZombie>("BlockUp2", "BlockUp2Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockUp2", "BlockUp2Afterimage2", 1, this, &CZombie::Afterimage);

	Anim->AddAnimation("BlockLeftUp1", "ZombieBlockLeftUp1", 0.3f);
	Anim->SetLoop("BlockLeftUp1", false);
	Anim->AddCurrentNotify<CZombie>("BlockLeftUp1", "BlockLeftUp1Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockLeftUp1", "BlockLeftUp1Afterimage2", 1, this, &CZombie::Afterimage);

	Anim->AddAnimation("BlockLeftUp2", "ZombieBlockLeftUp2", 0.3f);
	Anim->SetLoop("BlockLeftUp2", false);
	Anim->AddCurrentNotify<CZombie>("BlockLeftUp2", "BlockLeftUp2Afterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("BlockLeftUp2", "BlockLeftUp2Afterimage2", 1, this, &CZombie::Afterimage);

	// 탈출(회피 대쉬)
	Anim->AddAnimation("DashLeft", "ZombieDashLeft", 0.5f);
	Anim->AddCurrentNotify<CZombie>("DashLeft", "DashLeftAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashLeft", "DashLeftAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashLeft", "DashLeftAfterimage3", 2, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashLeft", "DashLeftAfterimage4", 3, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashLeft", "DashLeftAfterimage5", 4, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashLeft", "DashLeftAfterimage6", 5, this, &CZombie::Afterimage);

	Anim->AddAnimation("DashRight", "ZombieDashRight", 0.5f);
	Anim->AddCurrentNotify<CZombie>("DashRight", "DashRightAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashRight", "DashRightAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashRight", "DashRightAfterimage3", 2, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashRight", "DashRightAfterimage4", 3, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashRight", "DashRightAfterimage5", 4, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("DashRight", "DashRightAfterimage6", 5, this, &CZombie::Afterimage);

	// 가드브레이크
	Anim->AddAnimation("GuardBreakLeft", "ZombieGuardBreakLeft", 0.5f);
	Anim->AddCurrentNotify<CZombie>("GuardBreakLeft", "GuardBreakLeftAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakLeft", "GuardBreakLeftAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakLeft", "GuardBreakLeftAfterimage3", 2, this, &CZombie::Afterimage);

	Anim->AddAnimation("GuardBreakRight", "ZombieGuardBreakRight", 0.5f);
	Anim->AddCurrentNotify<CZombie>("GuardBreakRight", "GuardBreakRightAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakRight", "GuardBreakRightAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakRight", "GuardBreakRightAfterimage3", 2, this, &CZombie::Afterimage);

	Anim->AddAnimation("GuardBreakLeftUp", "ZombieGuardBreakLeftUp", 0.5f);
	Anim->AddCurrentNotify<CZombie>("GuardBreakLeftUp", "GuardBreakLeftUpAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakLeftUp", "GuardBreakLeftUpAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakLeftUp", "GuardBreakLeftUpAfterimage3", 2, this, &CZombie::Afterimage);

	Anim->AddAnimation("GuardBreakRightUp", "ZombieGuardBreakRightUp", 0.5f);
	Anim->AddCurrentNotify<CZombie>("GuardBreakRightUp", "GuardBreakRightUpAfterimage1", 0, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakRightUp", "GuardBreakRightUpAfterimage2", 1, this, &CZombie::Afterimage);
	Anim->AddCurrentNotify<CZombie>("GuardBreakRightUp", "GuardBreakRightUpAfterimage3", 2, this, &CZombie::Afterimage);

	// 애니메이션 엔드 함수
	Anim->SetCurrentEndFunction("AttackReadyLeft", this, &CZombie::Slash);
	Anim->SetCurrentEndFunction("AttackReadyRight", this, &CZombie::Slash);
	Anim->SetCurrentEndFunction("AttackLeft", this, &CZombie::AttackEnd);
	Anim->SetCurrentEndFunction("AttackRight", this, &CZombie::AttackEnd);
	Anim->SetCurrentEndFunction("KilledByLeft", this, &CZombie::Die);
	Anim->SetCurrentEndFunction("KilledByRight", this, &CZombie::Die);
	Anim->SetCurrentEndFunction("DashRight", this, &CZombie::DashEnd);
	Anim->SetCurrentEndFunction("DashLeft", this, &CZombie::DashEnd);
	Anim->SetCurrentEndFunction("OneKilledByLeft", this, &CZombie::Die);
	Anim->SetCurrentEndFunction("OneKilledByRight", this, &CZombie::Die);

	//Anim->SetCurrentAnimation("StandRight");
	Anim->SetCurrentAnimation("StandLeft");
	//Anim->SetCurrentAnimation("RunningRight");
	//Anim->SetCurrentAnimation("RunningLeft");
	//Anim->SetCurrentAnimation("AttackReadyRight");
	//Anim->SetCurrentAnimation("AttackRight");
	//Anim->SetCurrentAnimation("AttackReadyLeft");
	//Anim->SetCurrentAnimation("AttackLeft");
	//Anim->SetCurrentAnimation("HitByRight");
	//Anim->SetCurrentAnimation("HitByLeft");
	//Anim->SetCurrentAnimation("KilledByRight");
	//Anim->SetCurrentAnimation("KilledByLeft");
	//Anim->SetCurrentAnimation("OneKilledByRight");
	//Anim->SetCurrentAnimation("OneKilledByLeft");



	return true;
}

void CZombie::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	// 공격 충돌체를 0.1 초 후 삭제한다.
	// 남아있으면 시간차 공격으로 보일 수 있으므로 
	if (m_AttackCollider)
	{
		m_AttackColliderLifeTime += DeltaTime;

		if (m_AttackColliderLifeTime > 0.1f)
		{
			m_AttackColliderLifeTime = 0.f;
			m_AttackCollider->Destroy();
		}
	}

	if (m_Die)
		return;

    // 몬스터삭제
    if (m_Scene->IsCleanMonster())
    {
        return;
    }

	// 경계상태일 경우 '플레이어를 향하는 방향'을 구하여 자신의 애니메이션 방향으로 한다. 
	// 피격시에도 구하는 방향이 따로 있으므로 제외한다. 
	if (m_Alert && m_HitTime == 0.f)
	{
		float PosX = m_RootComponent->GetWorldPos().x;
		float PlayerPosX = m_Scene->GetSceneInfo()->GetPlayerObject()->GetRootComponent()->GetWorldPos().x;

		// 플레이어가 몬스터의 왼쪽에 있을 경우 
		if (PosX - PlayerPosX >= 0)
			m_AnimDir = EObjectDir::Left;
		// 플레이어가 몬스터의 오른쪽에 있을 경우 
		else
			m_AnimDir = EObjectDir::Right;
	}


	// 블락타임이 1초가 넘어가는건 가드브레이크 밖에 없다 
	// 이때 플레이어와 같이 색상 변경 
	if (m_HitTime < 1.2f && m_HitTime > 1.f)
	{
		m_Sprite->GetMaterial(0)->SetFullColorUnsignedChar(255, 255, 255, 0);
		m_Sprite->GetMaterial(0)->SetOnlyColor(true);
	}
	else
		m_Sprite->GetMaterial(0)->SetOnlyColor(false);
	
}

void CZombie::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_Die)
		return;

    // 몬스터삭제
    if (m_Scene->IsCleanMonster() && !m_Clean)
    {
        m_Clean = true;

        m_HP = 0.f;
        m_Hit = true;
        m_HitTime = 1.f;
        if (m_Body)
            m_Body->Destroy();
    }

	// 자신의 위치 대비 플레이어의 위치를 구한다. 
	Vector3 Pos = m_RootComponent->GetWorldPos();
	Vector3 PlayerPos = m_Scene->GetSceneInfo()->GetPlayerObject()->GetRootComponent()->GetWorldPos();

	// 플레이어가 자신의 왼쪽이라면
	if (Pos.x - PlayerPos.x >= 40.f)
	{
		// 플레이어가 자신의 왼쪽 위에 있다면 
		if (Pos.y + 50.f < PlayerPos.y)
			m_PlayerDir = EObjectDir::LeftUp;
		// 플레이어가 자신의 왼쪽 아래에 있다면 
		else if (Pos.y > PlayerPos.y + 30.f)
			m_PlayerDir = EObjectDir::LeftDown;

		// 플레이어가 자신의 왼쪽 중앙에 있다면
		else
			m_PlayerDir = EObjectDir::Left;
	}
	// 플레이어가 자신의 오른쪽이라면 
	else if (PlayerPos.x - Pos.x >= 40.f)
	{
		// 플레이어가 자신의 오른쪽 위에 있다면 
		if (Pos.y + 50.f < PlayerPos.y)
			m_PlayerDir = EObjectDir::RightUp;

		// 플레이어가 자신의 오른쪽 아래에 있다면 
		else if (Pos.y > PlayerPos.y + 50.f)
			m_PlayerDir = EObjectDir::RightDown;

		// 플레이어가 자신의 오른쪽 중앙에 있다면
		else
			m_PlayerDir = EObjectDir::Right;
	}
	// 플레이어가 자신의 가운데라면 
	else
	{
		// 플레이어가 자신의 위에 있다면
		if (Pos.y < PlayerPos.y)
		{
			m_PlayerDir = EObjectDir::Up;
		}
		// 플레이어가 자신의 아래에 있다면 
		else if (Pos.y > PlayerPos.y)
		{
			m_PlayerDir = EObjectDir::Down;
		}
	}
	
	// 피격 당했을 경우 
	if (m_HitTime > 0.f)
	{
		m_ActionTime = 0.f;

		// 자신의 위치 대비 플레이어의 위치를 구하여 밀려날 방향을 정한다. 
		if (m_GuardBreak)
		{
			EObjectDir Dir;

			// 플레이어의 카운터를 위해 
			// 몬스터 기준의 플레이어 방향을 구해  
			switch (m_PlayerDir)
			{
			case EObjectDir::Up:
				Dir = EObjectDir::Down;
				break;
			case EObjectDir::Left:
				Dir = EObjectDir::Right;
				break;
			case EObjectDir::Down:
				Dir = EObjectDir::Up;
				break;
			case EObjectDir::Right:
				Dir = EObjectDir::Left;
				break;
			case EObjectDir::LeftUp:
				Dir = EObjectDir::RightDown;
				break;
			case EObjectDir::LeftDown:
				Dir = EObjectDir::RightUp;
				break;
			case EObjectDir::RightUp:
				Dir = EObjectDir::LeftDown;
				break;
			case EObjectDir::RightDown:
				Dir = EObjectDir::LeftUp;
				break;
			}

			// 거꾸로 플레이어 기준의 몬스터 방향으로 넣어준다. 
			m_Scene->GetSceneInfo()->GetPlayerObject()->SetEnemyDir(Dir);
			
			m_GuardBreak = false;

			m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

			// 플레이어가 자신의 왼쪽이라면
			if (m_PlayerDir == EObjectDir::Left)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakLeft");
				m_Dir = EObjectDir::Right;
			}
			else if (m_PlayerDir == EObjectDir::LeftUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakLeftUp");
				m_Dir = EObjectDir::RightDown;
			}
			else if (m_PlayerDir == EObjectDir::LeftDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakLeft");
				m_Dir = EObjectDir::RightUp;
			}
			// 플레이어가 자신의 오른쪽이라면 
			else if (m_PlayerDir == EObjectDir::Right)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakRight");
				m_Dir = EObjectDir::Left;
			}
			else if (m_PlayerDir == EObjectDir::RightUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakRightUp");
				m_Dir = EObjectDir::LeftDown;
			}
			else if (m_PlayerDir == EObjectDir::RightDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakRight");
				m_Dir = EObjectDir::LeftUp;
			}
			// 플레이어가 자신의 위라면 
			else if (m_PlayerDir == EObjectDir::Up)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakLeftUp");
				m_Dir = EObjectDir::Down;
			}
			// 플레이어가 자신의 아래라면 
			else if (m_PlayerDir == EObjectDir::Down)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("GuardBreakRight");
				m_Dir = EObjectDir::Up;
			}

			// 대각선은 무브함수를 두번 호출하므로 이동속도를 줄인다.  
			if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
				|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
				m_MoveSpeed *= (3.f / 4.f);
		}
		else if (m_Hit)
		{
			m_Hit = false;

			m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

			// 플레이어가 자신의 왼쪽이라면
			if (m_PlayerDir == EObjectDir::Left)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
				m_Dir = EObjectDir::Right;
			}
			else if (m_PlayerDir == EObjectDir::LeftUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
				m_Dir = EObjectDir::RightDown;
			}
			else if (m_PlayerDir == EObjectDir::LeftDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
				m_Dir = EObjectDir::RightUp;
			}
			// 플레이어가 자신의 오른쪽이라면 
			else if (m_PlayerDir == EObjectDir::Right)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
				m_Dir = EObjectDir::Left;
			}
			else if (m_PlayerDir == EObjectDir::RightUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
				m_Dir = EObjectDir::LeftDown;
			}
			else if (m_PlayerDir == EObjectDir::RightDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
				m_Dir = EObjectDir::LeftUp;
			}
			// 플레이어가 자신의 위라면 
			else if (m_PlayerDir == EObjectDir::Up)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
				m_Dir = EObjectDir::Down;
			}
			// 플레이어가 자신의 아래라면 
			else if (m_PlayerDir == EObjectDir::Down)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
				m_Dir = EObjectDir::Up;
			}
			
			if (m_HP == 0.f)
			{
				// 죽으면 바로 타격할 수 없도록... 
				m_HitCollider->SetCollisionProfile("Default");

				m_HP -= -1.f;

				if (m_Bigkilled)
				{
					if (m_AnimDir == EObjectDir::Left)
						m_Sprite->GetAnimation()->ChangeAnimation("OneKilledByLeft");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("OneKilledByRight");	
				}
				else if (m_AnimDir == EObjectDir::Left)
					m_Sprite->GetAnimation()->ChangeAnimation("KilledByLeft");
				else
					m_Sprite->GetAnimation()->ChangeAnimation("KilledByRight");
			}

			// 대각선은 무브함수를 두번 호출하므로 이동속도를 줄인다.  
			if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
				|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
				m_MoveSpeed *= (3.f/4.f);
		}

		// 자연스러운 감속
		if (m_HitTime < 1.2f)
		{
			m_MoveSpeed -= 2000.f * DeltaTime;

			if (m_MoveSpeed < 0.f)
				m_MoveSpeed = 0.f;
		}

		// 실제 피격 이동 부분 
		switch (m_Dir)
		{
		case EObjectDir::Up:
			MoveUp();
			break;
		case EObjectDir::Left:
			RotationInv();
			break;
		case EObjectDir::Down:
			MoveDown();
			break;
		case EObjectDir::Right:
			Rotation();
			break;
		case EObjectDir::LeftUp:
			MoveUp();
			RotationInv();
			break;
		case EObjectDir::LeftDown:
			RotationInv();
			MoveDown();
			break;
		case EObjectDir::RightUp:
			Rotation();
			MoveUp();
			break;
		case EObjectDir::RightDown:
			Rotation();
			MoveDown();
			break;
		}

		m_HitTime -= DeltaTime;

		if (m_HitTime <= 0.f)
		{
			m_HitCollider->SetCollisionProfile("Monster");

			m_Target = false;

			m_Scene->GetSceneInfo()->GetPlayerObject()->SetTargetDir(EObjectDir::None);
			
			m_HitTime = 0.f;
			m_MoveSpeed = 200.f;
		}
	}
	else 
	{
		// 기본 패턴 정하기 (정지)
		if (m_BasicPattern == EBasicPattern::Ready && !m_Attack && !m_Dash)
		{
			m_ActionTime = 0.f;

			int Random = (rand() % 100) + 1;

			if (Random >= 1 && Random <= 100)
				m_BasicPattern = EBasicPattern::Stand;
		}
		// 기본 패턴 실행 
		if (m_BasicPattern == EBasicPattern::Stand)
		{
			if (m_ActionTime == 0.f)
			{
				int Random = (rand() % 100) + 1;

				if (Random >= 1 && Random <= 50)
					m_Sprite->GetAnimation()->ChangeAnimation("AlertLeft");
				else if (Random >= 51 && Random <= 100)
					m_Sprite->GetAnimation()->ChangeAnimation("AlertRight");
			}

			// 액션 타임이 끝나면 다시 패턴을 정할 수 있게 해준다. 
			if (m_ActionTime > 5.f)
			{
				m_ActionTime = 0.f;

				if(m_AlertPattern != EAlertPattern::None || m_CombatPattern != ECombatPattern::None)
					m_BasicPattern = EBasicPattern::None;
				else
					m_BasicPattern = EBasicPattern::Ready;
			}
			else
				m_ActionTime += DeltaTime;
		}

		// 경계 패턴 정하기 (이동, 정지)
		if (m_AlertPattern == EAlertPattern::Ready && !m_Attack && !m_Dash)
		{
			m_ActionTime = 0.f;

			int Random = (rand() % 100) + 1;

			if (Random >= 1 && Random <= 79)
				m_AlertPattern = EAlertPattern::Move;
			else if (Random >= 80 && Random <= 100)
				m_AlertPattern = EAlertPattern::Stand;
		}
		// 경계 패턴 실행
		if (m_AlertPattern == EAlertPattern::Move)
		{
			// 애니메이션을 교체한다. 
			// 애니메이션이 교체되는 타이밍의 방향을 저장하고 방향이 바뀌면 바로 갱신해준다. 
			if (m_ActionTime == 0.f || (m_PrevAnimDir != m_AnimDir))
			{
				int Random = (rand() % 100) + 1;

				// 확률에따라 이동속도를 정한다. 
				if (Random >= 1 && Random <= 60)
					m_MoveSpeed = 200.f;
				else if (Random >= 61 && Random <= 100)
					m_MoveSpeed = 175.f;
				

				if (m_AnimDir == EObjectDir::Left)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("RunningLeft");
					m_PrevAnimDir = m_AnimDir;
				}
				else if (m_AnimDir == EObjectDir::Right)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("RunningRight");
					m_PrevAnimDir = m_AnimDir;
				}

				// 대각선은 무브함수를 두번 호출하므로 이동속도를 줄인다.  
				if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
					|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
					m_MoveSpeed *= (2.f / 3.f);
			}
			
			m_Dir = m_PlayerDir;

			switch (m_Dir)
			{
			case EObjectDir::Up:
				MoveUp();
				break;
			case EObjectDir::Left:
				RotationInv();
				break;
			case EObjectDir::Down:
				MoveDown();
				break;
			case EObjectDir::Right:
				Rotation();
				break;
			case EObjectDir::LeftUp:
				MoveUp();
				RotationInv();
				break;
			case EObjectDir::LeftDown:
				RotationInv();
				MoveDown();
				break;
			case EObjectDir::RightUp:
				Rotation();
				MoveUp();
				break;
			case EObjectDir::RightDown:
				Rotation();
				MoveDown();
				break;
			}

			if (m_ActionTime > 3.f)
			{
				m_ActionTime = 0.f;

				if (m_BasicPattern != EBasicPattern::None || m_CombatPattern != ECombatPattern::None)
					m_AlertPattern = EAlertPattern::None;
				else
					m_AlertPattern = EAlertPattern::Ready;
				
			}
			else
				m_ActionTime += DeltaTime;
		}
		else if (m_AlertPattern == EAlertPattern::Stand)
		{
			if (m_ActionTime == 0.f || (m_PrevAnimDir != m_AnimDir))
			{
				if (m_AnimDir == EObjectDir::Left)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("AlertLeft");
					m_PrevAnimDir = m_AnimDir;
				}
				else if (m_AnimDir == EObjectDir::Right)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("AlertRight");
					m_PrevAnimDir = m_AnimDir;
				}
			}

			if (m_ActionTime > 2.f)
			{
				m_ActionTime = 0.f;
				
				if (m_BasicPattern != EBasicPattern::None || m_CombatPattern != ECombatPattern::None)
					m_AlertPattern = EAlertPattern::None;
				else
					m_AlertPattern = EAlertPattern::Ready;
			}
			else
				m_ActionTime += DeltaTime;
		}

		// 전투 패턴 정하기 (정지, 대쉬, 가드, 공격)
		if (m_CombatPattern == ECombatPattern::Ready && !m_Attack && !m_Dash)
		{
			int Random = (rand() % 100) + 1;

			if (Random >= 0 && Random <= 30)
				m_CombatPattern = ECombatPattern::Stand;
			else if (Random >= 31 && Random <= 60)
				m_CombatPattern = ECombatPattern::Attack;
			else if
				(Random >= 61 && Random <= 80)
				m_CombatPattern = ECombatPattern::Guard;
			else if
				(Random >= 81 && Random <= 100)
				m_CombatPattern = ECombatPattern::Dash;
		}
		// 전투 패턴 실행 
		if (m_CombatPattern == ECombatPattern::Stand)
		{
			if (m_ActionTime == 0.f || (m_PrevAnimDir != m_AnimDir))
			{
				if (m_AnimDir == EObjectDir::Left)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");
					m_PrevAnimDir = m_AnimDir;
				}
				else if (m_AnimDir == EObjectDir::Right)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("StandRight");
					m_PrevAnimDir = m_AnimDir;
				}
			}

			if (m_ActionTime > 2.f)
			{
				m_ActionTime = 0.f;

				if (m_AlertPattern != EAlertPattern::None || m_BasicPattern != EBasicPattern::None)
					m_CombatPattern = ECombatPattern::None;
				m_CombatPattern = ECombatPattern::Ready;
			}
			else
				m_ActionTime += DeltaTime;
		}
		// 중간에 끊길 수도 있으므로 어택변수도 조건에 추가한다. 
		else if (m_CombatPattern == ECombatPattern::Attack || m_Attack)
		{
			if (!m_Attack)
			{
				m_ActionTime = 0.f;

				m_Attack = true;

				// 공격 이동을 위해 속도 증가 
				m_MoveSpeed = 1200.f;

				if (m_AnimDir == EObjectDir::Left)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("AttackReadyLeft");
				}
				else if (m_AnimDir == EObjectDir::Right)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("AttackReadyRight");
				}
			}

			// 준비자세가 끝나고 공격 애니메이션에 들어갈경우 
			if (m_Slash)
			{
				// 플레이어를 잠깐 추적할 수 있도록 한다. 
				if(m_ActionTime < 1.f)
					m_Dir = m_PlayerDir;

				// 자연스러운 감속
				m_MoveSpeed -= 4000.f * DeltaTime;

				if (m_MoveSpeed < 0.f)
					m_MoveSpeed = 0.f;
				
				// 공격 이동 부분 
				switch (m_Dir)
				{
				case EObjectDir::Up:
					MoveUp();
					break;
				case EObjectDir::Left:
					RotationInv();
					break;
				case EObjectDir::Down:
					MoveDown();
					break;
				case EObjectDir::Right:
					Rotation();
					break;
				case EObjectDir::LeftUp:
					MoveUp();
					RotationInv();
					break;
				case EObjectDir::LeftDown:
					RotationInv();
					MoveDown();
					break;
				case EObjectDir::RightUp:
					Rotation();
					MoveUp();
					break;
				case EObjectDir::RightDown:
					Rotation();
					MoveDown();
					break;
				}
			}

			m_ActionTime += DeltaTime;

			if (m_ActionTime > 1.7f)
			{
				m_ActionTime = 0.f;
				m_Attack = false;

				// 원밖으로 나가서 컴뱃패턴이 아닌경우엔 컴뱃레디 하면 안된다. 
				if(m_AlertPattern == EAlertPattern::Ready || m_BasicPattern == EBasicPattern::Ready)
					m_CombatPattern = ECombatPattern::None;
				m_CombatPattern = ECombatPattern::Ready;
			}
		}
		else if (m_CombatPattern == ECombatPattern::Guard)
		{
			// 가드중이지만 공격을 막고있지 않다면 
			if (m_BlockTime == 0.f)
			{
				// 플레이어 방향에 따라 가드 애니메이션 방향을 계속 갱신한다. 

				// 플레이어가 자신의 왼쪽이라면
				if (m_PlayerDir == EObjectDir::Left)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardLeft");
					m_Dir = EObjectDir::Left;
				}
				else if (m_PlayerDir == EObjectDir::LeftUp)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardLeftUp");
					m_Dir = EObjectDir::LeftUp;
				}
				else if (m_PlayerDir == EObjectDir::LeftDown)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardLeft");
					m_Dir = EObjectDir::LeftDown;
				}
				// 플레이어가 자신의 오른쪽이라면 
				else if (m_PlayerDir == EObjectDir::Right)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardRight");
					m_Dir = EObjectDir::Right;
				}
				else if (m_PlayerDir == EObjectDir::RightUp)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardUp");
					m_Dir = EObjectDir::RightUp;
				}
				else if (m_PlayerDir == EObjectDir::RightDown)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardRight");
					m_Dir = EObjectDir::RightDown;
				}
				// 플레이어가 자신의 위라면 
				else if (m_PlayerDir == EObjectDir::Up)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardUp");
					m_Dir = EObjectDir::Up;
				}
				// 플레이어가 자신의 아래라면 
				else if (m_PlayerDir == EObjectDir::Down)
				{
					m_Sprite->GetAnimation()->ChangeAnimation("GuardRight");
					m_Dir = EObjectDir::Down;
				}
			}
			// 가드 중 공격을 막았다면 
			else if (m_BlockTime == 0.6f)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

				int Random = (rand() % 2) + 1;

				// 플레이어가 자신의 왼쪽이라면
				if (m_PlayerDir == EObjectDir::Left)
				{
					if(Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft2");

					m_Dir = EObjectDir::Left;
				}
				else if (m_PlayerDir == EObjectDir::LeftUp)
				{
					if (Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockLeftUp1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockLeftUp2");

					m_Dir = EObjectDir::LeftUp;
				}
				else if (m_PlayerDir == EObjectDir::LeftDown)
				{
					if (Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft2");

					m_Dir = EObjectDir::LeftDown;
				}
				// 플레이어가 자신의 오른쪽이라면 
				else if (m_PlayerDir == EObjectDir::Right)
				{
					if (Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockRight1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockRight2");

					m_Dir = EObjectDir::Right;
				}
				else if (m_PlayerDir == EObjectDir::RightUp)
				{
					if (Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockUp1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockUp2");

					m_Dir = EObjectDir::RightUp;
				}
				else if (m_PlayerDir == EObjectDir::RightDown)
				{
					if (Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockRight1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockRight2");

					m_Dir = EObjectDir::RightDown;
				}
				// 플레이어가 자신의 위라면 
				else if (m_PlayerDir == EObjectDir::Up)
				{
					if (Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockUp1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockUp2");

					m_Dir = EObjectDir::Up;
				}
				// 플레이어가 자신의 아래라면 
				else if (m_PlayerDir == EObjectDir::Down)
				{
					if (Random == 1)
						m_Sprite->GetAnimation()->ChangeAnimation("BlockRight1");
					else
						m_Sprite->GetAnimation()->ChangeAnimation("BlockRight2");

					m_Dir = EObjectDir::Down;
				}

				// 대각선은 무브함수를 두번 호출하므로 이동속도를 줄인다.  
				if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
					|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
					m_MoveSpeed *= (3.f / 4.f);
			}

			if (m_BlockTime > 0.f)
			{
				// 자연스러운 감속
				if (m_HitTime < 1.f)
				{
					m_MoveSpeed -= 2000.f * DeltaTime;

					if (m_MoveSpeed < 0.f)
						m_MoveSpeed = 0.f;
				}

				// 실제 피격 이동 부분. 반대로 밀려나야 한다.
				switch (m_Dir)
				{
				case EObjectDir::Up:
					MoveDown();
					break;
				case EObjectDir::Left:
					Rotation();
					break;
				case EObjectDir::Down:
					MoveUp();
					break;
				case EObjectDir::Right:
					RotationInv();
					break;
				case EObjectDir::LeftUp:
					Rotation();
					MoveDown();
					break;
				case EObjectDir::LeftDown:
					Rotation();
					MoveUp();
					break;
				case EObjectDir::RightUp:
					RotationInv();
					MoveDown();
					break;
				case EObjectDir::RightDown:
					RotationInv();
					MoveUp();
					break;
				}

				m_BlockTime -= DeltaTime;

				if (m_BlockTime <= 0.f)
				{
					m_BlockTime = 0.f;
					m_MoveSpeed = 200.f;

					m_CombatPattern = ECombatPattern::Ready;
				}
			}
			
			m_ActionTime += DeltaTime;

			// 가드 시간이 지났고 공격을 막고있지 않다면
			if (m_ActionTime > 2.f && m_BlockTime == 0.f)
			{
				m_ActionTime = 0.f;

				if(m_BasicPattern==EBasicPattern::None && m_AlertPattern==EAlertPattern::None)
					m_CombatPattern = ECombatPattern::Ready;
			}
		}
		else if (m_CombatPattern == ECombatPattern::Dash || m_Dash)
		{
			if (m_ActionTime == 0.f)
			{
				m_Dash = true;
				
				m_MoveSpeed = 1500.f;

				// 탈출이므로 반대방향의 애니메이션으로 바꾼다. 
				if (m_AnimDir == EObjectDir::Right)
					m_Sprite->GetAnimation()->ChangeAnimation("DashLeft");
				else if (m_AnimDir == EObjectDir::Left)
					m_Sprite->GetAnimation()->ChangeAnimation("DashRight");

				// 플레이어가 자신의 왼쪽이라면
				if (m_PlayerDir == EObjectDir::Left)
				{
					m_Dir = EObjectDir::Right;
				}
				else if (m_PlayerDir == EObjectDir::LeftUp)
				{
					m_Dir = EObjectDir::RightDown;
				}
				else if (m_PlayerDir == EObjectDir::LeftDown)
				{
					m_Dir = EObjectDir::RightUp;
				}
				// 플레이어가 자신의 오른쪽이라면 
				else if (m_PlayerDir == EObjectDir::Right)
				{
					m_Dir = EObjectDir::Left;
				}
				else if (m_PlayerDir == EObjectDir::RightUp)
				{
					m_Dir = EObjectDir::LeftDown;
				}
				else if (m_PlayerDir == EObjectDir::RightDown)
				{
					m_Dir = EObjectDir::LeftUp;
				}
				// 플레이어가 자신의 위라면 
				else if (m_PlayerDir == EObjectDir::Up)
				{
					m_Dir = EObjectDir::Down;
				}
				// 플레이어가 자신의 아래라면 
				else if (m_PlayerDir == EObjectDir::Down)
				{
					m_Dir = EObjectDir::Up;
				}

				// 대각선은 무브함수를 두번 호출하므로 이동속도를 줄인다.  
				if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
					|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
					m_MoveSpeed *= (2.f / 3.f);
			}

			// 자연스러운 감속
			m_MoveSpeed -= 3500.f * DeltaTime;

			if (m_MoveSpeed < 0.f)
				m_MoveSpeed = 0.f;

			//  이동 부분 
			switch (m_Dir)
			{
			case EObjectDir::Up:
				MoveUp();
				break;
			case EObjectDir::Left:
				RotationInv();
				break;
			case EObjectDir::Down:
				MoveDown();
				break;
			case EObjectDir::Right:
				Rotation();
				break;
			case EObjectDir::LeftUp:
				RotationInv();
				MoveUp();				
				break;
			case EObjectDir::LeftDown:
				RotationInv();
				MoveDown();
				break;
			case EObjectDir::RightUp:
				Rotation();
				MoveUp();
				break;
			case EObjectDir::RightDown:
				Rotation();
				MoveDown();
				break;
			}
			
			m_ActionTime += DeltaTime;

			if (m_ActionTime > 1.f)
			{
				m_ActionTime = 0.f;
				m_Dash = false;

				// 원밖으로 나가서 컴뱃패턴이 아닌경우엔 컴뱃레디 하면 안된다. 
				if (m_AlertPattern == EAlertPattern::Ready || m_BasicPattern == EBasicPattern::Ready)
					m_CombatPattern = ECombatPattern::None;
				m_CombatPattern = ECombatPattern::Ready;
			}
		}
	}
}

CZombie* CZombie::Clone() const
{
	return new CZombie(*this);
}

void CZombie::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CZombie::Load(FILE* File)
{
	CGameObject::Load(File);
}

EHitState CZombie::InflictDamage(int Damage, int IsBoss)
{
	// 현재 가드상태라면 가드중 시간을 증가시켜주고 리턴한다
	if (m_CombatPattern == ECombatPattern::Guard && Damage < 250)
	{
		// 0.5초 블락 
		m_BlockTime = 0.6;

		int Random = (rand() % 2) + 1;

		if (Random == 1)
			m_Scene->GetResource()->SoundPlay("Guard1");
		else if (Random == 2)
			m_Scene->GetResource()->SoundPlay("Guard2");

		// 살짝 밀려나기 위해
		m_MoveSpeed = 300.f;

		return EHitState::Block;
	}


	// 카메라 진동 (피격시 0.1f, 20.f / 타격 시 0.05f, 20.f)
	m_Scene->GetCameraManager()->GetCurrentCamera()->FixCameraPos(0.05, Vector3(0.f, 15.f, 0.f));

	// 혈흔 이펙트 
	CBlood* Afterimage = GetScene()->CreateObject<CBlood>("MonsterBlood");
	CEffect* Effect = Afterimage->GetEffect();
	Afterimage->SetRootComponent(Effect);
	Effect->SetAnimation<CAnimation2D>("MonsterBlood");

	switch (m_PlayerDir)
	{
	case EObjectDir::Up:
	{
		Afterimage->SetDir(EObjectDir::Down);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(0.f, -30.f, 0.f));
		
		Effect->GetAnimation()->AddAnimation("BloodDown", "BloodDown", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		//Afterimage->SetBloodLevel(EBloodLevel::Low);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(90.f, -30.f));
	}
		break;
	case EObjectDir::Left:
	{
		Afterimage->SetDir(EObjectDir::Right);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(50.f, 60.f, 0.f));
		Effect->AddWorldRotationZ(180.f);

		Effect->GetAnimation()->AddAnimation("BloodLeft", "BloodLeft", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->SetBloodLevel(EBloodLevel::High);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(200.f, 40.f));
		/*Effect2->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect2->AddWorldPosition(Vector3(70.f, 50.f, 0.f));
		Effect2->AddWorldRotationZ(180.f);

		Effect2->GetAnimation()->AddAnimation("BloodLeft2", "BloodLeft", 0.5f);

		Effect2->SetEffectType(EEffectType::Once);*/
	}
		break;
	case EObjectDir::Down:
	{
		Afterimage->SetDir(EObjectDir::Up);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(0.f, 110.f, 0.f));
		Effect->AddWorldRotationZ(180.f);

		Effect->GetAnimation()->AddAnimation("BloodDown", "BloodDown", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		//Afterimage->SetBloodLevel(EBloodLevel::Low);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(90.f, 180.f));
	}
		break;
	case EObjectDir::Right:
	{
		Afterimage->SetDir(EObjectDir::Left);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-60.f, 50.f, 0.f));

		Effect->GetAnimation()->AddAnimation("BloodLeft", "BloodLeft", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		//Afterimage->SetBloodLevel(EBloodLevel::High);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(-20.f, 70.f));
	}
		break;
	case EObjectDir::LeftUp:
	{
		Afterimage->SetDir(EObjectDir::RightDown);

		// 완료 
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(55.f, -20.f, 0.f));
		Effect->AddWorldRotationZ(180.f);

		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		//Afterimage->SetBloodLevel(EBloodLevel::Low);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(210.f, 10.f));
	}
		break;
	case EObjectDir::LeftDown:
	{
		Afterimage->SetDir(EObjectDir::RightUp);

		// 완료
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(65.f, 95.f, 0.f));
		Effect->AddWorldRotationZ(240.f);

		//Effect->GetAnimation()->AddAnimation("BloodLeftDown", "BloodLeftDown", 0.4f);
		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		//Afterimage->SetBloodLevel(EBloodLevel::Low);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(150.f, 170.f));
	}
		break;
	case EObjectDir::RightUp:
	{
		Afterimage->SetDir(EObjectDir::LeftDown);

		// 완료 
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-55.f, -30.f, 0.f));
		Effect->AddWorldRotationZ(90.f);

		//Effect->GetAnimation()->AddAnimation("BloodLeftDown", "BloodLeftDown", 0.4f);
		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		//Afterimage->SetBloodLevel(EBloodLevel::Low);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(-0.f, -10.f));
	}
		break;
	case EObjectDir::RightDown:
	{
		Afterimage->SetDir(EObjectDir::LeftUp);

		// 완료 
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-65.f, 100.f, 0.f));

		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		//Afterimage->SetBloodLevel(EBloodLevel::Low);
		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(-0.f, 150.f));
	}
		break;
	}

	
	// 받은 데미지에 따라 블러드레벨 결정
	

	// 혈흔 이펙트 테스트 End
	if(Damage <= 49)
		Afterimage->SetBloodLevel(EBloodLevel::Low);
	else if(Damage <= 80)
		Afterimage->SetBloodLevel(EBloodLevel::Middle);
	else if(Damage > 81)
		Afterimage->SetBloodLevel(EBloodLevel::High);

	m_HitTime = 0.7f;

	m_Hit = true;

	// 강한 데미지를 입을 수록 더 멀리 넉백되게 한다. 
	if (Damage <= 49)
		m_MoveSpeed = 400.f;
	else if (Damage >= 50 && Damage <= 69)
		m_MoveSpeed = 750.f;
	else if (Damage >= 70 && Damage < 100)
		m_MoveSpeed = 1200.f;
	else if (Damage >= 250 && m_CombatPattern == ECombatPattern::Guard)
	{
		// 어떻게 가드브레이크 걸리게 할 것인가? 
		m_HitTime = 1.2f;
		m_GuardBreak = true;

		m_MoveSpeed = 500.f;

		m_ActionTime = 0.f;
		m_Attack = false;
		m_Dash = false;
		m_Slash = false;

		// 히트 애니메이션이 아닌 가드브레이크 애니메이션을 연출해야 하므로 
		m_Hit = false;

		// 동작을 초기화시킨다. 다시 정하도록 
		if (m_CombatPattern != ECombatPattern::None)
			m_CombatPattern = ECombatPattern::Ready;

		m_Scene->GetResource()->SoundPlay("JustGuard");

		// 혈흔안튀게
		Afterimage->Destroy();

		return EHitState::None;
	}
	else if (Damage >= 250 && ((m_HP - Damage) <= 0))	
		m_Bigkilled = true;
	
	/*else
		Damage = 30.f;*/

	// 피격당하면 모든 동작이 끊긴다. 
	m_ActionTime = 0.f;
	m_Attack = false;
	m_Dash = false;
	m_Slash = false;

	// 동작을 초기화시킨다. 다시 정하도록 
	if (m_CombatPattern != ECombatPattern::None)
		m_CombatPattern = ECombatPattern::Ready;

	int Random = (rand() % 3) + 1;

	if (!m_Bigkilled)
	{
		if (Random == 1)
			m_Scene->GetResource()->SoundPlay("Hit1");
		else if (Random == 2)
			m_Scene->GetResource()->SoundPlay("Hit2");
		else if (Random == 3)
			m_Scene->GetResource()->SoundPlay("Hit3");
	}

	m_HP -= Damage;

    // 음.. 이쯤에서 메시지 카운트? 
    dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->AddHitCount();

	// 죽으면 포스트업데이트에서 사망 애니메이션으로 간다. 
	if (m_HP <= 0.f)
	{
		m_HP = 0.f;

		if (m_Body)
			m_Body->Destroy();
		

		// 빅킬은 밀려나지 않는다. 
		if (m_Bigkilled)
		{
			int Random1 = (rand() % 2) + 1;
			if (Random1 == 1)
				m_Scene->GetResource()->SoundPlay("Counter1");
			else if (Random1 == 2)
				m_Scene->GetResource()->SoundPlay("Counter2");

			m_Scene->GetResource()->SoundPlay("CounterHit"); 
			m_Scene->GetResource()->SoundPlay("Hit3");

			m_MoveSpeed = 0.f;

			m_HitTime = 1.5;
			return EHitState::Bigkill;
		}
		else			
			m_MoveSpeed = 800.f;
	}

	return EHitState::Normal;
}

void CZombie::MoveUp()
{
	m_HitCollider->AddWorldPosition(Vector3(0.f, m_MoveSpeed * g_DeltaTime, 0.f));
}

void CZombie::MoveDown()
{
	m_HitCollider->AddWorldPosition(Vector3(0.f, -m_MoveSpeed * g_DeltaTime, 0.f));
}

void CZombie::Rotation()
{
	m_HitCollider->AddWorldPosition(Vector3(m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
}

void CZombie::RotationInv()
{
	m_HitCollider->AddWorldPosition(Vector3(-m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
}

void CZombie::Slash()
{
	m_Slash = true;

	// 플레이어를 향하도록 
	m_Dir = m_PlayerDir;

	// 실제 공격 애니메이션으로 바꿔준다. 
	switch (m_AnimDir)
	{
	case EObjectDir::Left:
		m_Sprite->GetAnimation()->ChangeAnimation("AttackLeft");
		break;
	case EObjectDir::Right:
		m_Sprite->GetAnimation()->ChangeAnimation("AttackRight");
		break;
	}
}

void CZombie::Attack()
{
	m_AttackCollider = CreateComponent<CColliderBox2D>("MonsterAttack");
	m_AttackCollider->SetCollisionProfile("MonsterAttack");
	m_AttackCollider->SetCollisionCallback<CZombie>(ECollision_Result::Collision, this, &CZombie::CollisionBeginAttack);

	m_HitCollider->AddChild(m_AttackCollider);

	switch (m_Dir)
	{
	case EObjectDir::Up:
		m_AttackCollider->SetBoxSize(140.f, 80.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::Left:
		m_AttackCollider->SetBoxSize(140.f, 50.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::Down:
		m_AttackCollider->SetBoxSize(140.f, 80.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::Right:
		m_AttackCollider->SetBoxSize(140.f, 50.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::LeftUp:
		m_AttackCollider->SetBoxSize(140.f, 70.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::LeftDown:
		m_AttackCollider->SetBoxSize(140.f, 70.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::RightUp:
		m_AttackCollider->SetBoxSize(140.f, 70.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::RightDown:
		m_AttackCollider->SetBoxSize(140.f, 70.f);
		m_AttackCollider->SetRelativePosition(0.f, 0.f);
		break;
	case EObjectDir::End:
		break;
	default:
		break;
	}
	
}

void CZombie::Afterimage()
{
    // 잔상 생성
    // 이것은 애니메이션이 아닌 단순 텍스쳐로 생성되어야 함 
    // 잔상 생성
    CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("ZombieAfterImage");

    CEffect* Effect = Afterimage->GetEffect();

    Afterimage->SetRootComponent(Effect);

    Effect->SetWorldPosition(m_Sprite->GetWorldPos());
    //Effect->AddWorldPosition(Vector3(0.f, 0.f, 0.f));

    CMaterial* Material = Effect->GetMaterial(0);
    //Material->SetOpacity(0.8f);

    // 일단넣어보자 
    Afterimage->SetLifeTime(1.f);

    //if (m_BlockTime == 0.f && m_HitTime == 0.f)
    {
        //Effect->SetTexture(m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetTexture());

        Effect->SetTexture(m_Sprite->GetTexture());
        Effect->SetTextureFrameIndex(m_Sprite->GetAnimation()->GetCurrentFrame(""));

        //Effect->SetWorldScale(Effect->GetTexture()->GetWidth() * 2.5f, Effect->GetTexture()->GetHeight() * 2.5f);
        Effect->SetWorldScale(m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetFrameData(m_Sprite->GetAnimation()->GetCurrentFrame("")).End.x * 2.5f,
            m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetFrameData(m_Sprite->GetAnimation()->GetCurrentFrame("")).End.y * 2.5f);

        //Effect->SetPivot(m_Sprite->GetPivot());
        Effect->SetPivot(m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetFramePivot(m_Sprite->GetAnimation()->GetCurrentFrame("")));

        //Effect->SetPivot(m_Sprite->)

        // 잔상별 지속시간을 다르게 하여 각 잔상이 애니메이션 끝까지 이어지지 않게 한다. 
        //Effect->SetEffectType(EEffectType::Duration);

        Effect->SetDuration(3.f);

        Effect->SetRenderLayerName("Afterimage");



        // 프레임 홀수짝수에 따라 다른 색상 
        if (m_Sprite->GetAnimation()->GetCurrentFrame("") % 2 == 0)
            Material->SetBaseColorUnsignedChar(20, 232, 251, 255);
        //Material->SetBaseColorUnsignedChar(68, 83, 181, 255);
        else
            Material->SetBaseColorUnsignedChar(68, 83, 181, 255);
        //Material->SetBaseColorUnsignedChar(20, 232, 251, 255);


        /*if (m_Dash)
            Effect->SetDuration(m_Sprite->GetAnimation()->GetCurrentFrame("") / 15.f);
        else if (m_DoubleEdge)
            Effect->SetDuration(m_Sprite->GetAnimation()->GetCurrentFrame("") / 18.f);
        else
            Effect->SetDuration(m_Sprite->GetAnimation()->GetCurrentFrame("") / 13.f);*/
    }


    Material->SetRenderState("DepthDisable");

    // 홀수프레임에 먼지 생성 (잔상에 종속)

    CGameObject* EffectObject = m_Scene->CreateObject<CGameObject>("EffectObject");
    CEffect* Effect1 = CreateComponent<CEffect>("MoveDust");

    EffectObject->SetRootComponent(Effect1);
    EffectObject->SetLifeTime(1.f);

    Effect1->SetAnimation<CAnimation2D>("asas");

    //Effect->AddChild(Effect1);

    Effect1->SetRelativePosition(0.f, -15.f);

    Effect1->GetAnimation()->AddAnimation("MoveDust", "PlayerMoveDust", 0.6f);
    Effect1->SetEffectType(EEffectType::Once);
    Effect1->GetAnimation()->SetLoop("MoveDust", false);

    Effect1->SetRenderLayerName("Effect");

    CMaterial* Material1 = Effect1->GetMaterial(0);
    Material1->SetOpacity(1.f);


	////Material->SetRenderState("DepthDisable");
	//Material1->SetRenderState("DepthDisable");
	//Material->SetRenderState("AlphaBlend");
	//Material1->SetRenderState("AlphaBlend");
	//Material->SetRenderState("DepthLessEqual");
	//Material1->SetRenderState("DepthLessEqual");
}

void CZombie::AttackEnd()
{
	if(m_AlertPattern != EAlertPattern::None || m_BasicPattern != EBasicPattern::None)
		m_CombatPattern = ECombatPattern::None;
	else
		m_CombatPattern = ECombatPattern::Ready;

	m_Attack = false;
	m_Slash = false;

	m_MoveSpeed = 200.f;
}

void CZombie::DashEnd()
{
	if (m_AlertPattern != EAlertPattern::None || m_BasicPattern != EBasicPattern::None)
		m_CombatPattern = ECombatPattern::None;
	else
		m_CombatPattern = ECombatPattern::Ready;

	m_Dash = false;

	m_MoveSpeed = 200.f;
}

void CZombie::Die()
{
	if (m_Die)
		return;

    GetScene()->AddKillCount();

	m_Die = true;

	SetLifeTime(6.f);

	//m_Body->Destroy();
	//m_HitCollider->Destroy();
	m_HitCollider->SetCollisionProfile("Default");
}

void CZombie::CollisionBeginCognition(const CollisionResult& result)
{
	if (result.Src->GetName() == "Alert")
	{
		m_ActionTime = 0.f;
		m_BasicPattern = EBasicPattern::None;
		m_AlertPattern = EAlertPattern::Ready;
		m_CombatPattern = ECombatPattern::None;
		m_Alert = true; 
	}
	else if (result.Src->GetName() == "Combat")
	{
		// 하던 공격이 끊기면 안되므로 공격패턴이 아닐 경우에만 액션타임을 초기화한다. 
		if (!m_Attack && !m_Dash)
			m_ActionTime = 0.f;

		m_ActionTime = 0.f;
		m_BasicPattern = EBasicPattern::None;
		m_AlertPattern = EAlertPattern::None;
		m_CombatPattern = ECombatPattern::Ready;
	}
}

void CZombie::CollisionEndCognition(const CollisionResult& result)
{
	if (result.Src->GetName() == "Alert")
	{
		// 하던 공격이 끊기면 안되므로 공격패턴이 아닐 경우에만 액션타임을 초기화한다. 
		if (!m_Attack && !m_Dash)
			m_ActionTime = 0.f;

		
		m_BasicPattern = EBasicPattern::Ready;
		m_AlertPattern = EAlertPattern::None;
		m_CombatPattern = ECombatPattern::None;
		m_Alert = false; 
	}
	else if (result.Src->GetName() == "Combat")
	{
		// 하던 공격이 끊기면 안되므로 공격패턴이 아닐 경우에만 액션타임을 초기화한다. 
		if (!m_Attack && !m_Dash)
			m_ActionTime = 0.f;

		m_BasicPattern = EBasicPattern::None;
		m_AlertPattern = EAlertPattern::Ready;
		m_CombatPattern = ECombatPattern::None;
	}
}

void CZombie::CollisionBeginObject(const CollisionResult& result)
{
	m_PrevSpeed = m_MoveSpeed;
	m_MoveSpeed = 0;

	Vector3 SrcPos = result.Src->GetWorldPos();
	Vector3 DestPos = result.Dest->GetWorldPos();

	// 딱 붙는 코드 
	if (SrcPos.x - DestPos.x >= 0)
	{
		// 대상이 자신의 왼쪽 위에 있다면 
		if (SrcPos.y  < DestPos.y)
		{
			// 오른쪽 아래로 밀려난다
			m_HitCollider->AddWorldPosition(Vector3(2000.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -2000.f * g_DeltaTime, 0.f));
		}
		// 대상이 자신의 왼쪽 아래에 있다면 
		else if (SrcPos.y > DestPos.y)
		{
			// 오른쪽 위로 밀려난다 
			m_HitCollider->AddWorldPosition(Vector3(2000.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, 2000.f * g_DeltaTime, 0.f));
		}
		// 대상이 자신의 왼쪽 중앙에 있다면
		else
		{
			// 오른쪽으로 밀려난다. 
			m_HitCollider->AddWorldPosition(Vector3(2000.f * g_DeltaTime, 0.f, 0.f));
		}
	}
	// 대상이 자신의 오른쪽이라면 
	else if (DestPos.x - SrcPos.x >= 0)
	{
		// 대상이 자신의 오른쪽 위에 있다면 
		if (SrcPos.y < DestPos.y)
		{
			// 왼쪽 아래로 밀려난다
			m_HitCollider->AddWorldPosition(Vector3(-2000.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -2000.f * g_DeltaTime, 0.f));
		}
		// 대상이 자신의 오른쪽 아래에 있다면 
		else if (SrcPos.y > DestPos.y)
		{
			// 왼쪽 위로 밀려난다. 
			m_HitCollider->AddWorldPosition(Vector3(-2000.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, 2000.f * g_DeltaTime, 0.f));
		}
		// 대상이 자신의 오른쪽 중앙에 있다면
		else
		{
			// 왼쪽으로 밀려난다. 
			m_HitCollider->AddWorldPosition(Vector3(-2000.f * g_DeltaTime, 0.f, 0.f));
		}
	}
	// 플레이어가 자신의 가운데라면 
	else
	{
		// 플레이어가 자신의 위에 있다면
		if (SrcPos.y < DestPos.y)
		{
			// 아래로 밀려난다. 
			m_HitCollider->AddWorldPosition(Vector3(0.f, -2000.f * g_DeltaTime, 0.f));
		}
		// 플레이어가 자신의 아래에 있다면 
		else if (SrcPos.y > DestPos.y)
		{
			// 위로 밀려난다. 
			m_HitCollider->AddWorldPosition(Vector3(0.f, 2000.f * g_DeltaTime, 0.f));
		}
	}

}

void CZombie::CollisionEndObject(const CollisionResult& result)
{
	// 플레이어한테 칼질할떄 비비면 이상해지므로 거의 멈춰버리는게 나음 
	if (m_Attack && result.Dest->GetOwner()->GetName() == "Player2D")
		m_MoveSpeed = 20.f;
	else
		m_MoveSpeed = m_PrevSpeed;
}

void CZombie::CollisionBeginAttack(const CollisionResult& result)
{
	EObjectDir Dir;

	// 몬스터 기준의 플레이어 방향을 구해  
	switch (m_PlayerDir)
	{
	case EObjectDir::Up:
		Dir = EObjectDir::Down;
		break;
	case EObjectDir::Left:
		Dir = EObjectDir::Right;
		break;
	case EObjectDir::Down:
		Dir = EObjectDir::Up;
		break;
	case EObjectDir::Right:
		Dir = EObjectDir::Left;
		break;
	case EObjectDir::LeftUp:
		Dir = EObjectDir::RightDown;
		break;
	case EObjectDir::LeftDown:
		Dir = EObjectDir::RightUp;
		break;
	case EObjectDir::RightUp:
		Dir = EObjectDir::LeftDown;
		break;
	case EObjectDir::RightDown:
		Dir = EObjectDir::LeftUp;
		break;
	}

	// 거꾸로 플레이어 기준의 몬스터 방향으로 넣어준다. 
	m_Scene->GetSceneInfo()->GetPlayerObject()->SetEnemyDir(Dir);

	float Damage = 30.f;

	// 상대방에 데미지를 입힌다. 
	EHitState HitState = result.Dest->GetOwner()->InflictDamage(Damage);

	if (HitState == EHitState::Invincible)
		return;

	// 상대의 피격 시 상태에 따른 이펙트를 출력한다.
	CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("AfterImage1");

	//Effect->SetAnimation<CAnimation2D>("Afterimage1");

	// 일단넣어보자 
	Afterimage->SetLifeTime(5.f);

	CEffect* Effect1 = CreateComponent<CEffect>("PlayerHitEffect");

	Afterimage->SetRootComponent(Effect1);

	int Random1 = (rand() % 2) + 1;

	if (HitState == EHitState::Normal)
	{
		Effect1->SetAnimation<CAnimation2D>("Effect1");

		if (Random1 == 1)
			Effect1->GetAnimation()->AddAnimation("SwordSpark1", "PlayerSwordSpark1", 0.25f);
		else if (Random1 == 2)
			Effect1->GetAnimation()->AddAnimation("SwordSpark1", "PlayerSwordSpark2", 0.25f);

		Effect1->SetEffectType(EEffectType::Once);

		Effect1->SetRenderLayerName("Effect");

		Effect1->SetPivot(0.5f, 0.5f);

		CMaterial* Material1 = Effect1->GetMaterial(0);
		Material1->SetOpacity(1.f);

		//Material1->SetRenderState("DepthDisable");

		// 이펙트를 출력할 위치를 구한다. 
		Effect1->SetWorldPosition(result.HitPoint);

		// 랜덤으로 이펙트를 회전시킨다. 
		int Random = (rand() % 6) + 1;

		if (Random == 1)
			Effect1->AddWorldRotationZ(0.f);
		else if (Random == 2)
			Effect1->AddWorldRotationZ(60.f);
		else if (Random == 3)
			Effect1->AddWorldRotationZ(120.f);
		else if (Random == 4)
			Effect1->AddWorldRotationZ(180.f);
		else if (Random == 5)
			Effect1->AddWorldRotationZ(240.f);
		else if (Random == 6)
			Effect1->AddWorldRotationZ(360.f);
	}
	else if (HitState == EHitState::Block)
	{
		Effect1->SetAnimation<CAnimation2D>("Effect1");

		Effect1->GetAnimation()->AddAnimation("BlockCircle", "PlayerBlockCircle", 0.2f);

		Effect1->SetEffectType(EEffectType::Once);

		Effect1->SetRenderLayerName("Effect");

		Effect1->SetPivot(0.5f, 0.5f);

		CMaterial* Material1 = Effect1->GetMaterial(0);
		Material1->SetOpacity(1.f);

		//Material1->SetRenderState("DepthDisable");

		// 이펙트를 출력할 위치를 구한다. 
		Effect1->SetWorldPosition(result.HitPoint);

		CEffect* Effect2 = CreateComponent<CEffect>("PlayerHitEffect");
		Effect1->AddChild(Effect2);
		Effect2->SetAnimation<CAnimation2D>("Effect2");

		Effect2->GetAnimation()->AddAnimation("BlockLight", "PlayerBlockLight", 0.3f);

		Effect2->SetRenderLayerName("Effect");

		Effect2->SetRelativePosition(0.f, 0.f);


		CEffect* Effect3 = CreateComponent<CEffect>("PlayerHitEffect");
		Effect1->AddChild(Effect3);
		Effect3->SetAnimation<CAnimation2D>("Effect2");

		Effect3->GetAnimation()->AddAnimation("BlockSpark", "PlayerSwordSpark3", 0.2f);

		Effect3->SetRenderLayerName("Effect");

		Effect3->SetRelativePosition(0.f, 0.f);

		CMaterial* Material3 = Effect3->GetMaterial(0);
		Material3->SetBaseColorUnsignedChar(127, 235, 253, 0);


		CEffect* Effect4 = CreateComponent<CEffect>("PlayerHitEffect");

		Effect1->AddChild(Effect4);

		Effect4->SetAnimation<CAnimation2D>("BlockBigCircle");

		Effect4->GetAnimation()->AddAnimation("BlockBigCircle", "PlayerChain", 0.2f);

		Effect4->SetRelativePosition(0.f, 0.f);

		Effect4->SetRenderLayerName("Effect");
		Effect4->SetEffectType(EEffectType::Once);

		CMaterial* Material4 = Effect4->GetMaterial(0);
		Material4->SetBaseColorUnsignedChar(127, 235, 253, 0);



		// 랜덤으로 이펙트를 회전시킨다. 
		int Random = (rand() % 6) + 1;

		if (Random == 1)
			Effect3->AddWorldRotationZ(50.f);
		else if (Random == 2)
			Effect3->AddWorldRotationZ(100.f);
		else if (Random == 3)
			Effect3->AddWorldRotationZ(150.f);
		else if (Random == 4)
			Effect3->AddWorldRotationZ(200.f);
		else if (Random == 5)
			Effect3->AddWorldRotationZ(250.f);
		else if (Random == 6)
			Effect3->AddWorldRotationZ(350.f);
	}
	else if (HitState == EHitState::GuardBreak)
	{
		m_HitTime = 1.2f;

		m_HitCollider->SetCollisionProfile("Target");

		m_GuardBreak = true;

		// 저스트가드 이펙트 (플레이어 + 상대) 
		Effect1->SetAnimation<CAnimation2D>("PlayerChain");

		Effect1->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect1->AddWorldPosition(Vector3(-10.f, 40.f, 0.f));

		Effect1->GetAnimation()->AddAnimation("JustGuardCircle", "PlayerJustGuardCircle", 0.25f);

		Effect1->SetEffectType(EEffectType::Once);

		// 저스트가드 이펙트 (플레이어 + 상대) 
		CEffect* Effect2 = CreateComponent<CEffect>("PlayerHitEffect");
		Effect2->SetAnimation<CAnimation2D>("PlayerChain2");

		Effect1->AddChild(Effect2);

		Effect2->GetAnimation()->AddAnimation("JustGuardCircle2", "PlayerChain", 0.25f);

		Effect2->SetRelativePosition(0.f, 0.f);

		Effect2->SetEffectType(EEffectType::Once);

		CMaterial* Material1 = Effect2->GetMaterial(0);
		Material1->SetFullColorUnsignedChar(255, 255, 255, 0);
		Material1->SetOnlyColor(true);

		// 넉백시킨다. 
		m_MoveSpeed = 400.f;

		// 피격당하면 모든 동작이 끊긴다. 
		m_ActionTime = 0.f;
		m_Attack = false;
		m_Dash = false;
		m_Slash = false;

		// 동작을 초기화시킨다. 다시 정하도록 
		if (m_CombatPattern != ECombatPattern::None)
			m_CombatPattern = ECombatPattern::Ready;

		switch (m_PlayerDir)
		{
		case EObjectDir::Up:
			Dir = EObjectDir::Down;
			break;
		case EObjectDir::Left:
			Dir = EObjectDir::Right;
			break;
		case EObjectDir::Down:
			Dir = EObjectDir::Up;
			break;
		case EObjectDir::Right:
			Dir = EObjectDir::Left;
			break;
		case EObjectDir::LeftUp:
			Dir = EObjectDir::RightDown;
			break;
		case EObjectDir::LeftDown:
			Dir = EObjectDir::RightUp;
			break;
		case EObjectDir::RightUp:
			Dir = EObjectDir::LeftDown;
			break;
		case EObjectDir::RightDown:
			Dir = EObjectDir::LeftUp;
			break;
		}

		// 거꾸로 플레이어 기준의 몬스터 방향으로 넣어준다. 
		m_Scene->GetSceneInfo()->GetPlayerObject()->SetTargetDir(Dir);

		m_Target = true;
	}

	// 공격 충돌체를 삭제한다. 
	result.Src->Destroy();
}
