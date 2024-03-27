#include "Boss.h"
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

CBoss::CBoss() :
    m_HP(4000.f),
    m_RangePattern(EBossRangePattern::Ready),
    m_MeleePattern(EBossMeleePattern::None),
    m_HitTime(0.f),
    m_AttackColliderLifeTime(0.f),
    m_Dash(false),
    m_IsShowIntro(false)
{
    SetTypeID<CBoss>();
    m_ObjectTypeName = "Boss";

    m_StompReady.resize(2);
}

CBoss::CBoss(const CBoss& Obj)
{
    m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
}

CBoss::~CBoss()
{
}

void CBoss::ShowIntro()
{
    m_IsShowIntro = true;
}

void CBoss::Start()
{
    CGameObject::Start();
}

bool CBoss::Init()
{
    CGameObject::Init();

    m_Body = CreateComponent<CColliderBox2D>("Body");
    m_HitCollider = CreateComponent<CColliderBox2D>("HitCollider1");
    m_RangeCollider = CreateComponent<CColliderSphere2D>("Range");
    m_MeleeCollider = CreateComponent<CColliderSphere2D>("Melee");
    m_Sprite = CreateComponent<CSpriteComponent>("Sprite");

    m_Body->SetCollisionProfile("Object");
    m_HitCollider->SetCollisionProfile("Monster");
    m_RangeCollider->SetCollisionProfile("MonsterCognition");
    m_MeleeCollider->SetCollisionProfile("MonsterCognition");

    m_Body->SetCollisionCallback<CBoss>(ECollision_Result::Collision, this, &CBoss::CollisionBeginObject);
    m_Body->SetCollisionCallback<CBoss>(ECollision_Result::Release, this, &CBoss::CollisionEndObject);
    m_RangeCollider->SetCollisionCallback<CBoss>(ECollision_Result::Collision, this, &CBoss::CollisionBeginCognition);
    m_RangeCollider->SetCollisionCallback<CBoss>(ECollision_Result::Release, this, &CBoss::CollisionEndCognition);
    m_MeleeCollider->SetCollisionCallback<CBoss>(ECollision_Result::Collision, this, &CBoss::CollisionBeginCognition);
    m_MeleeCollider->SetCollisionCallback<CBoss>(ECollision_Result::Release, this, &CBoss::CollisionEndCognition);

    SetRootComponent(m_HitCollider);

    m_HitCollider->AddChild(m_Body);
    m_HitCollider->AddChild(m_Sprite);
    m_HitCollider->AddChild(m_RangeCollider);
    m_HitCollider->AddChild(m_MeleeCollider);

    m_HitCollider->SetBoxSize(80.f, 120.f);
    m_Body->SetBoxSize(80.f, 60.f);
    m_RangeCollider->SetRadius(500.f);
    m_MeleeCollider->SetRadius(170.f);

    m_Body->AddRelativePosition(Vector2(0.f, -30.f));

    m_Sprite->SetPivot(0.5f, 0.f);

    m_Sprite->SetRelativePosition(0.f, -60.f);
    m_HitCollider->SetWorldPosition(1000.f, 600.f);

    // ���� 
    m_HitCollider->SetRenderLayerName("Monster");

    CMaterial* Material = m_Sprite->GetMaterial(0);

    //Material->SetRenderState("DepthDisable");

    // �ִϸ��̼� �߰�
    CAnimation2D* Anim = m_Sprite->SetAnimation<CAnimation2D>("BossAnim");


    // ���� - ����
    Anim->AddAnimation("AppearJump", "BossAppearJump", 2.f);
    Anim->AddCurrentNotify<CBoss>("AppearJump", "AppearJumpSoundPlay", 7, this, &CBoss::PlaySound_FallDown);
    Anim->SetLoop("AppearJump", false);

    // ����
    Anim->AddAnimation("Appear", "BossAppear", 3.f);
    Anim->SetLoop("Appear", false);


    // �޸��� 
    Anim->AddAnimation("RunningRight", "BossRunningRight", 1.5f);
    /*Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage2", 1, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage3", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage4", 3, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage5", 4, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage6", 5, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage7", 6, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage8", 7, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage9", 8, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage10", 9, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage11", 10, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage12", 11, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage13", 12, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningRight", "RunningRightAfterimage14", 13, this, &CBoss::Afterimage);*/
    Anim->SetLoop("RunningRight", true);

    Anim->AddAnimation("RunningLeft", "BossRunningLeft", 1.5f);
    /*Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage2", 1, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage3", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage4", 3, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage5", 4, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage6", 5, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage7", 6, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage8", 7, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage9", 8, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage10", 9, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage11", 10, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage12", 11, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage13", 12, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("RunningLeft", "RunningLeftAfterimage14", 13, this, &CBoss::Afterimage);*/
    Anim->SetLoop("RunningLeft", true);

    // ���� �غ� 
    Anim->AddAnimation("GuardRight", "BossGuardRight", 0.3f);
    Anim->SetLoop("GuardRight", false);

    Anim->AddAnimation("GuardLeft", "BossGuardLeft", 0.3f);
    Anim->SetLoop("GuardLeft", false);

    // ���� ���� 
    Anim->AddAnimation("BlockRight", "BossBlockRight", 0.5f);
    Anim->SetLoop("BlockRight", false);

    Anim->AddAnimation("BlockLeft", "BossBlockLeft", 0.5f);
    Anim->SetLoop("BlockLeft", false);

    // ����극��ũ (����)
    Anim->AddAnimation("BlockBreakRight", "BossBlockBreakRight", 0.15f);
    Anim->SetLoop("BlockBreakRight", true);

    Anim->AddAnimation("BlockBreakLeft", "BossBlockBreakLeft", 0.15f);
    Anim->SetLoop("BlockBreakLeft", true);

    // ��Ʈ
    Anim->AddAnimation("HitByRight", "BossHitByRight", 1.f);
    Anim->SetLoop("HitByRight", false);

    Anim->AddAnimation("HitByLeft", "BossHitByLeft", 1.f);
    Anim->SetLoop("HitByLeft", false);

    // ���
    Anim->AddAnimation("KilledByRight", "BossKilledByRight", 1.8f);
    Anim->SetLoop("KilledByRight", false);

    Anim->AddAnimation("KilledByLeft", "BossKilledByLeft", 1.8f);
    Anim->SetLoop("KilledByLeft", false);

    // ����-��ġ 
    Anim->AddAnimation("AttackPunchRight", "BossAttackPunchRight", 1.3f);
    Anim->SetLoop("AttackPunchRight", false);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRight", 5, this, &CBoss::Attack);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRight", 16, this, &CBoss::Attack);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage2", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage3", 4, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage4", 6, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage5", 8, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage6", 10, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage7", 12, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage8", 14, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage9", 16, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage10", 18, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchRight", "AttackPunchRightAfterimage11", 20, this, &CBoss::Afterimage);

    Anim->AddAnimation("AttackPunchLeft", "BossAttackPunchLeft", 1.3f);
    Anim->SetLoop("AttackPunchLeft", false);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeft", 5, this, &CBoss::Attack);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeft", 16, this, &CBoss::Attack);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage2", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage3", 4, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage4", 6, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage5", 8, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage6", 10, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage7", 12, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage8", 14, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage9", 16, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage10", 18, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackPunchLeft", "AttackPunchLeftAfterimage11", 20, this, &CBoss::Afterimage);

    // ����-������-�غ�
    Anim->AddAnimation("AttackStompReady", "BossAttackStompReady", 0.4f);
    Anim->AddCurrentNotify<CBoss>("AttackStompReady", "AttackStompReadyAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStompReady", "AttackStompReadyAfterimage2", 1, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStompReady", "AttackStompReadyAfterimage3", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStompReady", "AttackStompReadyAfterimage4", 3, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStompReady", "AttackStompReadyAfterimage5", 4, this, &CBoss::Afterimage);
    Anim->SetLoop("AttackStompReady", false);

    // ����-������ 
    Anim->AddAnimation("AttackStomp", "BossAttackStomp", 0.3f);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStompAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStompAfterimage2", 1, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStompAfterimage3", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStompAfterimage4", 3, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStompAfterimage5", 4, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStompAfterimage6", 5, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStompAfterimage7", 6, this, &CBoss::Afterimage);
    Anim->SetLoop("AttackStomp", false);
    Anim->AddCurrentNotify<CBoss>("AttackStomp", "AttackStomp", 1, this, &CBoss::Attack);

    // ����-����-�غ� 
    Anim->AddAnimation("AttackRushReadyRight", "BossAttackRushReadyRight", 0.15f);
    Anim->SetLoop("AttackRushReadyRight", true);
    Anim->AddCurrentNotify<CBoss>("AttackRushReadyRight", "AttackRushReadyRightAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushReadyRight", "AttackRushReadyRightAfterimage2", 1, this, &CBoss::Afterimage);

    Anim->AddAnimation("AttackRushReadyLeft", "BossAttackRushReadyLeft", 0.15f);
    Anim->SetLoop("AttackRushReadyLeft", true);
    Anim->AddCurrentNotify<CBoss>("AttackRushReadyLeft", "AttackRushReadyLeftAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushReadyLeft", "AttackRushReadyLeftAfterimage2", 1, this, &CBoss::Afterimage);

    // ����-����
    Anim->AddAnimation("AttackRushRight", "BossAttackRushRight", 0.7f);
    Anim->SetLoop("AttackRushRight", false);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRight", 0, this, &CBoss::Attack);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage2", 1, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage3", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage4", 3, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage5", 4, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage6", 5, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage7", 6, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage8", 7, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushRight", "AttackRushRightAfterimage9", 8, this, &CBoss::Afterimage);

    Anim->AddAnimation("AttackRushLeft", "BossAttackRushLeft", 0.7f);
    Anim->SetLoop("AttackRushLeft", false);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeft", 0, this, &CBoss::Attack);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage1", 0, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage2", 1, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage3", 2, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage4", 3, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage5", 4, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage6", 5, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage7", 6, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage8", 7, this, &CBoss::Afterimage);
    Anim->AddCurrentNotify<CBoss>("AttackRushLeft", "AttackRushLeftAfterimage9", 8, this, &CBoss::Afterimage);
    
    // �ִϸ��̼� ������
    Anim->SetCurrentEndFunction("AttackStompReady", this, &CBoss::Stomp);
    Anim->SetCurrentEndFunction("AttackRushReadyLeft", this, &CBoss::Rush);
    Anim->SetCurrentEndFunction("AttackRushReadyRight", this, &CBoss::Rush);
    Anim->SetCurrentEndFunction("KilledByLeft", this, &CBoss::Die);
    Anim->SetCurrentEndFunction("KilledByRight", this, &CBoss::Die);

    Anim->SetCurrentEndFunction("AppearJump", this, &CBoss::Intro2);

    Anim->SetCurrentAnimation("Appear");
    

    // �����Լ��� ���⼭ �ھƹ�����. AttackEnd�� �������� ���� �� �ع����ϱ� 
    // ���� �ð� ������ ���� ������ �ð��� ���� �� AttackEnd�� ȣ���ϵ��� ����. 

    return true;
}

