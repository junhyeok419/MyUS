
#include "TestSceneInfo.h"
#include "Scene/Scene.h"
#include "../UI/MainHUD.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Zombie.h"
#include "../GameObject/Assassin.h"
#include "../GameObject/Boss.h"

CTestSceneInfo::CTestSceneInfo()
{
}

CTestSceneInfo::~CTestSceneInfo()
{
}

bool CTestSceneInfo::Init()
{
    CSceneInfo::Init();

    m_MainHUD = m_Owner->GetViewport()->CreateUIWindow<CMainHUD>("MainHUD");

    m_Owner->GetResource()->SoundPlay("Field");

    /*CZombie* Zombie1 = m_Owner->CreateObject<CZombie>("Monster1");
    Zombie1->SetWorldPosition(500.f, 500.f);*/

    //CZombie* Zombie1 = m_Owner->CreateObject<CZombie>("Monster1");
    //Zombie1->SetWorldPosition(500.f, 500.f);

    //CZombie* Zombie2 = m_Owner->CreateObject<CZombie>("Monster2");
    //Zombie2->SetWorldPosition(600.f, 500.f);

    //CZombie* Zombie3 = m_Owner->CreateObject<CZombie>("Monster3");
    //Zombie3->SetWorldPosition(700.f, 500.f);
    //CZombie* Zombie4 = m_Owner->CreateObject<CZombie>("Monster4");
    //Zombie4->SetWorldPosition(800.f, 500.f);
    //CZombie* Zombie5 = m_Owner->CreateObject<CZombie>("Monster5");
    //Zombie5->SetWorldPosition(900.f, 500.f);
    //CZombie* Zombie6 = m_Owner->CreateObject<CZombie>("Monster6");
    //Zombie6->SetWorldPosition(1000.f, 500.f);
    //CZombie* Zombie7 = m_Owner->CreateObject<CZombie>("Monster7");
    //Zombie7->SetWorldPosition(1100.f, 500.f);

    //CZombie* Zombie8 = m_Owner->CreateObject<CZombie>("Monster8");
    //Zombie1->SetWorldPosition(500.f, 100.f);

    //CZombie* Zombie9 = m_Owner->CreateObject<CZombie>("Monster9");
    //Zombie1->SetWorldPosition(500.f, 200.f);

    //CZombie* Zombie10 = m_Owner->CreateObject<CZombie>("Monster10");
    //Zombie1->SetWorldPosition(500.f, 300.f);

    //CZombie* Zombie11= m_Owner->CreateObject<CZombie>("Monster11");
    //Zombie1->SetWorldPosition(500.f, 400.f);

    //CZombie* Zombie12 = m_Owner->CreateObject<CZombie>("Monster12");
    //Zombie1->SetWorldPosition(500.f, 500.f);

    //CZombie* Zombie13 = m_Owner->CreateObject<CZombie>("Monster13");
    //Zombie1->SetWorldPosition(500.f, 600.f);

    //CZombie* Zombie14= m_Owner->CreateObject<CZombie>("Monster14");
    //Zombie1->SetWorldPosition(500.f, 700.f);

    //CZombie* Zombie15= m_Owner->CreateObject<CZombie>("Monster15");
    //Zombie1->SetWorldPosition(500.f, 800.f);

    //CZombie* Zombie16= m_Owner->CreateObject<CZombie>("Monster16");
    //Zombie1->SetWorldPosition(500.f, 900.f);

    //CZombie* Zombie17= m_Owner->CreateObject<CZombie>("Monster17");
    //Zombie1->SetWorldPosition(500.f, 1000.f);

    //CZombie* Zombie18= m_Owner->CreateObject<CZombie>("Monster18");
    //Zombie1->SetWorldPosition(500.f, 1100.f);

    //CZombie* Zombie19 = m_Owner->CreateObject<CZombie>("Monster19");
    //Zombie1->SetWorldPosition(700.f, 400.f);

    //CZombie* Zombie20 = m_Owner->CreateObject<CZombie>("Monster20");
    //Zombie1->SetWorldPosition(700.f, 500.f);

    //CZombie* Zombie21 = m_Owner->CreateObject<CZombie>("Monster21");
    //Zombie1->SetWorldPosition(700.f, 600.f);

    //CZombie* Zombie22 = m_Owner->CreateObject<CZombie>("Monster22");
    //Zombie1->SetWorldPosition(700.f, 700.f);

    //CZombie* Zombie23 = m_Owner->CreateObject<CZombie>("Monster23");
    //Zombie1->SetWorldPosition(700.f, 800.f);


    CAssassin* Assassin1 = m_Owner->CreateObject<CAssassin>("Assassin1");
    Assassin1->SetWorldPosition(2600.f, 600.f);

    CAssassin* Assassin2 = m_Owner->CreateObject<CAssassin>("Assassin2");
    Assassin2->SetWorldPosition(2600.f, 700.f);

    CAssassin* Assassin3 = m_Owner->CreateObject<CAssassin>("Assassin3");
    Assassin3->SetWorldPosition(2600.f, 800.f);

    CAssassin* Assassin4 = m_Owner->CreateObject<CAssassin>("Assassin4");
    Assassin4->SetWorldPosition(2600.f, 500.f);

    CAssassin* Assassin5 = m_Owner->CreateObject<CAssassin>("Assassin5");
    Assassin5->SetWorldPosition(2600.f, 900.f);

    //CBoss* Boss = m_Owner->CreateObject<CBoss>("Boss");
    ////Boss->ShowIntro();
    //Boss->SetWorldPosition(2600.f, 500.f);

    // 임시배경
    CMonster* Monster = m_Owner->CreateObject<CMonster>("Monster");

    CPlayer2D* Player = m_Owner->CreateObject<CPlayer2D>("Player2D");
    SetPlayerObject(Player);
    Player->SetWorldPosition(7500.f, 7500.f);

    return true;
}
