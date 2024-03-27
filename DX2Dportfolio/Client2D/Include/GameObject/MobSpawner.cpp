#include <string>
#include "MobSpawner.h"
#include "Zombie.h"
#include "Assassin.h"
#include "Boss.h"
#include "Component/SpriteComponent.h"
#include "Resource/Material/Material.h"
#include "Component/ColliderBox2D.h"
#include "Scene/Scene.h"
#include "../Scene/MainSceneInfo.h"
#include "../Scene/TestSceneInfo.h"
#include "Device.h"


CMobSpawner::CMobSpawner()
{
    SetTypeID<CMobSpawner>();

    m_ObjectTypeName = "MobSpawner";

    m_SpawnCount = -1;
}

CMobSpawner::CMobSpawner(const CMobSpawner& Obj) :
    CGameObject(Obj)
{
}

CMobSpawner::~CMobSpawner()
{
}

void CMobSpawner::Start()
{
    CGameObject::Start();
}

bool CMobSpawner::Init()
{
    CGameObject::Init();

    srand((unsigned int)time(nullptr));

    m_SpawnArea = CreateComponent<CColliderBox2D>("Area");

    SetRootComponent(m_SpawnArea);

    return true;
}

void CMobSpawner::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CMobSpawner::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);

    if (m_Scene->IsCleanMonster())
    {
        return;
    }

    // 최초에 좀비 20마리를 스폰한다. 
    if (m_Scene->GetKillCount() == 0 && m_SpawnCount == -1)
    {
        m_SpawnCount = 0;

        for (int i = 1; i <= 20; ++i)
        {
            CZombie* Zombie1 = m_Scene->CreateObject<CZombie>("Zombie" + std::to_string(i));
            Zombie1->SetWorldPosition(GetRandomPosInArea());
        }
    }
    // 이후 킬카운트 1마다 암살자 1마리를 소환한다 
    else if (m_Scene->GetKillCount() != m_SpawnCount && m_SpawnCount < 20)
    {
        int length = m_Scene->GetKillCount() - m_SpawnCount;

        for (int i = 0; i < length; ++i)
        {
            CAssassin* Assassin1 = m_Scene->CreateObject<CAssassin>("Assassin" + std::to_string(m_SpawnCount));
            Assassin1->SetWorldPosition(GetRandomPosInArea());
        }

        m_SpawnCount = m_Scene->GetKillCount();
    }
}

CMobSpawner* CMobSpawner::Clone() const
{
    return new CMobSpawner(*this);
}

void CMobSpawner::CreateSpawnArea(Vector2 LT)
{
    // 이건 중심을 의미한다. 주의 . 수정안했음
    m_SpawnArea->SetWorldPosition(LT);
    
    m_SpawnArea->SetBoxSize(2000.f, 2000.f);
}

Vector2 CMobSpawner::GetRandomPosInArea()
{
    int randomX = (rand() % (int)(m_SpawnArea->GetBoxSize().x)) + (int)(m_SpawnArea->GetInfo().Left);
    int randomY = (rand() % (int)(m_SpawnArea->GetBoxSize().y)) + (int)(m_SpawnArea->GetInfo().Bottom);

    return Vector2((float)randomX, (float)randomY);
}