void CBoss::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    // ���� �浹ü�� 0.1 �� �� �����Ѵ�.
    // ���������� �ð��� �������� ���� �� �����Ƿ� 
    if (m_AttackCollider)
    {
        // ���� ������, m_RushAttack�� ����� true�� ���� ���� 
        // ���� �浹ü�� �ݹ� ������� ������ ����  -> �Ʒ� �������� �������� �ذ�..
        if (m_RushAttack)
            m_AttackColliderLifeTime += (DeltaTime * 0.2);
        else
            m_AttackColliderLifeTime += DeltaTime;

        if (m_AttackColliderLifeTime > 0.1f)
        {
            m_AttackColliderLifeTime = 0.f;
            m_AttackCollider->Destroy();
            m_AttackCollider = nullptr;  // �ƴ� �̰��ϳ��ߴٰ� ������ �ذ��?
        }
    }

    if (m_Die)
        return;

    // �������� ��� '�÷��̾ ���ϴ� ����'�� ���Ͽ� �ڽ��� �ִϸ��̼� �������� �Ѵ�. 
    // �ǰݽÿ��� ���ϴ� ������ ���� �����Ƿ� �����Ѵ�. 
    if (m_HitTime == 0.f)
    {
        float PosX = m_RootComponent->GetWorldPos().x;
        float PlayerPosX = m_Scene->GetSceneInfo()->GetPlayerObject()->GetRootComponent()->GetWorldPos().x;

        // �÷��̾ ������ ���ʿ� ���� ��� 
        if (PosX - PlayerPosX >= 0)
            m_AnimDir = EObjectDir::Left;
        // �÷��̾ ������ �����ʿ� ���� ��� 
        else
            m_AnimDir = EObjectDir::Right;
    }


    // ���Ÿ���� 1�ʰ� �Ѿ�°� ����극��ũ �ۿ� ���� 
    // �̶� �÷��̾�� ���� ���� ���� 
    if (m_HitTime < 1.2f && m_HitTime > 1.f)
    {
        m_Sprite->GetMaterial(0)->SetFullColorUnsignedChar(255, 255, 255, 0);
        m_Sprite->GetMaterial(0)->SetOnlyColor(true);
    }
    else
        m_Sprite->GetMaterial(0)->SetOnlyColor(false);
}

