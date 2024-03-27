
#include "MainSceneInfo.h"
#include "Scene/Scene.h"
#include "../UI/MainHUD.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/Assassin.h"
#include "../GameObject/Boss.h"
#include "../GameObject/MobSpawner.h"

CMainSceneInfo::CMainSceneInfo()
{
}

CMainSceneInfo::~CMainSceneInfo()
{
}

bool CMainSceneInfo::Init()
{
	CSceneInfo::Init();

	m_MainHUD = m_Owner->GetViewport()->CreateUIWindow<CMainHUD>("MainHUD");

	m_Owner->GetResource()->SoundPlay("Field");

    /*CZombie* Zombie1 = m_Owner->CreateObject<CZombie>("Monster1");
    Zombie1->SetWorldPosition(500.f, 500.f);*/

	/*CZombie* Zombie1 = m_Owner->CreateObject<CZombie>("Monster1");
	Zombie1->SetWorldPosition(500.f, 500.f);

	CZombie* Zombie2 = m_Owner->CreateObject<CZombie>("Monster2");
	Zombie2->SetWorldPosition(600.f, 500.f);

	CZombie* Zombie3 = m_Owner->CreateObject<CZombie>("Monster3");
	Zombie3->SetWorldPosition(700.f, 500.f);
	CZombie* Zombie4 = m_Owner->CreateObject<CZombie>("Monster4");
	Zombie4->SetWorldPosition(800.f, 500.f);
	CZombie* Zombie5 = m_Owner->CreateObject<CZombie>("Monster5");
	Zombie5->SetWorldPosition(900.f, 500.f);
	CZombie* Zombie6 = m_Owner->CreateObject<CZombie>("Monster6");
	Zombie6->SetWorldPosition(1000.f, 500.f);
	CZombie* Zombie7 = m_Owner->CreateObject<CZombie>("Monster7");
	Zombie7->SetWorldPosition(1100.f, 500.f);

	CZombie* Zombie8 = m_Owner->CreateObject<CZombie>("Monster8");
	Zombie8->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie9 = m_Owner->CreateObject<CZombie>("Monster9");
	Zombie9->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie10 = m_Owner->CreateObject<CZombie>("Monster10");
	Zombie10->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie11= m_Owner->CreateObject<CZombie>("Monster11");
	Zombie11->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie12 = m_Owner->CreateObject<CZombie>("Monster12");
	Zombie12->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie13 = m_Owner->CreateObject<CZombie>("Monster13");
	Zombie13->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie14= m_Owner->CreateObject<CZombie>("Monster14");
	Zombie14->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie15= m_Owner->CreateObject<CZombie>("Monster15");
	Zombie15->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie16= m_Owner->CreateObject<CZombie>("Monster16");
	Zombie16->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie17= m_Owner->CreateObject<CZombie>("Monster17");
	Zombie17->SetWorldPosition(5350.f, 3900.f);

	CZombie* Zombie18= m_Owner->CreateObject<CZombie>("Monster18");
	Zombie18->SetWorldPosition(5350.f, 5400.f);

	CZombie* Zombie19 = m_Owner->CreateObject<CZombie>("Monster19");
	Zombie19->SetWorldPosition(5350.f, 5300.f);

	CZombie* Zombie20 = m_Owner->CreateObject<CZombie>("Monster20");
	Zombie20->SetWorldPosition(5350.f, 5200.f);

	CZombie* Zombie21 = m_Owner->CreateObject<CZombie>("Monster21");
	Zombie21->SetWorldPosition(5350.f, 5100.f);

	CZombie* Zombie22 = m_Owner->CreateObject<CZombie>("Monster22");
	Zombie22->SetWorldPosition(5350.f, 5000.f);

	CZombie* Zombie23 = m_Owner->CreateObject<CZombie>("Monster23");
	Zombie23->SetWorldPosition(5350.f, 4900.f);*/

	
	/*CAssassin* Assassin1 = m_Owner->CreateObject<CAssassin>("Assassin1");
	Assassin1->SetWorldPosition(2600.f, 600.f);

	CAssassin* Assassin2 = m_Owner->CreateObject<CAssassin>("Assassin2");
	Assassin2->SetWorldPosition(2600.f, 700.f);

	CAssassin* Assassin3 = m_Owner->CreateObject<CAssassin>("Assassin3");
	Assassin3->SetWorldPosition(2600.f, 800.f);

	CAssassin* Assassin4 = m_Owner->CreateObject<CAssassin>("Assassin4");
	Assassin4->SetWorldPosition(2600.f, 500.f);

	CAssassin* Assassin5 = m_Owner->CreateObject<CAssassin>("Assassin5");
	Assassin5->SetWorldPosition(2600.f, 900.f);*/

    /*CBoss* Boss = m_Owner->CreateObject<CBoss>("Boss");
    Boss->ShowIntro();
    Boss->SetWorldPosition(6000.f, 4000.f);*/
	
    CMobSpawner* Spawner = m_Owner->CreateObject<CMobSpawner>("Spawner");
    Spawner->CreateSpawnArea(Vector2(5400.f, 3100.f));

	// �ӽù��
	CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");
    

	CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");
	SetPlayerObject(Player);
	Player->SetWorldPosition(5400.f,3100.f);
    Player->SetWorldPosition(5350.f, 3900.f);

    /*CZombie* Zombie1 = m_Owner->CreateObject<CZombie>("Monster23");
    Zombie1->SetWorldPosition(5400.f, 3500.f);*/

	return true;
}

void CMainSceneInfo::Update(float DeltaTime)
{
    // ųī��Ʈ�� 20�� �Ѿ�� ������ ���� 
    if (m_KillCount >= 10 && !m_StartBossFight)
    {
        m_StartBossFight = true;

        // û��
        CleanMonster();
        
        // �����̿� ��� - �ƾ� ���� (�ð�)
        // ī�޶� �����̴� 3�� + ������ �����ϴ� 5�� 
        m_MainHUD->StartCutScene(10.f);
   
        // ī�޶� ��� - ��Ʈ�� ���� (������ġ, ������, �ӵ�, �ӹ��½ð�)
        // ������ġ�� �÷��̾���ġ���޾ƿ���, �������� ������ġ�� �Ѵ�. 
        m_Owner->GetCameraManager()->GetCurrentCamera()
            ->PatrolCameraPos(m_PlayerObject->GetWorldPos(), Vector3(6000.f, 4000.f, 0.f), 5.f);
    }
}

void CMainSceneInfo::CreateBoss()
{
    m_Owner->GetResource()->SoundStop("Field");
    m_Owner->GetResource()->SoundPlay("Boss");

    CBoss* Boss = m_Owner->CreateObject<CBoss>("Boss");
    Boss->ShowIntro();
    Boss->SetWorldPosition(6000.f, 4000.f);
}

void CMainSceneInfo::AddHitCount()
{
    m_MainHUD->AddHitCount();
}

void CMainSceneInfo::AddChainCount()
{
    m_MainHUD->AddChainCount();
}

void CMainSceneInfo::SetJustGuardMessage()
{
    m_MainHUD->SetJustGuardMessage();
}

void CMainSceneInfo::SetCounterMessage()
{
    m_MainHUD->SetCounterMessage();
}