void CBoss::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);

    // ��Ʈ�ζ� �÷��̾ �����ϸ� �������Ƿ� �ּ� 7�ʰ��� �÷��̾ �������Ѿ��� 
    if (m_IsShowIntro)
    {
        m_HitCollider->AddWorldPositionY(360.f);

        m_Sprite->GetAnimation()->SetCurrentAnimation("AppearJump");
        m_IsShowIntro = false;
        m_PlayIntroTime = 6.5f;
        return;
    }

    if (m_PlayIntroTime > 0.f)
    {
        m_PlayIntroTime -= DeltaTime;

        m_MoveSpeed = 500.f;

        if(m_PlayIntroTime > 5.8f)
            MoveDown();

        return;
    }
    else
        m_PlayIntroTime = 0.f;

    if (m_Die)
    {
        if(m_DieTime != 100.f)
            m_DieTime -= DeltaTime;

        if (m_DieTime < 0.f)
        {
            m_Scene->GetResource()->SoundPlay("BossStompExplosion");
            m_DieTime = 100.f;
        }
        

        return;
    }

    // �ڽ��� ��ġ ��� �÷��̾��� ��ġ�� ���Ѵ�. 
    Vector3 Pos = m_RootComponent->GetWorldPos();
    Vector3 PlayerPos = m_Scene->GetSceneInfo()->GetPlayerObject()->GetRootComponent()->GetWorldPos();

    // �÷��̾ �ڽ��� �����̶��
    if (Pos.x - PlayerPos.x >= 40.f)
    {
        // �÷��̾ �ڽ��� ���� ���� �ִٸ� 
        if (Pos.y + 50.f < PlayerPos.y)
            m_PlayerDir = EObjectDir::LeftUp;
        // �÷��̾ �ڽ��� ���� �Ʒ��� �ִٸ� 
        else if (Pos.y > PlayerPos.y + 30.f)
            m_PlayerDir = EObjectDir::LeftDown;

        // �÷��̾ �ڽ��� ���� �߾ӿ� �ִٸ�
        else
            m_PlayerDir = EObjectDir::Left;
    }
    // �÷��̾ �ڽ��� �������̶�� 
    else if (PlayerPos.x - Pos.x >= 40.f)
    {
        // �÷��̾ �ڽ��� ������ ���� �ִٸ� 
        if (Pos.y + 50.f < PlayerPos.y)
            m_PlayerDir = EObjectDir::RightUp;

        // �÷��̾ �ڽ��� ������ �Ʒ��� �ִٸ� 
        else if (Pos.y > PlayerPos.y + 50.f)
            m_PlayerDir = EObjectDir::RightDown;

        // �÷��̾ �ڽ��� ������ �߾ӿ� �ִٸ�
        else
            m_PlayerDir = EObjectDir::Right;
    }
    // �÷��̾ �ڽ��� ������ 
    else
    {
        // �÷��̾ �ڽ��� ���� �ִٸ�
        if (Pos.y < PlayerPos.y)
        {
            m_PlayerDir = EObjectDir::Up;
        }
        // �÷��̾ �ڽ��� �Ʒ��� �ִٸ� 
        else if (Pos.y > PlayerPos.y)
        {
            m_PlayerDir = EObjectDir::Down;
        }
    }

    // �ǰ� ������ ��� 
    if (m_HitTime > 0.f)
    {
        m_ActionTime = 0.f;

        // �ڽ��� ��ġ ��� �÷��̾��� ��ġ�� ���Ͽ� �з��� ������ ���Ѵ�. 
        if (m_GuardBreak)
        {
            EObjectDir Dir;

            // �÷��̾��� ī���͸� ���� 
            // ���� ������ �÷��̾� ������ ����  
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

            // �Ųٷ� �÷��̾� ������ ���� �������� �־��ش�. 
            m_Scene->GetSceneInfo()->GetPlayerObject()->SetEnemyDir(Dir);

            m_GuardBreak = false;

            m_Sprite->GetAnimation()->ChangeAnimation("RunningLeft");

            // �÷��̾ �ڽ��� �����̶��
            if (m_PlayerDir == EObjectDir::Left)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakLeft");
                m_Dir = EObjectDir::Right;
            }
            else if (m_PlayerDir == EObjectDir::LeftUp)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakLeft");
                m_Dir = EObjectDir::RightDown;
            }
            else if (m_PlayerDir == EObjectDir::LeftDown)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakLeft");
                m_Dir = EObjectDir::RightUp;
            }
            // �÷��̾ �ڽ��� �������̶�� 
            else if (m_PlayerDir == EObjectDir::Right)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakRight");
                m_Dir = EObjectDir::Left;
            }
            else if (m_PlayerDir == EObjectDir::RightUp)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakRight");
                m_Dir = EObjectDir::LeftDown;
            }
            else if (m_PlayerDir == EObjectDir::RightDown)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakRight");
                m_Dir = EObjectDir::LeftUp;
            }
            // �÷��̾ �ڽ��� ����� 
            else if (m_PlayerDir == EObjectDir::Up)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakLeft");
                m_Dir = EObjectDir::Down;
            }
            // �÷��̾ �ڽ��� �Ʒ���� 
            else if (m_PlayerDir == EObjectDir::Down)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("BlockBreakRight");
                m_Dir = EObjectDir::Up;
            }

            //m_MoveSpeed = 120;

            // �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
            if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
                || m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
                m_MoveSpeed *= (1.f / 2.f);
        }
        else if (m_Hit)
        {
            m_Hit = false;

            m_Sprite->GetAnimation()->ChangeAnimation("RunningLeft");

            // �÷��̾ �ڽ��� �����̶��
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
            // �÷��̾ �ڽ��� �������̶�� 
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
            // �÷��̾ �ڽ��� ����� 
            else if (m_PlayerDir == EObjectDir::Up)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
                m_Dir = EObjectDir::Down;
            }
            // �÷��̾ �ڽ��� �Ʒ���� 
            else if (m_PlayerDir == EObjectDir::Down)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
                m_Dir = EObjectDir::Up;
            }

            if (m_HP == 0.f)
            {
                // ������ �ٷ� Ÿ���� �� ������... 
                m_HitCollider->SetCollisionProfile("Default");

                m_HP -= -1.f;

                if (m_AnimDir == EObjectDir::Left)
                    m_Sprite->GetAnimation()->ChangeAnimation("KilledByLeft");
                else
                    m_Sprite->GetAnimation()->ChangeAnimation("KilledByRight");

                ///
                m_DieTime = 1.1f;

                m_Die = true;

                SetLifeTime(200.f);

                m_HitCollider->SetCollisionProfile("Default");
                ///
            }

            //m_MoveSpeed = 120;

            // �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
            if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
                || m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
                m_MoveSpeed *= (1.f / 2.f);
        }

        // �ڿ������� ����
        if (m_HitTime < 1.2f)
        {
            m_MoveSpeed -= 2000.f * DeltaTime;

            if (m_MoveSpeed < 0.f)
                m_MoveSpeed = 0.f;
        }

        // ���� �ǰ� �̵� �κ� 
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
            m_MoveSpeed = 120.f;
        }
    }
    else
    { 
        // ���Ÿ� ���� ���ϱ� (�̵� 30, ������ 30, ���� 40)
        if (m_RangePattern == EBossRangePattern::Ready && !m_StompAttack && !m_RushAttack && !m_PunchAttack)
        {
            m_ActionTime = 0.f;

            int Random = (rand() % 100) + 1;

            if (Random >= 1 && Random <= 30)
                m_RangePattern = EBossRangePattern::Move;
            else if (Random >= 31 && Random <= 60)
                m_RangePattern = EBossRangePattern::Stomp;
            else if (Random >= 61 && Random <= 100)
                m_RangePattern = EBossRangePattern::Rush;
        }
        // ���Ÿ� ���� 1 : �̵�
        if(m_RangePattern == EBossRangePattern::Move)
        {
            m_Dir = m_PlayerDir;

            // �ִϸ��̼��� ��ü�Ѵ�. 
            // �ִϸ��̼��� ��ü�Ǵ� Ÿ�̹��� ������ �����ϰ� ������ �ٲ�� �ٷ� �������ش�. 
            if (m_ActionTime == 0.f || (m_PrevAnimDir != m_AnimDir))
            {
                int Random = (rand() % 100) + 1;

                m_MoveSpeed = 120.f;

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
                
                // �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
                if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
                    || m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
                    m_MoveSpeed *= (1.f / 2.f);
            }

            // m_Dir = m_PlayerDir;

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

            if (m_ActionTime > 2.f)
            {
                m_ActionTime = 0.f;

                if (m_MeleePattern != EBossMeleePattern::None)
                    m_RangePattern = EBossRangePattern::None;
                else
                    m_RangePattern = EBossRangePattern::Ready;
            }
            else
                m_ActionTime += DeltaTime;
        }
        // ���Ÿ� ���� 2 : ������ 
        // �߰��� ���� ���� �����Ƿ� ���ú����� ���ǿ� �߰��Ѵ�. 
        else if (m_RangePattern == EBossRangePattern::Stomp || m_StompAttack)
        {
            if (!m_StompAttack)
            {
                m_ActionTime = 0.f;

                m_StompAttack = true;

                m_StompReady[0] = true;

                m_StompReady[1] = true;

                m_Sprite->GetAnimation()->ChangeAnimation("AttackStompReady");

                // ����
                m_Scene->GetResource()->SoundPlay("BossStompReady");
            }

            // �غ��ڼ� ���� 0.8�ʰ� ������ ���. ��Ŭ ����Ʈ
            if (m_StompReady[1] && m_ActionTime > 0.7f)
            {
                m_StompReady[1] = false;

                // ������ �⸦ ������ ����Ʈ�� ����Ѵ�.
                CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("StompCircle");

                Afterimage->SetLifeTime(0.25f);

                CEffect* Effect1 = CreateComponent<CEffect>("StompCircleEffect");

                Afterimage->SetRootComponent(Effect1);

                Effect1->SetAnimation<CAnimation2D>("Effect1");

                Effect1->GetAnimation()->AddAnimation("StompCircle", "BossStompCircle", 0.25f);

                Effect1->SetWorldPosition(m_Body->GetWorldPos());
                Effect1->AddWorldPosition(-20.f, 128.f);

                Effect1->SetRenderLayerName("Effect");
                //Effect1->SetRenderLayerName("");

                CMaterial* Material = Effect1->GetMaterial(0);
                Material->SetRenderState("DepthDisable");

                
            }

            // �غ��ڼ��� ������ 1�ʰ� ������ ��� . ���� ���� �� ��ġ ��� 
            if (m_StompReady[0] && m_ActionTime > 1.f)
            {
                m_StompReady[0] = false;

                m_Sprite->GetAnimation()->ChangeAnimation("AttackStomp");

                m_StompPos = m_Scene->GetSceneInfo()->GetPlayerObject()->GetWorldPos();
            }

            m_ActionTime += DeltaTime;

            if (m_ActionTime > 2.5f)
            {
                m_ActionTime = 0.f;
                AttackEnd();

                // �������� ������ �Ĺ������� �ƴѰ�쿣 �Ĺ�� �ϸ� �ȵȴ�. 
                if (m_MeleePattern == EBossMeleePattern::Ready)
                    m_RangePattern = EBossRangePattern::None;
                else
                    m_RangePattern = EBossRangePattern::Ready;
            }
        }
        else if (m_RangePattern == EBossRangePattern::Rush || (m_RushAttack))
        {
            if (!m_RushAttack)
            {
                m_ActionTime = 0.f;

                m_RushAttack = true;

                m_RushReady = true;

                // ���� �̵��� ���� �ӵ� ���� 
                m_MoveSpeed = 2200.f;

                if (m_AnimDir == EObjectDir::Left)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("AttackRushReadyLeft");
                }
                else if (m_AnimDir == EObjectDir::Right)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("AttackRushReadyRight");
                }
            }

            // �غ��ڼ��� ������ 1�ʰ� ������ ��� ���� ���� 
            if (m_RushReady && m_ActionTime > 0.8f)
            {   
                m_RushReady = false;

                if (m_AnimDir == EObjectDir::Left)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("AttackRushLeft");
                }
                else if (m_AnimDir == EObjectDir::Right)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("AttackRushRight");
                }


                // ���⿡ ���� ����Ʈ 
                CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("RushSonicBoom");

                Afterimage->SetLifeTime(0.25f);

                CEffect* Effect1 = CreateComponent<CEffect>("RushSonicBoom");

                Afterimage->SetRootComponent(Effect1);

                Effect1->SetAnimation<CAnimation2D>("Effect1");

                Effect1->GetAnimation()->AddAnimation("RushSonicBoom", "BossRushSonicBoom", 0.25f);

                Effect1->SetWorldPosition(m_Body->GetWorldPos());
                Effect1->AddWorldPosition(0.f, 50.f);

                Effect1->SetRenderLayerName("Effect");
                //Effect1->SetRenderLayerName("");

                CMaterial* Material = Effect1->GetMaterial(0);
                Material->SetRenderState("DepthDisable");
                Material->SetOpacity(0.8f);
                

                // ���� ������ ����ش�. + ����Ʈ����
                // �÷��̾ �ڽ��� �����̶��
                if (m_PlayerDir == EObjectDir::Left)
                {
                    m_Dir = EObjectDir::Left;
                    Effect1->AddRelativeRotationZ(-180.f);                 
                }
                else if (m_PlayerDir == EObjectDir::LeftUp)
                {
                    m_Dir = EObjectDir::LeftUp;
                    Effect1->AddRelativeRotationZ(-225.f);
                }
                else if (m_PlayerDir == EObjectDir::LeftDown)
                {
                    m_Dir = EObjectDir::LeftDown;
                    Effect1->AddRelativeRotationZ(-135.f);
                }
                // �÷��̾ �ڽ��� �������̶�� 
                else if (m_PlayerDir == EObjectDir::Right)
                {
                    m_Dir = EObjectDir::Right;
                }
                else if (m_PlayerDir == EObjectDir::RightUp)
                {
                    m_Dir = EObjectDir::RightUp;
                    Effect1->AddRelativeRotationZ(-315.f);
                }
                else if (m_PlayerDir == EObjectDir::RightDown)
                {
                    m_Dir = EObjectDir::RightDown;
                    Effect1->AddRelativeRotationZ(-45.f);
                }
                // �÷��̾ �ڽ��� ����� 
                else if (m_PlayerDir == EObjectDir::Up)
                {
                    m_Dir = EObjectDir::Up;
                    Effect1->AddRelativeRotationZ(-270.f);
                }
                // �÷��̾ �ڽ��� �Ʒ���� 
                else if (m_PlayerDir == EObjectDir::Down)
                {
                    m_Dir = EObjectDir::Down;
                    Effect1->AddRelativeRotationZ(-90.f);
                }

                // �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
                if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
                    || m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
                    m_MoveSpeed *= (4.f / 5.f);

                // ���� 
                m_Scene->GetResource()->SoundPlay("BossRushVoice");
                m_Scene->GetResource()->SoundPlay("BossRushWind");
            }

            if (m_ActionTime > 0.8f)
            {
                // �ڿ������� ����
                m_MoveSpeed -= 3500.f * DeltaTime;

                if (m_MoveSpeed < 0.f)
                    m_MoveSpeed = 0.f;

                //  �̵� �κ� 
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
            }

            m_ActionTime += DeltaTime;

            if (m_ActionTime > 2.5f)
            {
                m_ActionTime = 0.f;
                AttackEnd();

                // �������� ������ �Ĺ������� �ƴѰ�쿣 �Ĺ�� �ϸ� �ȵȴ�. 
                if (m_MeleePattern == EBossMeleePattern::Ready)
                    m_RangePattern == EBossRangePattern::None;
                else
                     m_RangePattern == EBossRangePattern::Ready;
            }
        }

        // �ٰŸ� ���� ���ϱ� (���� 25, ��ġ 40, ������ 35)
        if (m_MeleePattern == EBossMeleePattern::Ready && !m_RushAttack && !m_StompAttack)
        {
            int Random = (rand() % 100) + 1;

            if (Random >= 0 && Random <= 30)
                m_MeleePattern = EBossMeleePattern::Guard;  // 25
            else if (Random >= 30 && Random <= 100)
                m_MeleePattern = EBossMeleePattern::Punch;  // 40
            else if (Random >= 66 && Random <= 100)
                m_MeleePattern = EBossMeleePattern::Stomp;  // 35
        }

        // �ٰŸ� ���� 1 : ����
        if (m_MeleePattern == EBossMeleePattern::Guard)
        {
            if (m_BlockTime == 0.f && !m_Guard)
            {
                m_Guard = true;

                // �÷��̾� ���⿡ ���� ���� �ִϸ��̼� ������ ��� �����Ѵ�. 

                // �÷��̾ �ڽ��� �����̶��
                if (m_PlayerDir == EObjectDir::Left)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardLeft");
                    m_Dir = EObjectDir::Left;
                }
                else if (m_PlayerDir == EObjectDir::LeftUp)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardLeft");
                    m_Dir = EObjectDir::LeftUp;
                }
                else if (m_PlayerDir == EObjectDir::LeftDown)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardLeft");
                    m_Dir = EObjectDir::LeftDown;
                }
                // �÷��̾ �ڽ��� �������̶�� 
                else if (m_PlayerDir == EObjectDir::Right)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardRight");
                    m_Dir = EObjectDir::Right;
                }
                else if (m_PlayerDir == EObjectDir::RightUp)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardRight");
                    m_Dir = EObjectDir::RightUp;
                }
                else if (m_PlayerDir == EObjectDir::RightDown)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardRight");
                    m_Dir = EObjectDir::RightDown;
                }
                // �÷��̾ �ڽ��� ����� 
                else if (m_PlayerDir == EObjectDir::Up)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardLeft");
                    m_Dir = EObjectDir::Up;
                }
                // �÷��̾ �ڽ��� �Ʒ���� 
                else if (m_PlayerDir == EObjectDir::Down)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("GuardRight");
                    m_Dir = EObjectDir::Down;
                }
            }

            // ���� �� ������ ���Ҵٸ� 
            else if (m_BlockTime == 0.4f)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("RunningLeft");

                // �÷��̾ �ڽ��� �����̶��
                if (m_PlayerDir == EObjectDir::Left)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
                    m_Dir = EObjectDir::Left;
                }
                else if (m_PlayerDir == EObjectDir::LeftUp)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
                    m_Dir = EObjectDir::LeftUp;
                }
                else if (m_PlayerDir == EObjectDir::LeftDown)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
                    m_Dir = EObjectDir::LeftDown;
                }
                // �÷��̾ �ڽ��� �������̶�� 
                else if (m_PlayerDir == EObjectDir::Right)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
                    m_Dir = EObjectDir::Right;
                }
                else if (m_PlayerDir == EObjectDir::RightUp)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
                    m_Dir = EObjectDir::RightUp;
                }
                else if (m_PlayerDir == EObjectDir::RightDown)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
                    m_Dir = EObjectDir::RightDown;
                }
                // �÷��̾ �ڽ��� ����� 
                else if (m_PlayerDir == EObjectDir::Up)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
                    m_Dir = EObjectDir::Up;
                }
                // �÷��̾ �ڽ��� �Ʒ���� 
                else if (m_PlayerDir == EObjectDir::Down)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
                    m_Dir = EObjectDir::Down;
                }

                // �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
                if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
                    || m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
                    m_MoveSpeed *= (1.f / 2.f);
            }

            if (m_BlockTime > 0.f)
            {
                // �ڿ������� ����
                if (m_HitTime < 1.f)
                {
                    m_MoveSpeed -= 2000.f * DeltaTime;

                    if (m_MoveSpeed < 0.f)
                        m_MoveSpeed = 0.f;
                }

                // ���� �ǰ� �̵� �κ�. �ݴ�� �з����� �Ѵ�.
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
                    m_Guard = false;

                    m_BlockTime = 0.f;
                    m_MoveSpeed = 120.f;

                    m_MeleePattern = EBossMeleePattern::Ready;
                }
            }

            m_ActionTime += DeltaTime;

            // ���� �ð��� ������ ������ �������� �ʴٸ�
            if (m_ActionTime > 2.f && m_BlockTime == 0.f)
            {
                m_Guard = false;

                m_ActionTime = 0.f;

                if (m_RangePattern == EBossRangePattern::None)
                    m_MeleePattern = EBossMeleePattern::Ready;
            }
        }
        // �ٰŸ� ����3 : ��ġ 
        else if (m_MeleePattern == EBossMeleePattern::Punch || (m_PunchAttack))
        {
            if (!m_PunchAttack)
            {
                m_Sprite->GetAnimation()->ChangeAnimation("RunningLeft");

                m_PunchAttack = true;

                m_ActionTime = 0.f;

                // ���� �̵��� ���� �ӵ� ����
                m_MoveSpeed = 250.f;

                if (m_AnimDir == EObjectDir::Left)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("AttackPunchLeft");
                }
                else if (m_AnimDir == EObjectDir::Right)
                {
                    m_Sprite->GetAnimation()->ChangeAnimation("AttackPunchRight");
                }

                // ���� ������ ����ش�. 
                 // �÷��̾ �ڽ��� �����̶��
                if (m_PlayerDir == EObjectDir::Left)
                {
                    m_Dir = EObjectDir::Left;
                }
                else if (m_PlayerDir == EObjectDir::LeftUp)
                {
                    m_Dir = EObjectDir::LeftUp;
                }
                else if (m_PlayerDir == EObjectDir::LeftDown)
                {
                    m_Dir = EObjectDir::LeftDown;
                }
                // �÷��̾ �ڽ��� �������̶�� 
                else if (m_PlayerDir == EObjectDir::Right)
                {
                    m_Dir = EObjectDir::Right;
                }
                else if (m_PlayerDir == EObjectDir::RightUp)
                {
                    m_Dir = EObjectDir::RightUp;
                }
                else if (m_PlayerDir == EObjectDir::RightDown)
                {
                    m_Dir = EObjectDir::RightDown;
                }
                // �÷��̾ �ڽ��� ����� 
                else if (m_PlayerDir == EObjectDir::Up)
                {
                    m_Dir = EObjectDir::Up;
                }
                // �÷��̾ �ڽ��� �Ʒ���� 
                else if (m_PlayerDir == EObjectDir::Down)
                {
                    m_Dir = EObjectDir::Down;
                }

                // �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
                if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
                    || m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
                    m_MoveSpeed *= (4.f / 5.f);
            }


            if (m_ActionTime < 1.5f)
            {
                // �ڿ������� ����
                m_MoveSpeed -= 120.f * DeltaTime;

                if (m_MoveSpeed < 0.f)
                    m_MoveSpeed = 0.f;

                //  �̵� �κ� 
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
            }
            

            m_ActionTime += DeltaTime;

            if (m_ActionTime > 2.f)
            {
                m_PunchAttack = false;
                m_ActionTime = 0.f;
                AttackEnd();

                //// �������� ������ �Ĺ������� �ƴѰ�쿣 �Ĺ�� �ϸ� �ȵȴ�. 
                //if (m_MeleePattern == EBossMeleePattern::Ready)
                //    m_RangePattern == EBossRangePattern::None;
                //else
                //    m_RangePattern == EBossRangePattern::Ready;

                if (m_RangePattern == EBossRangePattern::None)
                    m_MeleePattern = EBossMeleePattern::Ready;
            }
        }
    }
}

CBoss* CBoss::Clone() const
{
    return new CBoss(*this);
}

void CBoss::Save(FILE* File)
{
    CGameObject::Save(File);
}

void CBoss::Load(FILE* File)
{
    CGameObject::Load(File);
}

EHitState CBoss::InflictDamage(int Damage, int IsBoss)
{
    // ���۾Ƹ��� ���� 
    if ((m_RushAttack || m_StompAttack || m_PunchAttack) && m_ActionTime < 1.4f && !m_HitTime !=0.f)
    {
        m_SuperArmor = true;
    }
    else
        m_SuperArmor = false;

    // ���� ������ ��� 
    if (m_Guard && Damage < 250)
    {
        m_BlockTime = 0.5;

        int Random = (rand() % 2) + 1;

        if (Random == 1)
            m_Scene->GetResource()->SoundPlay("Guard1");
        else if (Random == 2)
            m_Scene->GetResource()->SoundPlay("Guard2");

        // ��¦ �з����� ����
        m_MoveSpeed = 300.f;

        return EHitState::Block;
    }

    // ���۾Ƹ� ������ �ǰ��� ���
    if (m_SuperArmor)
    {
        m_HP -= (Damage * 0.7);

        int Random = (rand() % 2) + 1;

        if (Random == 1)
            m_Scene->GetResource()->SoundPlay("SuperArmor1");
        else if (Random == 2)
            m_Scene->GetResource()->SoundPlay("SuperArmor2");

        return EHitState::SuperArmor;
    }

    // �Ϲ� �ǰ��� ���

    // ī�޶� ���� (�ǰݽ� 0.1f, 20.f / Ÿ�� �� 0.05f, 20.f)
    m_Scene->GetCameraManager()->GetCurrentCamera()->FixCameraPos(0.05, Vector3(0.f, 15.f, 0.f));

    // ���� ����Ʈ 
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

        // �Ϸ� 
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

        // �Ϸ�
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

        // �Ϸ� 
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

        // �Ϸ� 
        Effect->SetWorldPosition(m_Sprite->GetWorldPos());
        Effect->AddWorldPosition(Vector3(-65.f, 100.f, 0.f));

        Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

        Effect->SetEffectType(EEffectType::Once);

        //Afterimage->SetBloodLevel(EBloodLevel::Low);
        Afterimage->CreateBloodArea(GetWorldPos(), Vector2(-0.f, 150.f));
    }
        break;
    }

    // ���� �������� ���� ���巹�� ����
    if (Damage <= 49)
        Afterimage->SetBloodLevel(EBloodLevel::Low);
    else if (Damage <= 80)
        Afterimage->SetBloodLevel(EBloodLevel::Middle);
    else if (Damage > 81)
        Afterimage->SetBloodLevel(EBloodLevel::High);

    
    m_HitTime = 1.f;

    m_Hit = true;

    m_Bigkilled = false;

    // ���� �������� ���� ���� �� �ָ� �˹�ǰ� �Ѵ�. 
    if (Damage <= 49)
        m_MoveSpeed = 400.f;
    else if (Damage >= 50 && Damage <= 69)
        m_MoveSpeed = 650.f;
    else if (Damage >= 70 && Damage < 100)
        m_MoveSpeed = 800.f;
    else if (Damage >= 250 && m_Guard)
    {
        m_Guard = false;

        // ��� ����극��ũ �ɸ��� �� ���ΰ�? 
        m_HitTime = 1.2f;
        m_GuardBreak = true;

        m_MoveSpeed = 500.f;

        m_ActionTime = 0.f;

        m_StompAttack = false;
        m_PunchAttack = false;
        m_RushAttack = false;

        // ��Ʈ �ִϸ��̼��� �ƴ� ����극��ũ �ִϸ��̼��� �����ؾ� �ϹǷ� 
        m_Hit = false;

        // ������ �ʱ�ȭ��Ų��. �ٽ� ���ϵ��� 
        if (m_RangePattern != EBossRangePattern::None)
            m_RangePattern = EBossRangePattern::Ready;
        else if (m_MeleePattern != EBossMeleePattern::None)
            m_MeleePattern = EBossMeleePattern::Ready;
       
        m_Scene->GetResource()->SoundPlay("JustGuard");

        // �����Ƣ��
        Afterimage->Destroy();

        return EHitState::None;
    }
    else if (Damage >= 250)
        m_Bigkilled = true;

    m_ActionTime = 0.f;

    m_StompAttack = false;
    m_PunchAttack = false;
    m_RushAttack = false;

    // ������ �ʱ�ȭ��Ų��. �ٽ� ���ϵ��� 
    if (m_RangePattern != EBossRangePattern::None)
        m_RangePattern = EBossRangePattern::Ready;
    else if (m_MeleePattern != EBossMeleePattern::None)
        m_MeleePattern = EBossMeleePattern::Ready;

    int Random = (rand() % 3) + 1;

    if (Random == 1)
        m_Scene->GetResource()->SoundPlay("Hit1");
    else if (Random == 2)
        m_Scene->GetResource()->SoundPlay("Hit2");
    else if (Random == 3)
        m_Scene->GetResource()->SoundPlay("Hit3");


    m_HP -= Damage;
    
    // ��.. ���뿡�� �޽��� ī��Ʈ? 
    dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->AddHitCount();

    // ������ ����Ʈ������Ʈ���� ��� �ִϸ��̼����� ����. 
    if (m_HP <= 0.f)
    {
        m_Scene->GetResource()->SoundPlay("BossKillCry");

        m_RangePattern = EBossRangePattern::None;
        m_MeleePattern = EBossMeleePattern::None;

        m_HP = 0.f;

        if (m_Body)
            m_Body->Destroy();

        // ��ų�� �з����� �ʴ´�. 
        if (m_Bigkilled)
        {
            int Random1 = (rand() % 2) + 1;
            if (Random1 == 1)
                m_Scene->GetResource()->SoundPlay("Counter1");
            else if (Random1 == 2)
                m_Scene->GetResource()->SoundPlay("Counter2");

            // m_Scene->GetResource()->SoundPlay("CounterHit");
            m_Scene->GetResource()->SoundPlay("Hit3");

            m_MoveSpeed = 200.f;

            //m_HitTime = 1.5;
        }
        else
            m_MoveSpeed = 200.f;
    }
    // ī���͸� �¾����� ������ƴѰ�� �Ҹ����...
    else if (m_Target)
    {
        int Random1 = (rand() % 2) + 1;
        if (Random1 == 1)
            m_Scene->GetResource()->SoundPlay("Counter1");
        else if (Random1 == 2)
            m_Scene->GetResource()->SoundPlay("Counter2");
    }

    
    return EHitState::Normal;
}

void CBoss::MoveUp()
{
    m_HitCollider->AddWorldPosition(Vector3(0.f, m_MoveSpeed * g_DeltaTime, 0.f));
}

void CBoss::MoveDown()
{
    m_HitCollider->AddWorldPosition(Vector3(0.f, -m_MoveSpeed * g_DeltaTime, 0.f));
}

void CBoss::Rotation()
{
    m_HitCollider->AddWorldPosition(Vector3(m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
}

void CBoss::RotationInv()
{
    m_HitCollider->AddWorldPosition(Vector3(-m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
}

void CBoss::Stomp()
{
    m_StompAttack = true;
}

void CBoss::Rush()
{
    m_RushAttack = true;
}

void CBoss::Attack()
{
    m_AttackCollider = CreateComponent<CColliderBox2D>("MonsterAttack");
    m_AttackCollider->SetCollisionProfile("MonsterAttack");
    m_AttackCollider->SetCollisionCallback<CBoss>(ECollision_Result::Collision, this, &CBoss::CollisionBeginAttack);

    m_HitCollider->AddChild(m_AttackCollider);

    if (m_PunchAttack)
    {
        switch (m_Dir)
        {
        case EObjectDir::Up:
            m_AttackCollider->SetBoxSize(180.f, 80.f);
            m_AttackCollider->SetRelativePosition(0.f, 60.f);
            break;
        case EObjectDir::Left:
            m_AttackCollider->SetBoxSize(180.f, 95.f);
            m_AttackCollider->SetRelativePosition(0.f, 0.f);
            break;
        case EObjectDir::Down:
            m_AttackCollider->SetBoxSize(180.f, 80.f);
            m_AttackCollider->SetRelativePosition(0.f, -40.f);
            break;
        case EObjectDir::Right:
            m_AttackCollider->SetBoxSize(180.f, 95.f);
            m_AttackCollider->SetRelativePosition(0.f, 0.f);
            break;
        case EObjectDir::LeftUp:
            m_AttackCollider->SetBoxSize(130.f, 120.f);
            m_AttackCollider->SetRelativePosition(-30.f, 30.f);
            break;
        case EObjectDir::LeftDown:
            m_AttackCollider->SetBoxSize(130.f, 120.f);
            m_AttackCollider->SetRelativePosition(-30.f, -30.f);
            break;
        case EObjectDir::RightUp:
            m_AttackCollider->SetBoxSize(130.f, 120.f);
            m_AttackCollider->SetRelativePosition(30.f, 30.f);
            break;
        case EObjectDir::RightDown:
            m_AttackCollider->SetBoxSize(130.f, 120.f);
            m_AttackCollider->SetRelativePosition(30.f, -30.f);
            break;
        case EObjectDir::End:
            break;
        default:
            break;
        }

        m_Scene->GetResource()->SoundPlay("NormalSwing");
    }
    else if (m_StompAttack)
    {
        // ī�޶� ���� (�ǰݽ� 0.1f, 20.f / Ÿ�� �� 0.05f, 20.f)
        m_Scene->GetCameraManager()->GetCurrentCamera()->FixCameraPos(0.07, Vector3(0.f, 45.f, 0.f));

        m_AttackCollider->SetBoxSize(100.f, 100.f);
        m_AttackCollider->SetWorldPosition(m_StompPos);
        
        // ����ũ ����Ʈ
        {
            CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("StompSpark");

            Afterimage->SetLifeTime(0.6f);

            CEffect* Effect1 = CreateComponent<CEffect>("StompSpark");

            Afterimage->SetRootComponent(Effect1);

            Effect1->SetAnimation<CAnimation2D>("Effect1");

            Effect1->GetAnimation()->AddAnimation("StompSpark", "BossStompSpark", 0.6f);

            Effect1->SetWorldPosition(m_Body->GetWorldPos());
            Effect1->AddWorldPosition(20.f, 0.f);

            Effect1->SetRenderLayerName("Effect");
            //Effect1->SetRenderLayerName("");

            CMaterial* Material = Effect1->GetMaterial(0);
            Material->SetRenderState("DepthDisable");
        }

        // ���̺� ����Ʈ
        {
            CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("StompWave");

            Afterimage->SetLifeTime(0.25f);

            CEffect* Effect1 = CreateComponent<CEffect>("StompWave");

            Afterimage->SetRootComponent(Effect1);

            Effect1->SetAnimation<CAnimation2D>("Effect1");

            Effect1->GetAnimation()->AddAnimation("StompWave", "BossStompWave", 0.25f);

            Effect1->SetWorldPosition(m_Body->GetWorldPos());
            Effect1->AddWorldPosition(0.f, -40.f);

            Effect1->SetRenderLayerName("Effect");
            //Effect1->SetRenderLayerName("");

            CMaterial* Material = Effect1->GetMaterial(0);
            Material->SetRenderState("DepthDisable");
        }

        // ����Ʈ ����Ʈ
        {
            CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("StompDust");

            Afterimage->SetLifeTime(1.f);

            CEffect* Effect1 = CreateComponent<CEffect>("StompDust");

            Afterimage->SetRootComponent(Effect1);

            Effect1->SetAnimation<CAnimation2D>("Effect1");

            Effect1->GetAnimation()->AddAnimation("StompDust", "BossStompDust", 0.8f);

            Effect1->SetWorldPosition(m_Body->GetWorldPos());
            Effect1->AddWorldPosition(0.f, -30.f);

            Effect1->SetRenderLayerName("Effect");
            //Effect1->SetRenderLayerName("");

            CMaterial* Material = Effect1->GetMaterial(0);
            Material->SetRenderState("DepthDisable");
        }

        // Ÿ�� ����Ʈ ����Ʈ
        {
            CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("StompTargetDust");

            Afterimage->SetLifeTime(0.25f);

            CEffect* Effect1 = CreateComponent<CEffect>("StompTargetDust");

            Afterimage->SetRootComponent(Effect1);

            Effect1->SetAnimation<CAnimation2D>("Effect1");

            Effect1->GetAnimation()->AddAnimation("StompTargetDust", "BossStompTargetDust", 0.2f);

            Effect1->SetWorldPosition(m_AttackCollider->GetWorldPos());
            Effect1->AddWorldPosition(0.f, -50.f);

            Effect1->SetRenderLayerName("Effect");
            //Effect1->SetRenderLayerName("");

            CMaterial* Material = Effect1->GetMaterial(0);
            Material->SetRenderState("DepthDisable");
        }

        // Ÿ�� �ͽ��÷��� ����Ʈ
        {
            CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("StompTargetExplosion");

            Afterimage->SetLifeTime(0.25f);

            CEffect* Effect1 = CreateComponent<CEffect>("StompTargetExplosion");

            Afterimage->SetRootComponent(Effect1);

            Effect1->SetAnimation<CAnimation2D>("Effect1");

            Effect1->GetAnimation()->AddAnimation("StompTargetExplosion", "BossStompTargetExplosion", 0.25f);

            Effect1->SetWorldPosition(m_AttackCollider->GetWorldPos());
            Effect1->AddWorldPosition(0.f, -50.f);

            Effect1->SetRenderLayerName("Effect");
            //Effect1->SetRenderLayerName("");

            CMaterial* Material = Effect1->GetMaterial(0);
            Material->SetRenderState("DepthDisable");
        }

        // ����
        m_Scene->GetResource()->SoundPlay("BossStompExplosion");
    }
    // �̰� �� �۵��Ѵ�. 
    else if (m_RushAttack)
    {
         m_AttackCollider->SetBoxSize(150.f, 150.f);
    }
}

void CBoss::Afterimage()
{
    // �ܻ� ����
    // �̰��� �ִϸ��̼��� �ƴ� �ܼ� �ؽ��ķ� �����Ǿ�� �� 
    CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("AfterImage1");

    CEffect* Effect = Afterimage->GetEffect();

    Afterimage->SetRootComponent(Effect);

    Effect->SetWorldPosition(m_Sprite->GetWorldPos());

    CMaterial* Material = Effect->GetMaterial(0);

    Material->SetOpacity(0.9f);

    // �ϴܳ־�� 
    Afterimage->SetLifeTime(5.f);

    // Ư����Ȳ����
    //if (!m_PunchAttack)
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

        // �ܻ� ���ӽð��� �ٸ��� �Ͽ� �� �ܻ��� �ִϸ��̼� ������ �̾����� �ʰ� �Ѵ�. 
        //Effect->SetEffectType(EEffectType::Duration);

        Effect->SetDuration(3.f);

        Effect->SetRenderLayerName("Afterimage");

        // ������ Ȧ��¦���� ���� �ٸ� ���� 
        if (m_Sprite->GetAnimation()->GetCurrentFrame("") % 2 == 0)
            Material->SetBaseColorUnsignedChar(20, 232, 251, 255);
        else
            Material->SetBaseColorUnsignedChar(68, 83, 181, 255);
    }

    //Material->SetRenderState("DepthDisable");

    //if (!m_RushReady)
    {
        // Ȧ�������ӿ� ���� ���� (�ܻ� ����)  
        // �̰��� �ִϸ��̼����� �����Ǿ�� �� 
        CEffect* Effect1 = CreateComponent<CEffect>("MoveDust");

        Effect1->SetAnimation<CAnimation2D>("asas");

        Effect->AddChild(Effect1);

        Effect1->SetRelativePosition(0.f, -15.f);

        Effect1->GetAnimation()->AddAnimation("MoveDust", "PlayerMoveDust", 0.4f);
        Effect1->SetEffectType(EEffectType::Once);
        Effect1->GetAnimation()->SetLoop("MoveDust", false);

        Effect1->SetRenderLayerName("Effect");

        CMaterial* Material1 = Effect1->GetMaterial(0);
        Material1->SetOpacity(1.f);
    }
}

void CBoss::AttackEnd()
{
    if (m_MeleePattern != EBossMeleePattern::None)
        m_RangePattern = EBossRangePattern::None;
    else
        m_RangePattern = EBossRangePattern::Ready;

    m_StompAttack = false;
    m_StompReady[0] = false;
    m_StompReady[1] = false;
    m_RushAttack = false;
    m_PunchAttack = false;
    m_RushReady = false;

    m_ActionTime = 0.f;

    m_MoveSpeed = 120.f;
}

void CBoss::RushEnd()
{
}

void CBoss::Die()
{
    if (m_Die)
        return;

    /*m_Die = true;

    SetLifeTime(200.f);

    m_HitCollider->SetCollisionProfile("Default");*/

    //m_Scene->GetResource()->SoundPlay("BossStompExplosion");
}

void CBoss::Intro2()
{
    m_Sprite->GetAnimation()->SetCurrentAnimation("Appear");
    m_Scene->GetResource()->SoundPlay("BossIntroShout");
}

void CBoss::PlaySound_FallDown()
{
    m_Scene->GetResource()->SoundPlay("BossIntroFallDown");

    // ����Ʈ ����Ʈ
    {
        CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("StompDust");

        Afterimage->SetLifeTime(1.f);

        CEffect* Effect1 = CreateComponent<CEffect>("StompDust");

        Afterimage->SetRootComponent(Effect1);

        Effect1->SetAnimation<CAnimation2D>("Effect1");

        Effect1->GetAnimation()->AddAnimation("StompDust", "BossStompDust", 1.2f);

        Effect1->SetWorldPosition(m_Body->GetWorldPos());
        Effect1->AddWorldPosition(0.f, 0.f);

        Effect1->SetRenderLayerName("Effect");
        //Effect1->SetRenderLayerName("");

        CMaterial* Material = Effect1->GetMaterial(0);
        Material->SetRenderState("DepthDisable");
    }
}

void CBoss::CollisionBeginCognition(const CollisionResult& result)
{
    if (result.Src->GetName() == "Range")
    {
        // ������ ���� �ּ�ó���ؾ� �´µ�. 
        //m_ActionTime = 0.f;
        //m_RangePattern = EBossRangePattern::Ready;
        if(m_RangePattern != EBossRangePattern::None)
            m_MeleePattern = EBossMeleePattern::None;
        m_Range = true;
    }
    else if (result.Src->GetName() == "Melee")
    {
        // �ϴ� ������ ����� �ȵǹǷ� ���������� �ƴ� ��쿡�� �׼�Ÿ���� �ʱ�ȭ�Ѵ�. 
        if (!m_PunchAttack && !m_StompAttack && !m_RushAttack && !m_Guard)
            m_ActionTime = 0.f;

        //m_ActionTime = 0.f;
        m_RangePattern = EBossRangePattern::None;
        m_MeleePattern = EBossMeleePattern::Ready;
    }
}

void CBoss::CollisionEndCognition(const CollisionResult& result)
{
    if (result.Src->GetName() == "Range")
    {
        // �ϴ� ������ ����� �ȵǹǷ� ���������� �ƴ� ��쿡�� �׼�Ÿ���� �ʱ�ȭ�Ѵ�. 
        if (!m_PunchAttack && !m_RushAttack && !m_StompAttack && !m_Dash)
            m_ActionTime = 0.f;

        // �⺻ ������ �������̱⋚����.. ����� �ٸ���. / �״ϱ� m_Range�� ��� true�� 
        m_RangePattern = EBossRangePattern::Ready;
        m_MeleePattern = EBossMeleePattern::None;
        m_Range = true;
    }
    else if (result.Src->GetName() == "Melee")
    {
        // �ϴ� ������ ����� �ȵǹǷ� ���������� �ƴ� ��쿡�� �׼�Ÿ���� �ʱ�ȭ�Ѵ�. 
        if (!m_PunchAttack && !m_RushAttack && !m_StompAttack && !m_Dash)
        {
            m_ActionTime = 0.f;
            m_Guard = false;
        }

        m_RangePattern = EBossRangePattern::Ready;
        m_MeleePattern = EBossMeleePattern::None;
    }
}

void CBoss::CollisionBeginObject(const CollisionResult& result)
{
    m_PrevSpeed = m_MoveSpeed;
    m_MoveSpeed = 0;

    Vector3 SrcPos = result.Src->GetWorldPos();
    Vector3 DestPos = result.Dest->GetWorldPos();

    // �� �ٴ� �ڵ� 
    if (SrcPos.x - DestPos.x >= 0)
    {
        // ����� �ڽ��� ���� ���� �ִٸ� 
        if (SrcPos.y < DestPos.y)
        {
            // ������ �Ʒ��� �з�����
            m_HitCollider->AddWorldPosition(Vector3(2000.f * g_DeltaTime, 0.f, 0.f));
            m_HitCollider->AddWorldPosition(Vector3(0.f, -2000.f * g_DeltaTime, 0.f));
        }
        // ����� �ڽ��� ���� �Ʒ��� �ִٸ� 
        else if (SrcPos.y > DestPos.y)
        {
            // ������ ���� �з����� 
            m_HitCollider->AddWorldPosition(Vector3(2000.f * g_DeltaTime, 0.f, 0.f));
            m_HitCollider->AddWorldPosition(Vector3(0.f, 2000.f * g_DeltaTime, 0.f));
        }
        // ����� �ڽ��� ���� �߾ӿ� �ִٸ�
        else
        {
            // ���������� �з�����. 
            m_HitCollider->AddWorldPosition(Vector3(2000.f * g_DeltaTime, 0.f, 0.f));
        }
    }
    // ����� �ڽ��� �������̶�� 
    else if (DestPos.x - SrcPos.x >= 0)
    {
        // ����� �ڽ��� ������ ���� �ִٸ� 
        if (SrcPos.y < DestPos.y)
        {
            // ���� �Ʒ��� �з�����
            m_HitCollider->AddWorldPosition(Vector3(-2000.f * g_DeltaTime, 0.f, 0.f));
            m_HitCollider->AddWorldPosition(Vector3(0.f, -2000.f * g_DeltaTime, 0.f));
        }
        // ����� �ڽ��� ������ �Ʒ��� �ִٸ� 
        else if (SrcPos.y > DestPos.y)
        {
            // ���� ���� �з�����. 
            m_HitCollider->AddWorldPosition(Vector3(-2000.f * g_DeltaTime, 0.f, 0.f));
            m_HitCollider->AddWorldPosition(Vector3(0.f, 2000.f * g_DeltaTime, 0.f));
        }
        // ����� �ڽ��� ������ �߾ӿ� �ִٸ�
        else
        {
            // �������� �з�����. 
            m_HitCollider->AddWorldPosition(Vector3(-2000.f * g_DeltaTime, 0.f, 0.f));
        }
    }
    // �÷��̾ �ڽ��� ������ 
    else
    {
        // �÷��̾ �ڽ��� ���� �ִٸ�
        if (SrcPos.y < DestPos.y)
        {
            // �Ʒ��� �з�����. 
            m_HitCollider->AddWorldPosition(Vector3(0.f, -2000.f * g_DeltaTime, 0.f));
        }
        // �÷��̾ �ڽ��� �Ʒ��� �ִٸ� 
        else if (SrcPos.y > DestPos.y)
        {
            // ���� �з�����. 
            m_HitCollider->AddWorldPosition(Vector3(0.f, 2000.f * g_DeltaTime, 0.f));
        }
    }
}

void CBoss::CollisionEndObject(const CollisionResult& result)
{
    // �÷��̾����� Į���ҋ� ���� �̻������Ƿ� ���� ��������°� ���� 
    if ((m_RushAttack || m_StompAttack) && result.Dest->GetOwner()->GetName() == "Player2D")
        m_MoveSpeed = 20.f;
    else
        m_MoveSpeed = m_PrevSpeed;
}

void CBoss::CollisionBeginAttack(const CollisionResult& result)
{
    EObjectDir Dir;

    // ���� ������ �÷��̾� ������ ����  
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

    // �Ųٷ� �÷��̾� ������ ���� �������� �־��ش�. 
    m_Scene->GetSceneInfo()->GetPlayerObject()->SetEnemyDir(Dir);

    // ���� �� ����� ����
    float Damage = 0.f;
    int type = 0;

    if (m_PunchAttack)
    {
        Damage = 50.f;
        type = 1;
    }
    if (m_StompAttack)
    {
        Damage = 70.f;
        type = 2;
    }
        
    if (m_RushAttack)
    {
        Damage = 100.f;
        type = 3;
    }
        
    // ���濡 �������� ������. 
    EHitState HitState = result.Dest->GetOwner()->InflictDamage(Damage, type);

    if (HitState == EHitState::Invincible)
        return;

    // ����� �ǰ� �� ���¿� ���� ����Ʈ�� ����Ѵ�.
    CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("AfterImage1");

    //Effect->SetAnimation<CAnimation2D>("Afterimage1");

    // �ϴܳ־�� 
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

        // ����Ʈ�� ����� ��ġ�� ���Ѵ�. 
        Effect1->SetWorldPosition(result.HitPoint);

        // �������� ����Ʈ�� ȸ����Ų��. 
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

        // ����Ʈ�� ����� ��ġ�� ���Ѵ�. 
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



        // �������� ����Ʈ�� ȸ����Ų��. 
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

        // ����Ʈ���� ����Ʈ (�÷��̾� + ���) 
        Effect1->SetAnimation<CAnimation2D>("PlayerChain");

        Effect1->SetWorldPosition(m_Sprite->GetWorldPos());
        Effect1->AddWorldPosition(Vector3(-10.f, 40.f, 0.f));

        Effect1->GetAnimation()->AddAnimation("JustGuardCircle", "PlayerJustGuardCircle", 0.25f);

        Effect1->SetEffectType(EEffectType::Once);

        // ����Ʈ���� ����Ʈ (�÷��̾� + ���) 
        CEffect* Effect2 = CreateComponent<CEffect>("PlayerHitEffect");
        Effect2->SetAnimation<CAnimation2D>("PlayerChain2");

        Effect1->AddChild(Effect2);

        Effect2->GetAnimation()->AddAnimation("JustGuardCircle2", "PlayerChain", 0.25f);

        Effect2->SetRelativePosition(0.f, 0.f);

        Effect2->SetEffectType(EEffectType::Once);

        CMaterial* Material1 = Effect2->GetMaterial(0);
        Material1->SetFullColorUnsignedChar(255, 255, 255, 0);
        Material1->SetOnlyColor(true);

        // �˹��Ų��. 
        m_MoveSpeed = 400.f;

        // �ǰݴ��ϸ� ��� ������ �����. 
        m_ActionTime = 0.f;
        m_StompAttack = false;
        m_RushAttack = false;
        m_PunchAttack = false;

        // ������ �ʱ�ȭ��Ų��. �ٽ� ���ϵ��� 
        if (m_RangePattern != EBossRangePattern::None)
            m_RangePattern = EBossRangePattern::Ready;
        else if(m_MeleePattern != EBossMeleePattern::None)
            m_MeleePattern = EBossMeleePattern::Ready;

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

        // �Ųٷ� �÷��̾� ������ ���� �������� �־��ش�. 
        m_Scene->GetSceneInfo()->GetPlayerObject()->SetTargetDir(Dir);

        m_Target = true;
    }

    // ���� �浹ü�� �����Ѵ�. 
    result.Src->Destroy();
    m_AttackColliderLifeTime = 0.f;
}
