#include "DefaultSetting.h"
#include "../GameObject/Player2D.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Bullet.h"
#include "../UI/StartSceneUI.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "CollisionManager.h"

CDefaultSetting::CDefaultSetting()
{
}

CDefaultSetting::~CDefaultSetting()
{
}

void CDefaultSetting::Init()
{
    LoadSound();

    LoadResource();

    LoadResourceMonster();

	CreateCDO();

	SetInput();

    SetCollision();
}

void CDefaultSetting::CreateCDO()
{
    CScene::CreateObjectCDO<CPlayer2D>("Player2D");
    CScene::CreateObjectCDO<CMonster>("Monster");
    CScene::CreateObjectCDO<CBullet>("Bullet");

    CScene::CreateUIWindowCDO<CStartSceneUI>("StartSceneUI");
}

void CDefaultSetting::LoadSound()
{
    CResourceManager::GetInst()->CreateSoundChannel("Effect1");
    CResourceManager::GetInst()->CreateSoundChannel("Effect2");
    CResourceManager::GetInst()->CreateSoundChannel("Effect3");
    CResourceManager::GetInst()->CreateSoundChannel("Back");

    CResourceManager::GetInst()->SetVolume("Effect1", 40);
    CResourceManager::GetInst()->SetVolume("Effect2", 80);
    CResourceManager::GetInst()->SetVolume("Effect3", 100);
    CResourceManager::GetInst()->SetVolume("Back", 30);    // 30으로 세팅 / 임시 0

    CResourceManager::GetInst()->LoadSound("Effect1", "Hit1", false, "Unsouled_Sound/Game/CombatBase/HitSound01.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "Hit2", false, "Unsouled_Sound/Game/CombatBase/HitSound02.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "Hit3", false, "Unsouled_Sound/Game/CombatBase/HitSound03.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "SuperArmor1", false, "Unsouled_Sound/Game/CombatBase/Effect_SuperArmor.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "SuperArmor2", false, "Unsouled_Sound/Game/CombatBase/Effect_SuperArmor02.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "GuardStart", false, "Unsouled_Sound/Game/CombatBase/Guard.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "Guard1", false, "Unsouled_Sound/Game/CombatBase/Guard01.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "Guard2", false, "Unsouled_Sound/Game/CombatBase/Guard02.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "JustGuard", false, "Unsouled_Sound/Game/CombatBase/JustGuard.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "DashAttack", false, "Unsouled_Sound/Game/CombatBase/DashAt02.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "Dash", false, "Unsouled_Sound/Game/CombatBase/DragDustSShort.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "Counter1", false, "Unsouled_Sound/Game/CombatBase/Counter.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "Counter2", false, "Unsouled_Sound/Game/CombatBase/Counter02.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "CounterHit", false, "Unsouled_Sound/Game/CombatBase/Assassin_CounterHit.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "CounterHit2", false, "Unsouled_Sound/Game/CombatBase/ZombieArcher_CounterHit.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "NormalSwing", false, "Unsouled_Sound/Game/Effect/NormalSwing.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "BigSwing", false, "Unsouled_Sound/Game/Effect/BigSwing.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "DoubleEdgeSwing", false, "Unsouled_Sound/Game/Effect/DoubleEdgeSwing.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "FootStep_Grass", false, "Unsouled_Sound/Game/Effect/FootSteps_Grass.wav");
    CResourceManager::GetInst()->LoadSound("Effect1", "GhostMove", false, "Unsouled_Sound/Game/Effect/GhostMove.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "GhostSlashReady", false, "Unsouled_Sound/Game/CombatBase/SoulSlashReady.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "GhostSlash01", false, "Unsouled_Sound/Game/CombatBase/SoulSlash01.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "GhostSlash02", false, "Unsouled_Sound/Game/CombatBase/SoulSlash02.wav");

    // Boss Intro & Killed
    CResourceManager::GetInst()->LoadSound("Effect3", "BossIntroFallDown", false, "Unsouled_Sound/Game/Boss/Boss_Niug_FallDown.wav");
    CResourceManager::GetInst()->LoadSound("Effect3", "BossIntroShout", false, "Unsouled_Sound/Game/Boss/Boss_Niug_IntroShouts.wav");
    CResourceManager::GetInst()->LoadSound("Effect3", "BossKillCry", false, "Unsouled_Sound/Game/Boss/Boss_Niug_KilledCry.wav");
    // Boss Punch
    CResourceManager::GetInst()->LoadSound("Effect2", "BossPunchSwing", false, "Unsouled_Sound/Game/Boss/Punch/Boss_NiugWoL01_Swing.wav");
    // Boss Stomp
    CResourceManager::GetInst()->LoadSound("Effect2", "BossStompReady", false, "Unsouled_Sound/Game/Boss/Stomp/Boss_Niug_RageOfIsno_ReadyVoice.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "BossStompExplosion", false, "Unsouled_Sound/Game/Boss/Stomp/Boss_Niug_RageOfIsno_Explosion.wav"); // + Rush
    // Boss Rush
    CResourceManager::GetInst()->LoadSound("Effect2", "BossRushVoice", false, "Unsouled_Sound/Game/Boss/Rush/Boss_NiugBallistaShoulder_Voice.wav");
    CResourceManager::GetInst()->LoadSound("Effect2", "BossRushWind", false, "Unsouled_Sound/Game/Boss/Rush/Boss_NiugBallistaShoulder_Wind.wav");


    CResourceManager::GetInst()->LoadSound("Back", "Field", true, "Unsouled_Sound/Game/Back/Field.wav");
    CResourceManager::GetInst()->LoadSound("Back", "Boss", true, "Unsouled_Sound/Game/Back/Boss.wav");
}

void CDefaultSetting::LoadResource()
{
    std::vector<const TCHAR*>   vecFileName;

    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand"))
    {
        // 플레이어 정지 위
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);

                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Stand/ChehulisStand%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 1)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerStand", "PlayerStand", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStand", Vector2(0.f, 0.f), Vector2(17.f, 40.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStand")->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }



    // 플레이어 정지 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Stand/ChehulisStandBack%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 1)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerStandBack", "PlayerStandBack", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandBack")->AddFramePivot(0.5f, 0.f);


        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 정지 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Stand/ChehulisStand_Left%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 1)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerStandLeft", "PlayerStandLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(12.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandLeft", Vector2(0.f, 0.f), Vector2(11.f, 41.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.45f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandLeft")->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 정지 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Stand/ChehulisStand_Right%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 1)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerStandRight", "PlayerStandRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerStandRight", Vector2(0.f, 0.f), Vector2(10.f, 41.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerStandRight")->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 달리기 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Running/ChehulisRunning%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 2)
                    break;
            }
        }
        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerRunning", "PlayerRunning", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(15.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(16.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(15.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(16.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(15.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(16.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(17.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(19.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(16.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(16.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(16.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunning", Vector2(0.f, 0.f), Vector2(16.f, 40.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.6f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.56f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.6f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.56f, -0.04f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.6f, -0.02f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.625f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.588f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.526f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.687f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.625f, -0.04f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.625f, -0.02f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunning")->AddFramePivot(0.562f, 0.f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 달리기 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Running/ChehulisRunning_Right%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerRunningRight", "PlayerRunningRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(22.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(27.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(31.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(32.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(27.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(22.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(20.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(28.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(32.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(34.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningRight", Vector2(0.f, 0.f), Vector2(28.f, 41.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.62f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.636f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.666f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.612f, -0.04f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.625f, -0.02f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.55f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.636f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.6f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.642f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.6f, -0.1f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.617f, -0.05f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningRight")->AddFramePivot(0.535f, 0.f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 달리기 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Running/ChehulisRunning_Left%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 2)
                    break;
            }
        }
        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerRunningLeft", "PlayerRunningLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(22.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(20.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(28.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(32.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(34.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(28.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(22.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(27.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(31.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(32.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningLeft", Vector2(0.f, 0.f), Vector2(27.f, 41.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.318f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.35f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.32f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.375f, -0.1f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.352f, -0.05f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.428f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.333f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.318f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.296f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.354f, -0.05f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.343f, -0.025f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningLeft")->AddFramePivot(0.407f, 0.f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 달리기 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Running/ChehulisRunningBack%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerRunningBack", "PlayerRunningBack", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(16.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(16.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(15.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(16.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(18.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerRunningBack", Vector2(0.f, 0.f), Vector2(18.f, 41.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.58f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.55f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.55f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.55f, -0.04f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.639f, -0.02f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.51f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.55f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.48f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.58f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.55f, -0.04f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.58f, -0.02f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerRunningBack")->AddFramePivot(0.514f, 0.f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택1 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack01Down%d%d.png"),i,j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 1)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack1Down", "PlayerAttack1Down", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(67.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(67.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(44.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(42.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(42.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(40.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Down", Vector2(0.f, 0.f), Vector2(33.f, 36.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.8f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.8f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.8f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.8f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.44f, 0.28f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.44f, 0.28f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.68f, 0.23f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.66f, 0.14f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.66f, 0.14f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.65f, 0.14f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Down")->AddFramePivot(0.57f, 0.14f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택1 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack11Left"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 11; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack01Left%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack1Left", "PlayerAttack1Left", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(53.f, 52.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(53.f, 52.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(53.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(42.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(37.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(31.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Left", Vector2(0.f, 0.f), Vector2(31.f, 32.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.3f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.3f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.3f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.3f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.73f, 0.1f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.73f, 0.1f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.73f, 0.12f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.666f, 0.143f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.621f, 0.143f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.548f, 0.17f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Left")->AddFramePivot(0.548f, 0.07f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택1 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack01Right00.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack01Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack1Right", "PlayerAttack1Right", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(65.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(64.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(57.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(52.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(39.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(42.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Right", Vector2(0.f, 0.f), Vector2(39.f, 29.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(1.f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(1.f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(1.f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(1.f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(0.55f, 0.2f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(0.546f, 0.2f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(0.614f, 0.2f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(0.673f, 0.213f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(0.897f, 0.213f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(0.9f, 0.26f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Right")->AddFramePivot(0.897f, 0.104f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택1 위쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack01Up00.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 0; i < 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack01Up0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack1Up", "PlayerAttack1Up", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(52.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(52.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(42.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(41.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(34.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(32.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(32.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack1Up", Vector2(0.f, 0.f), Vector2(34.f, 38.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.333f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.333f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.333f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.333f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.423f, 0.22f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.461f, 0.186f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.333f, 0.186f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.317f, 0.24f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.382f, 0.264f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.406f, 0.264f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.406f, 0.3f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack1Up")->AddFramePivot(0.441f, 0.264f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택2 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Down01.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Down0%d.png"), i);

            vecFileName.push_back(FileName);
        }

    
        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack2Down", "PlayerAttack2Down", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(17.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(17.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(17.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(17.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(68.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(68.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(66.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(43.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(43.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(45.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Down", Vector2(0.f, 0.f), Vector2(41.f, 29.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.19f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.19f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.19f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.19f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.529f, 0.364f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.529f, 0.364f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.515f, 0.2f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.255f, 0.035f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.255f, 0.035f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.244f, 0.035f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Down")->AddFramePivot(0.244f, 0.035f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택2 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Left01.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack2Left", "PlayerAttack2Left", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(68.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(68.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(57.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(57.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(39.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(40.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Left", Vector2(0.f, 0.f), Vector2(39.f, 27.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.307f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.307f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.307f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.307f, 0.f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.558f, 0.237f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.558f, 0.237f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.666f, 0.122f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.666f, 0.034f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.512f, 0.038f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.475f, 0.038f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Left")->AddFramePivot(0.512f, 0.038f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택2 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Right00.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

    
        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack2Right", "PlayerAttack2Right", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(70.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(70.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(49.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(45.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(36.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(38.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Right", Vector2(0.f, 0.f), Vector2(28.f, 36.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.65f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.65f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.65f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.65f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.485f, 0.190f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.485f, 0.190f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.265f, 0.167f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.288f, 0.167f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.361f, 0.167f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.342f, 0.163f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Right")->AddFramePivot(0.464f, 0.167f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택2 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Up00.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 0; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack02Up0%d.png"), i);

            vecFileName.push_back(FileName);
        }


        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack2Up", "PlayerAttack2Up", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(26.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(62.f, 52.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(62.f, 52.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(44.f, 52.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(33.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(33.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(33.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(29.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack2Up", Vector2(0.f, 0.f), Vector2(14.f, 38.f));

        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.461f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.461f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.461f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.461f, 0.033f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.467f, 0.116f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.403f, 0.135f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.568f, 0.135f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.575f, 0.175f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.575f, 0.175f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.575f, 0.175f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.517f, 0.233f);
        CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack2Up")->AddFramePivot(0.071f, 0.132f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택3 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Down"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Down00.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Down0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack3Down", "PlayerAttack3Down", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(58.f, 89.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(58.f, 89.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(51.f, 63.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(41.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(25.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Down", Vector2(0.f, 0.f), Vector2(17.f, 28.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Down");
        Sequence->AddFramePivot(0.466f, 0.024f);
        Sequence->AddFramePivot(0.466f, 0.024f);
        Sequence->AddFramePivot(0.466f, 0.024f);
        Sequence->AddFramePivot(0.466f, 0.024f);
        Sequence->AddFramePivot(0.466f, 0.024f);
        Sequence->AddFramePivot(0.534f, 0.439f);
        Sequence->AddFramePivot(0.534f, 0.439f);
        Sequence->AddFramePivot(0.470f, 0.62f);
        Sequence->AddFramePivot(0.341f, 0.673f);
        Sequence->AddFramePivot(0.160f, 0.487f);
        Sequence->AddFramePivot(0.173f, 0.388f);
        Sequence->AddFramePivot(0.235f, 0.322f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택3 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Left"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Left00.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 0; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack3Left", "PlayerAttack3Left", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(31.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(68.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(68.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(59.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(50.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(36.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Left", Vector2(0.f, 0.f), Vector2(32.f, 30.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Left");
        Sequence->AddFramePivot(0.354f, 0.13f);
        Sequence->AddFramePivot(0.354f, 0.13f);
        Sequence->AddFramePivot(0.354f, 0.13f);
        Sequence->AddFramePivot(0.354f, 0.13f);
        Sequence->AddFramePivot(0.354f, 0.13f);
        Sequence->AddFramePivot(0.558f, 0.082f);
        Sequence->AddFramePivot(0.558f, 0.082f);
        Sequence->AddFramePivot(0.644f, 0.09f);
        Sequence->AddFramePivot(0.58f, 0.132f);
        Sequence->AddFramePivot(0.416f, 0.2f);
        Sequence->AddFramePivot(0.343f, 0.067f);

        for (int i = 0; i < 11; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택3 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Right"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Right01.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack3Right", "PlayerAttack3Right", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(33.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(65.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(65.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(61.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(55.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(49.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(42.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(33.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Right", Vector2(0.f, 0.f), Vector2(33.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Right");
        Sequence->AddFramePivot(0.696f, 0.033f);
        Sequence->AddFramePivot(0.696f, 0.033f);
        Sequence->AddFramePivot(0.696f, 0.033f);
        Sequence->AddFramePivot(0.696f, 0.033f);
        Sequence->AddFramePivot(0.696f, 0.033f);
        Sequence->AddFramePivot(0.276f, 0.148f);
        Sequence->AddFramePivot(0.276f, 0.148f);
        Sequence->AddFramePivot(0.245f, 0.177f);
        Sequence->AddFramePivot(0.272f, 0.231f);
        Sequence->AddFramePivot(0.306f, 0.237f);
        Sequence->AddFramePivot(0.357f, 0.257f);
        Sequence->AddFramePivot(0.454f, 0.293f);
        Sequence->AddFramePivot(0.454f, 0.217f);

        for (int i = 0; i < 13; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택3 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Up"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Up01.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Attack/ChehulisAttack03Up0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttack3Up", "PlayerAttack3Up", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(18.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(40.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(40.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(39.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(24.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(15.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(15.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttack3Up", Vector2(0.f, 0.f), Vector2(15.f, 38.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttack3Up");
        Sequence->AddFramePivot(0.333f, 0.225f);
        Sequence->AddFramePivot(0.333f, 0.225f);
        Sequence->AddFramePivot(0.333f, 0.225f);
        Sequence->AddFramePivot(0.333f, 0.225f);
        Sequence->AddFramePivot(0.333f, 0.225f);
        Sequence->AddFramePivot(0.375f, 0.017f);
        Sequence->AddFramePivot(0.375f, 0.017f);
        Sequence->AddFramePivot(0.384f, 0.017f);
        Sequence->AddFramePivot(0.375f, 0.017f);
        Sequence->AddFramePivot(0.266f, 0.018f);
        Sequence->AddFramePivot(0.266f, 0.024f);
        Sequence->AddFramePivot(0.266f, 0.027f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 어택 먼지
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttackDust"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Dust/2DEffect_StatueDust030%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerAttackDust", "PlayerAttackDust", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(12.f, 9.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(12.f, 9.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(12.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(13.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(12.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(14.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(12.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerAttackDust", Vector2(0.f, 0.f), Vector2(11.f, 11.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerAttackDust");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 잔상, 이동 먼지
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerMoveDust"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Dust/2DEffect_DragDust0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerMoveDust", "PlayerMoveDust", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMoveDust", Vector2(0.f, 0.f), Vector2(11.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMoveDust", Vector2(0.f, 0.f), Vector2(11.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMoveDust", Vector2(0.f, 0.f), Vector2(11.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMoveDust", Vector2(0.f, 0.f), Vector2(11.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMoveDust", Vector2(0.f, 0.f), Vector2(11.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerMoveDust", Vector2(0.f, 0.f), Vector2(11.f, 12.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerMoveDust");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }


    // 플레이어 대쉬 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                /*if (i == 0 && j == 0)
                    j = 1;*/

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Dash/ChehulisMoveLeft%d%d.png"), i,j);

                vecFileName.push_back(FileName);

                if (i == 2 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashLeft", "PlayerDashLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(37.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(27.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(27.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 23; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                /*if (i == 0 && j == 0)
                    j = 1;*/

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Dash/ChehulisMoveRight%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 2 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashRight", "PlayerDashRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(36.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(25.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(29.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(29.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(29.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(29.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(29.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashRight", Vector2(0.f, 0.f), Vector2(29.f, 33.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 23; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 위쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashUp"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                /*if (i == 0 && j == 0)
                    j = 1;*/

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Dash/ChehulisMoveUp%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 2 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashUp", "PlayerDashUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(22.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(22.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(16.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(16.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(16.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(16.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(16.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashUp", Vector2(0.f, 0.f), Vector2(16.f, 42.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashUp");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 23; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashDown"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                /*if (i == 0 && j == 0)
                    j = 1;*/

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Dash/ChehulisMoveDown%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 2 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashDown", "PlayerDashDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashDown", Vector2(0.f, 0.f), Vector2(18.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashDown");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 23; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttackLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackLeft", "PlayerDashAttackLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(38.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(92.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(92.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(73.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(73.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(64.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(64.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(64.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(64.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackLeft", Vector2(0.f, 0.f), Vector2(64.f, 29.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackLeft");
        Sequence->AddFramePivot(0.447f, 0.f);
        Sequence->AddFramePivot(0.565f, 0.f);
        Sequence->AddFramePivot(0.565f, 0.f);
        Sequence->AddFramePivot(0.712f, 0.f);
        Sequence->AddFramePivot(0.712f, 0.f);
        Sequence->AddFramePivot(0.671f, 0.f);
        Sequence->AddFramePivot(0.671f, 0.f);
        Sequence->AddFramePivot(0.671f, 0.f);
        Sequence->AddFramePivot(0.671f, 0.f);
        Sequence->AddFramePivot(0.671f, 0.f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 왼쪽 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackDownLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttack_DownLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackDownLeft", "PlayerDashAttackDownLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(45.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(45.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(42.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(46.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(45.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(42.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(33.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(33.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(33.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownLeft", Vector2(0.f, 0.f), Vector2(33.f, 29.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackDownLeft");
        Sequence->AddFramePivot(0.688f, 0.286f);
        Sequence->AddFramePivot(0.688f, 0.286f);
        Sequence->AddFramePivot(0.738f, 0.286f);
        Sequence->AddFramePivot(0.673f, 0.391f);
        Sequence->AddFramePivot(0.688f, 0.391f);
        Sequence->AddFramePivot(0.690f, 0.375f);
        Sequence->AddFramePivot(0.575f, 0.138f);
        Sequence->AddFramePivot(0.575f, 0.138f);
        Sequence->AddFramePivot(0.575f, 0.138f);
        Sequence->AddFramePivot(0.575f, 0.138f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttackRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackRight", "PlayerDashAttackRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(31.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(92.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(73.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(73.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(73.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(63.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(63.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(63.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(63.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackRight", Vector2(0.f, 0.f), Vector2(63.f, 28.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackRight");
        Sequence->AddFramePivot(0.630f, 0.3f);
        Sequence->AddFramePivot(0.467f, 0.069f);
        Sequence->AddFramePivot(0.328f, 0.036f);
        Sequence->AddFramePivot(0.328f, 0.036f);
        Sequence->AddFramePivot(0.328f, 0.036f);
        Sequence->AddFramePivot(0.380f, 0.036f);
        Sequence->AddFramePivot(0.380f, 0.036f);
        Sequence->AddFramePivot(0.380f, 0.036f);
        Sequence->AddFramePivot(0.380f, 0.036f);
        Sequence->AddFramePivot(0.380f, 0.036f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 오른쪽 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackDownRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttack_DownRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackDownRight", "PlayerDashAttackDownRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(61.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(61.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(61.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(63.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(60.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(61.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(41.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(41.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(41.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDownRight", Vector2(0.f, 0.f), Vector2(41.f, 28.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackDownRight");
        Sequence->AddFramePivot(0.278f, 0.256f);
        Sequence->AddFramePivot(0.278f, 0.256f);
        Sequence->AddFramePivot(0.278f, 0.256f);
        Sequence->AddFramePivot(0.301f, 0.308f);
        Sequence->AddFramePivot(0.283f, 0.308f);
        Sequence->AddFramePivot(0.295f, 0.308f);
        Sequence->AddFramePivot(0.463f, 0.036f);
        Sequence->AddFramePivot(0.463f, 0.036f);
        Sequence->AddFramePivot(0.463f, 0.036f);
        Sequence->AddFramePivot(0.463f, 0.036f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 위쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackUp"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttackUp0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackUp", "PlayerDashAttackUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(18.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(29.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(20.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(17.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(15.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(15.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(15.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(15.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(15.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUp", Vector2(0.f, 0.f), Vector2(15.f, 46.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackUp");
        Sequence->AddFramePivot(0.5f, 0.027f);
        Sequence->AddFramePivot(0.827f, 0.102f);
        Sequence->AddFramePivot(0.75f, 0.017f);
        Sequence->AddFramePivot(0.70f, 0.018f);
        Sequence->AddFramePivot(0.8f, 0.044f);
        Sequence->AddFramePivot(0.8f, 0.044f);
        Sequence->AddFramePivot(0.8f, 0.044f);
        Sequence->AddFramePivot(0.8f, 0.044f);
        Sequence->AddFramePivot(0.8f, 0.044f);
        Sequence->AddFramePivot(0.8f, 0.044f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 왼쪽 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackUpLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttack_UpLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackUpLeft", "PlayerDashAttackUpLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(35.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(35.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(35.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(35.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(34.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(28.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(24.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(24.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(24.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpLeft", Vector2(0.f, 0.f), Vector2(24.f, 40.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackUpLeft");
        Sequence->AddFramePivot(0.714f, 0.138f);
        Sequence->AddFramePivot(0.714f, 0.138f);
        Sequence->AddFramePivot(0.714f, 0.138f);
        Sequence->AddFramePivot(0.714f, 0.020f);
        Sequence->AddFramePivot(0.705f, 0.020f);
        Sequence->AddFramePivot(0.642f, 0.022f);
        Sequence->AddFramePivot(0.583f, 0.025f);
        Sequence->AddFramePivot(0.583f, 0.025f);
        Sequence->AddFramePivot(0.583f, 0.025f);
        Sequence->AddFramePivot(0.583f, 0.025f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 오른쪽 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackUpRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttack_UpRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackUpRight", "PlayerDashAttackUpRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(36.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(36.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(36.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(36.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(34.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(31.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(24.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(24.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(24.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackUpRight", Vector2(0.f, 0.f), Vector2(24.f, 39.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackUpRight");
        Sequence->AddFramePivot(0.222f, 0.167f);
        Sequence->AddFramePivot(0.222f, 0.167f);
        Sequence->AddFramePivot(0.222f, 0.167f);
        Sequence->AddFramePivot(0.222f, 0.020f);
        Sequence->AddFramePivot(0.235f, 0.020f);
        Sequence->AddFramePivot(0.258f, 0.021f);
        Sequence->AddFramePivot(0.333f, 0.026f);
        Sequence->AddFramePivot(0.333f, 0.026f);
        Sequence->AddFramePivot(0.333f, 0.026f);
        Sequence->AddFramePivot(0.333f, 0.026f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 대쉬 어택 아래쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackDown"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DashAttack/ChehulisDashAttackDown0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDashAttackDown", "PlayerDashAttackDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(17.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(17.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(23.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(16.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(12.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(12.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(12.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(12.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(12.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDashAttackDown", Vector2(0.f, 0.f), Vector2(12.f, 28.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDashAttackDown");
        Sequence->AddFramePivot(0.411f, 0.f);
        Sequence->AddFramePivot(0.411f, 0.f);
        Sequence->AddFramePivot(0.652f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.633f);
        Sequence->AddFramePivot(0.333f, 0.633f);
        Sequence->AddFramePivot(0.333f, 0.393f);
        Sequence->AddFramePivot(0.333f, 0.393f);
        Sequence->AddFramePivot(0.333f, 0.393f);
        Sequence->AddFramePivot(0.333f, 0.393f);
        Sequence->AddFramePivot(0.333f, 0.393f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 체인 이펙트
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerChain"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Chain/2DEffect_ChainEffect0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerChain", "PlayerChain", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerChain", Vector2(0.f, 0.f), Vector2(11.f, 11.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerChain", Vector2(0.f, 0.f), Vector2(27.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerChain", Vector2(0.f, 0.f), Vector2(41.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerChain", Vector2(0.f, 0.f), Vector2(47.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerChain", Vector2(0.f, 0.f), Vector2(47.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerChain", Vector2(0.f, 0.f), Vector2(47.f, 47.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerChain");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
     
        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 정지 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockDown"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Guard/ChehulisBlockDown0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockDown", "PlayerBlockDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockDown", Vector2(0.f, 0.f), Vector2(27.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockDown", Vector2(0.f, 0.f), Vector2(27.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockDown", Vector2(0.f, 0.f), Vector2(27.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockDown");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    
    // 플레이어 가드 정지 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Guard/ChehulisBlockLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockLeft", "PlayerBlockLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLeft", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLeft", Vector2(0.f, 0.f), Vector2(17.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLeft", Vector2(0.f, 0.f), Vector2(18.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.529f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 정지 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Guard/ChehulisBlockRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockRight", "PlayerBlockRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockRight", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockRight", Vector2(0.f, 0.f), Vector2(18.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockRight", Vector2(0.f, 0.f), Vector2(18.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    
    // 플레이어 가드 정지 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockUp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Guard/ChehulisBlockUp0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockUp", "PlayerBlockUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockUp", Vector2(0.f, 0.f), Vector2(25.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockUp", Vector2(0.f, 0.f), Vector2(25.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockUp", Vector2(0.f, 0.f), Vector2(25.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockUp");
        Sequence->AddFramePivot(0.64f, 0.f);
        Sequence->AddFramePivot(0.64f, 0.f);
        Sequence->AddFramePivot(0.64f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 양날베기 준비 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeRight_Pre"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Right_Pre0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeRight_Pre", "PlayerDoubleEdgeRight_Pre", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight_Pre", Vector2(0.f, 0.f), Vector2(25.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight_Pre", Vector2(0.f, 0.f), Vector2(28.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight_Pre", Vector2(0.f, 0.f), Vector2(28.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight_Pre", Vector2(0.f, 0.f), Vector2(28.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight_Pre", Vector2(0.f, 0.f), Vector2(28.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight_Pre", Vector2(0.f, 0.f), Vector2(28.f, 36.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeRight_Pre");
        Sequence->AddFramePivot(0.72f, 0.028f);
        Sequence->AddFramePivot(0.428f, 0.028f);
        Sequence->AddFramePivot(0.428f, 0.028f);
        Sequence->AddFramePivot(0.428f, 0.028f);
        Sequence->AddFramePivot(0.428f, 0.028f);
        Sequence->AddFramePivot(0.428f, 0.028f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 양날베기 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Right%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 7)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeRight", "PlayerDoubleEdgeRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(25.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(61.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(65.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(31.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(55.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(59.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(59.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(40.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeRight", Vector2(0.f, 0.f), Vector2(37.f, 24.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeRight");
        Sequence->AddFramePivot(0.56f, 0.032f);
        Sequence->AddFramePivot(0.5f, 0.396f);
        Sequence->AddFramePivot(0.446f, 0.191f);
        Sequence->AddFramePivot(0.702f, 0.112f);
        Sequence->AddFramePivot(0.677f, 0.030f);
        Sequence->AddFramePivot(0.5f, 0.440f);
        Sequence->AddFramePivot(0.457f, 0.343f);
        Sequence->AddFramePivot(0.474f, 0.315f);
        Sequence->AddFramePivot(0.7f, 0.112f);
        Sequence->AddFramePivot(0.729f, 0.044f);
        Sequence->AddFramePivot(0.729f, 0.044f);
        Sequence->AddFramePivot(0.729f, 0.044f);
        Sequence->AddFramePivot(0.729f, 0.044f);
        Sequence->AddFramePivot(0.729f, 0.044f);
        Sequence->AddFramePivot(0.729f, 0.044f);
        Sequence->AddFramePivot(0.729f, 0.044f);
        Sequence->AddFramePivot(0.729f, 0.044f);

        for (int i = 0; i < 17; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 양날베기 준비 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeDown_Pre"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Down_Pre0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeDown_Pre", "PlayerDoubleEdgeDown_Pre", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown_Pre", Vector2(0.f, 0.f), Vector2(25.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeDown_Pre");
        Sequence->AddFramePivot(0.28f, 0.028f);
        Sequence->AddFramePivot(0.572f, 0.028f);
        Sequence->AddFramePivot(0.572f, 0.028f);
        Sequence->AddFramePivot(0.572f, 0.028f);
        Sequence->AddFramePivot(0.572f, 0.028f);
        Sequence->AddFramePivot(0.572f, 0.028f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 양날베기 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeDown"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Down%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 7)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeDown", "PlayerDoubleEdgeDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(27.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(61.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(65.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(40.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(35.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(55.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(59.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(59.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(37.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeDown", Vector2(0.f, 0.f), Vector2(39.f, 24.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeDown");
        Sequence->AddFramePivot(0.44f, 0.032f);
        Sequence->AddFramePivot(0.5f, 0.396f);
        Sequence->AddFramePivot(0.554f, 0.191f);
        Sequence->AddFramePivot(0.298f, 0.112f);
        Sequence->AddFramePivot(0.323f, 0.030f);
        Sequence->AddFramePivot(0.5f, 0.440f);
        Sequence->AddFramePivot(0.508f, 0.343f);
        Sequence->AddFramePivot(0.508f, 0.315f);
        Sequence->AddFramePivot(0.282f, 0.112f);
        Sequence->AddFramePivot(0.243f, 0.044f);  // 10
        Sequence->AddFramePivot(0.282f, 0.044f);
        Sequence->AddFramePivot(0.282f, 0.044f);
        Sequence->AddFramePivot(0.282f, 0.044f);
        Sequence->AddFramePivot(0.282f, 0.044f);
        Sequence->AddFramePivot(0.282f, 0.044f);
        Sequence->AddFramePivot(0.282f, 0.044f);
        Sequence->AddFramePivot(0.282f, 0.044f);

        for (int i = 0; i < 17; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 양날베기 준비 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeLeft_Pre"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Left_Pre0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeLeft_Pre", "PlayerDoubleEdgeLeft_Pre", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft_Pre", Vector2(0.f, 0.f), Vector2(24.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft_Pre", Vector2(0.f, 0.f), Vector2(26.f, 36.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeLeft_Pre");
        Sequence->AddFramePivot(0.458f, 0.f);
        Sequence->AddFramePivot(0.458f, 0.f);
        Sequence->AddFramePivot(0.458f, 0.f);
        Sequence->AddFramePivot(0.458f, 0.f);
        Sequence->AddFramePivot(0.458f, 0.f);
        Sequence->AddFramePivot(0.458f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 양날베기 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Left%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 7)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeLeft", "PlayerDoubleEdgeLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(28.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(59.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(66.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(42.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(30.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(58.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(58.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(55.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(35.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeLeft", Vector2(0.f, 0.f), Vector2(29.f, 25.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeLeft");
        Sequence->AddFramePivot(0.571f, 0.031f);
        Sequence->AddFramePivot(0.576f, 0.177f);
        Sequence->AddFramePivot(0.545f, 0.029f);
        Sequence->AddFramePivot(0.357f, 0.030f);
        Sequence->AddFramePivot(0.2f, 0.032f);
        Sequence->AddFramePivot(0.551f, 0.107f);
        Sequence->AddFramePivot(0.551f, 0.032f);
        Sequence->AddFramePivot(0.527f, 0.061f);
        Sequence->AddFramePivot(0.314f, 0.040f);
        Sequence->AddFramePivot(0.379f, 0.040f);  // 10
        Sequence->AddFramePivot(0.379f, 0.040f);
        Sequence->AddFramePivot(0.379f, 0.040f);
        Sequence->AddFramePivot(0.379f, 0.040f);
        Sequence->AddFramePivot(0.379f, 0.040f);
        Sequence->AddFramePivot(0.379f, 0.040f);
        Sequence->AddFramePivot(0.379f, 0.040f);
        Sequence->AddFramePivot(0.379f, 0.040f);

        for (int i = 0; i < 17; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 양날베기 준비 위쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeUp_Pre"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Up_Pre0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeUp_Pre", "PlayerDoubleEdgeUp_Pre", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp_Pre", Vector2(0.f, 0.f), Vector2(23.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp_Pre", Vector2(0.f, 0.f), Vector2(24.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp_Pre", Vector2(0.f, 0.f), Vector2(24.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp_Pre", Vector2(0.f, 0.f), Vector2(24.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp_Pre", Vector2(0.f, 0.f), Vector2(24.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp_Pre", Vector2(0.f, 0.f), Vector2(24.f, 36.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeUp_Pre");
        Sequence->AddFramePivot(0.521f, 0.f);
        Sequence->AddFramePivot(0.521f, 0.f);
        Sequence->AddFramePivot(0.521f, 0.f);
        Sequence->AddFramePivot(0.521f, 0.f);
        Sequence->AddFramePivot(0.521f, 0.f);
        Sequence->AddFramePivot(0.521f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    
    // 플레이어 양날베기 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeUp"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/DoubleEdge/Maras_DoubleEdge_Up%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 7)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerDoubleEdgeUp", "PlayerDoubleEdgeUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(28.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(59.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(66.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(42.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(31.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(58.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(58.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(55.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(35.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(33.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerDoubleEdgeUp", Vector2(0.f, 0.f), Vector2(32.f, 25.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerDoubleEdgeUp");
        Sequence->AddFramePivot(0.5f, 0.031f);
        Sequence->AddFramePivot(0.491f, 0.177f);
        Sequence->AddFramePivot(0.469f, 0.029f);
        Sequence->AddFramePivot(0.682f, 0.030f);
        Sequence->AddFramePivot(0.677f, 0.032f);
        Sequence->AddFramePivot(0.517f, 0.107f);
        Sequence->AddFramePivot(0.465f, 0.032f);
        Sequence->AddFramePivot(0.472f, 0.033f);
        Sequence->AddFramePivot(0.714f, 0.040f);
        Sequence->AddFramePivot(0.575f, 0.040f);  // 10
        Sequence->AddFramePivot(0.593f, 0.040f);
        Sequence->AddFramePivot(0.593f, 0.040f);
        Sequence->AddFramePivot(0.593f, 0.040f);
        Sequence->AddFramePivot(0.593f, 0.040f);
        Sequence->AddFramePivot(0.593f, 0.040f);
        Sequence->AddFramePivot(0.593f, 0.040f);
        Sequence->AddFramePivot(0.593f, 0.040f);

        for (int i = 0; i < 17; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 양날베기 바닥 먼지 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCircleDust"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Dust/2DEffect_CircleDust0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerCircleDust", "PlayerCircleDust", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCircleDust", Vector2(0.f, 0.f), Vector2(44.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCircleDust", Vector2(0.f, 0.f), Vector2(44.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCircleDust", Vector2(0.f, 0.f), Vector2(44.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCircleDust", Vector2(0.f, 0.f), Vector2(44.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCircleDust", Vector2(0.f, 0.f), Vector2(44.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCircleDust", Vector2(0.f, 0.f), Vector2(44.f, 21.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCircleDust");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 양날베기 기 이펙트 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerKi"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Ki/2DEffect_Ki0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerKi", "PlayerKi", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKi", Vector2(0.f, 0.f), Vector2(14.f, 14.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKi", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKi", Vector2(0.f, 0.f), Vector2(10.f, 10.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKi", Vector2(0.f, 0.f), Vector2(22.f, 22.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKi", Vector2(0.f, 0.f), Vector2(28.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKi", Vector2(0.f, 0.f), Vector2(30.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKi", Vector2(0.f, 0.f), Vector2(29.f, 30.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerKi");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 양날베기 기 배경
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerKiBackground"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 1; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Ki/2DEffect_KiBackground.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerKiBackground", "PlayerKiBackground", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerKiBackground", Vector2(0.f, 0.f), Vector2(40.f, 40.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerKiBackground");
        Sequence->AddFramePivot(0.5f, 0.f);
    
        for (int i = 0; i < 1; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 히트 by 오른쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerHitByRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Hit/ChehulisHitby_Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerHitByRight", "PlayerHitByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByRight", Vector2(0.f, 0.f), Vector2(21.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByRight", Vector2(0.f, 0.f), Vector2(15.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByRight", Vector2(0.f, 0.f), Vector2(32.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByRight", Vector2(0.f, 0.f), Vector2(32.f, 25.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerHitByRight");
        Sequence->AddFramePivot(0.5f, -0.3f);
        Sequence->AddFramePivot(0.5f, -0.2f);
        Sequence->AddFramePivot(0.5f, -0.1f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 히트 by 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerHitByLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Hit/ChehulisHitby_Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerHitByLeft", "PlayerHitByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByLeft", Vector2(0.f, 0.f), Vector2(17.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByLeft", Vector2(0.f, 0.f), Vector2(16.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByLeft", Vector2(0.f, 0.f), Vector2(19.f, 27.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerHitByLeft");
        Sequence->AddFramePivot(0.5f, -0.3f);
        Sequence->AddFramePivot(0.5f, -0.15f);
        Sequence->AddFramePivot(0.6f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 히트 by 아래쪽  
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerHitByDown"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Hit/ChehulisHitby_Down0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerHitByDown", "PlayerHitByDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByDown", Vector2(0.f, 0.f), Vector2(16.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByDown", Vector2(0.f, 0.f), Vector2(15.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerHitByDown", Vector2(0.f, 0.f), Vector2(22.f, 29.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerHitByDown");
        Sequence->AddFramePivot(0.5f, -0.3f);
        Sequence->AddFramePivot(0.5f, -0.15f);
        Sequence->AddFramePivot(0.6f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 기본 타격 이펙트 1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSwordSpark1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/SwordSpark/2DEffect_SwordSpark0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSwordSpark1", "PlayerSwordSpark1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark1", Vector2(0.f, 0.f), Vector2(62.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark1", Vector2(0.f, 0.f), Vector2(62.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark1", Vector2(0.f, 0.f), Vector2(62.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark1", Vector2(0.f, 0.f), Vector2(62.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark1", Vector2(0.f, 0.f), Vector2(62.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark1", Vector2(0.f, 0.f), Vector2(62.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSwordSpark1");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 위쪽1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedUp1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingUp010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedUp1", "PlayerBlockedUp1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedUp1", Vector2(0.f, 0.f), Vector2(24.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedUp1", Vector2(0.f, 0.f), Vector2(24.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedUp1", Vector2(0.f, 0.f), Vector2(24.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedUp1");
        Sequence->AddFramePivot(0.6f, 0.f);
        Sequence->AddFramePivot(0.6f, 0.f);
        Sequence->AddFramePivot(0.6f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 위쪽2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedUp2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingUp020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedUp2", "PlayerBlockedUp2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedUp2", Vector2(0.f, 0.f), Vector2(24.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedUp2", Vector2(0.f, 0.f), Vector2(24.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedUp2", Vector2(0.f, 0.f), Vector2(24.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedUp2");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 왼쪽 위1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedLeftUp1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingLeftUp010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedLeftUp1", "PlayerBlockedLeftUp1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeftUp1", Vector2(0.f, 0.f), Vector2(24.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeftUp1", Vector2(0.f, 0.f), Vector2(24.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeftUp1", Vector2(0.f, 0.f), Vector2(24.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedLeftUp1");
        Sequence->AddFramePivot(0.4f, 0.f);
        Sequence->AddFramePivot(0.4f, 0.f);
        Sequence->AddFramePivot(0.4f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 아래쪽1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedDown1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingDown010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedDown1", "PlayerBlockedDown1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedDown1", Vector2(0.f, 0.f), Vector2(26.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedDown1", Vector2(0.f, 0.f), Vector2(26.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedDown1", Vector2(0.f, 0.f), Vector2(26.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedDown1");
        Sequence->AddFramePivot(0.4f, 0.f);
        Sequence->AddFramePivot(0.4f, 0.f);
        Sequence->AddFramePivot(0.4f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 아래쪽2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedDown2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingDown020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedDown2", "PlayerBlockedDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedDown2", Vector2(0.f, 0.f), Vector2(27.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedDown2", Vector2(0.f, 0.f), Vector2(27.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedDown2", Vector2(0.f, 0.f), Vector2(27.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedDown2");
        Sequence->AddFramePivot(0.35f, 0.f);
        Sequence->AddFramePivot(0.35f, 0.f);
        Sequence->AddFramePivot(0.35f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 오른쪽 아래1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedRightDown1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingRightDown010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedRightDown1", "PlayerBlockedRightDown1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRightDown1", Vector2(0.f, 0.f), Vector2(26.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRightDown1", Vector2(0.f, 0.f), Vector2(26.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRightDown1", Vector2(0.f, 0.f), Vector2(26.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedRightDown1");
        Sequence->AddFramePivot(0.6f, 0.f);
        Sequence->AddFramePivot(0.6f, 0.f);
        Sequence->AddFramePivot(0.6f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 왼쪽1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedLeft1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingLeft010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedLeft1", "PlayerBlockedLeft1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeft1", Vector2(0.f, 0.f), Vector2(14.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeft1", Vector2(0.f, 0.f), Vector2(14.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeft1", Vector2(0.f, 0.f), Vector2(14.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedLeft1");
        Sequence->AddFramePivot(0.55f, 0.f);
        Sequence->AddFramePivot(0.55f, 0.f);
        Sequence->AddFramePivot(0.55f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 왼쪽2 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedLeft2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingLeft020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedLeft2", "PlayerBlockedLeft2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeft2", Vector2(0.f, 0.f), Vector2(15.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeft2", Vector2(0.f, 0.f), Vector2(15.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedLeft2", Vector2(0.f, 0.f), Vector2(15.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedLeft2");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 오른쪽1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedRight1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingRight010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedRight1", "PlayerBlockedRight1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRight1", Vector2(0.f, 0.f), Vector2(14.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRight1", Vector2(0.f, 0.f), Vector2(14.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRight1", Vector2(0.f, 0.f), Vector2(14.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedRight1");
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.45f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 성공 오른쪽2 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedRight2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Block/ChehulisBlockingRight020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockedRight2", "PlayerBlockedRight2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRight2", Vector2(0.f, 0.f), Vector2(15.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRight2", Vector2(0.f, 0.f), Vector2(15.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockedRight2", Vector2(0.f, 0.f), Vector2(15.f, 35.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockedRight2");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 기본 타격 이펙트 2 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSwordSpark2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/SwordSpark/2DEffect_SwordSpark020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSwordSpark2", "PlayerSwordSpark2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(67.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(67.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(67.f, 8.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark2", Vector2(0.f, 0.f), Vector2(67.f, 8.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSwordSpark2");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 1.8f);
        Sequence->AddFramePivot(0.5f, 1.8f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 써클 이펙트   
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockCircle"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Block/2DEffect_BlockSmallEffectCircle0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockCircle", "PlayerBlockCircle", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockCircle", Vector2(0.f, 0.f), Vector2(3.f, 3.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockCircle", Vector2(0.f, 0.f), Vector2(7.f, 7.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockCircle", Vector2(0.f, 0.f), Vector2(15.f, 15.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockCircle", Vector2(0.f, 0.f), Vector2(21.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockCircle", Vector2(0.f, 0.f), Vector2(21.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockCircle", Vector2(0.f, 0.f), Vector2(21.f, 21.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockCircle");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 가드 라이트 이펙트   
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockLight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Block/2DEffect_BlockSmallEffectLight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerBlockLight", "PlayerBlockLight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLight", Vector2(0.f, 0.f), Vector2(25.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLight", Vector2(0.f, 0.f), Vector2(27.f, 23.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLight", Vector2(0.f, 0.f), Vector2(27.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLight", Vector2(0.f, 0.f), Vector2(30.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerBlockLight", Vector2(0.f, 0.f), Vector2(30.f, 14.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerBlockLight");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 기본 타격 이펙트 2 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSwordSpark3"))
    {
        vecFileName.clear();

        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/SwordSpark/2DEffect_SwordSpark0201.png"));

            vecFileName.push_back(FileName);
        }

        for (int i = 6; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/SwordSpark/2DEffect_SwordSpark020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSwordSpark3", "PlayerSwordSpark3", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSwordSpark3", Vector2(0.f, 0.f), Vector2(64.f, 40.f));
        

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSwordSpark3");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 저스트가드 써클 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerJustGuardCircle"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/JustGuard/UI_JustGuardEffect%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 0)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerJustGuardCircle", "PlayerJustGuardCircle", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerJustGuardCircle", Vector2(0.f, 0.f), Vector2(24.f, 24.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerJustGuardCircle");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 카운터어택 왼쪽 (왼쪽 위)   
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerCounterLeft", "PlayerCounterLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(45.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(34.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(34.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(34.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(34.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(34.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(27.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(27.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterLeft");
        Sequence->AddFramePivot(0.355f, 0.f);
        Sequence->AddFramePivot(0.147f, 0.f);
        Sequence->AddFramePivot(0.147f, 0.f);
        Sequence->AddFramePivot(0.147f, 0.f);
        Sequence->AddFramePivot(0.147f, 0.f);
        Sequence->AddFramePivot(0.147f, 0.f);
        Sequence->AddFramePivot(0.407f, 0.f);
        Sequence->AddFramePivot(0.407f, 0.f);
        Sequence->AddFramePivot(0.413f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 카운터어택 위 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterUp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashUp0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerCounterUp", "PlayerCounterUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(13.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(13.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(55.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(55.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(55.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(55.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(35.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(35.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterUp", Vector2(0.f, 0.f), Vector2(35.f, 29.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterUp");
        Sequence->AddFramePivot(0.384f, 0.182f);
        Sequence->AddFramePivot(0.384f, 0.182f);
        Sequence->AddFramePivot(0.109f, 0.025f);
        Sequence->AddFramePivot(0.109f, 0.025f);
        Sequence->AddFramePivot(0.109f, 0.025f);
        Sequence->AddFramePivot(0.109f, 0.025f);
        Sequence->AddFramePivot(0.457f, 0.035f);
        Sequence->AddFramePivot(0.457f, 0.035f);
        Sequence->AddFramePivot(0.457f, 0.035f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 카운터어택 오른쪽 (오른쪽 위)   
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerCounterRight", "PlayerCounterRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(20.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(20.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(41.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(41.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(41.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(41.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(43.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(43.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterRight", Vector2(0.f, 0.f), Vector2(43.f, 33.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterRight");
        Sequence->AddFramePivot(0.4f, 0.030f);
        Sequence->AddFramePivot(0.4f, 0.030f);
        Sequence->AddFramePivot(0.829f, 0.031f);
        Sequence->AddFramePivot(0.829f, 0.031f);
        Sequence->AddFramePivot(0.829f, 0.031f);
        Sequence->AddFramePivot(0.829f, 0.031f);
        Sequence->AddFramePivot(0.837f, 0.061f);
        Sequence->AddFramePivot(0.837f, 0.061f);
        Sequence->AddFramePivot(0.837f, 0.061f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 카운터어택 왼쪽 아래  
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterDownLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashBackLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerCounterDownLeft", "PlayerCounterDownLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(23.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownLeft", Vector2(0.f, 0.f), Vector2(26.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterDownLeft");
        Sequence->AddFramePivot(0.347f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        Sequence->AddFramePivot(0.346f, 0.f);
        //Sequence->AddFramePivot(0.659f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 플레이어 카운터어택 오른쪽 아래 (아래)  
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterDownRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashBackRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerCounterDownRight", "PlayerCounterDownRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(20.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(29.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(29.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(29.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(32.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(32.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(29.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(29.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerCounterDownRight", Vector2(0.f, 0.f), Vector2(24.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerCounterDownRight");
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.689f, 0.f);
        Sequence->AddFramePivot(0.689f, 0.f);
        Sequence->AddFramePivot(0.689f, 0.f);
        Sequence->AddFramePivot(0.687f, 0.f);
        Sequence->AddFramePivot(0.687f, 0.f);
        Sequence->AddFramePivot(0.655f, 0.f);
        Sequence->AddFramePivot(0.655f, 0.f);
        Sequence->AddFramePivot(0.583f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 카운터어택 슬래시 이펙트 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("CounterSlash"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Counter/2DEffect_CounterEffect0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("CounterSlash", "CounterSlash", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("CounterSlash", Vector2(0.f, 0.f), Vector2(114.f, 7.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("CounterSlash", Vector2(0.f, 0.f), Vector2(114.f, 7.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("CounterSlash", Vector2(0.f, 0.f), Vector2(114.f, 7.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("CounterSlash", Vector2(0.f, 0.f), Vector2(78.f, 7.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("CounterSlash", Vector2(0.f, 0.f), Vector2(54.f, 5.f)); 

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("CounterSlash");
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.8f, 0.5f);
        Sequence->AddFramePivot(0.9f, 0.5f);
        Sequence->AddFramePivot(1.f, 0.5f);

        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 귀신 베기 준비 왼쪽(왼쪽 위)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyLeft"))
    {
        vecFileName.clear();
        
        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
            TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashLeft01.png"));

        vecFileName.push_back(FileName);
        

        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSlashReadyLeft", "PlayerSlashReadyLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSlashReadyLeft", Vector2(0.f, 0.f), Vector2(45.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyLeft");
        Sequence->AddFramePivot(0.355f, 0.f);

        SAFE_DELETE_ARRAY(vecFileName[0]);
    }

    // 귀신 베기 준비 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyUp"))
    {
        vecFileName.clear();

        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
            TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashUp01.png"));

        vecFileName.push_back(FileName);


        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSlashReadyUp", "PlayerSlashReadyUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSlashReadyUp", Vector2(0.f, 0.f), Vector2(13.f, 44.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyUp");
        Sequence->AddFramePivot(0.384f, 0.182f);

        SAFE_DELETE_ARRAY(vecFileName[0]);
    }

    // 귀신 베기 준비 오른쪽(오른쪽 위)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyRight"))
    {
        vecFileName.clear();

        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
            TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashRight01.png"));

        vecFileName.push_back(FileName);


        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSlashReadyRight", "PlayerSlashReadyRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSlashReadyRight", Vector2(0.f, 0.f), Vector2(20.f, 40.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyRight");
        Sequence->AddFramePivot(0.4f, 0.03f);

        SAFE_DELETE_ARRAY(vecFileName[0]);
    }

    // 귀신 베기 준비 왼쪽 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyLeftDown"))
    {
        vecFileName.clear();

        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
            TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashBackLeft01.png"));

        vecFileName.push_back(FileName);


        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSlashReadyLeftDown", "PlayerSlashReadyLeftDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSlashReadyLeftDown", Vector2(0.f, 0.f), Vector2(23.f, 33.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyLeftDown");
        Sequence->AddFramePivot(0.347f, 0.f);

        SAFE_DELETE_ARRAY(vecFileName[0]);
    }

    // 귀신 베기 준비 오른쪽 아래(아래)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyRightDown"))
    {
        vecFileName.clear();

        TCHAR* FileName = new TCHAR[MAX_PATH];

        memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
            TEXT("Unsouled_Resource_Used/Sprite/Player/Slash/ChehulisSlashBackRight01.png"));

        vecFileName.push_back(FileName);


        CResourceManager::GetInst()->CreateAnimationSequence2D("PlayerSlashReadyRightDown", "PlayerSlashReadyRightDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("PlayerSlashReadyRightDown", Vector2(0.f, 0.f), Vector2(20.f, 38.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("PlayerSlashReadyRightDown");
        Sequence->AddFramePivot(0.45f, 0.f);

        SAFE_DELETE_ARRAY(vecFileName[0]);
    }


    // 귀신베기 슬래시 이펙트 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("GhostSlash"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Counter/ChehulisSlashSwipe0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("GhostSlash", "GhostSlash", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GhostSlash", Vector2(0.f, 0.f), Vector2(156.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GhostSlash", Vector2(0.f, 0.f), Vector2(156.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GhostSlash", Vector2(0.f, 0.f), Vector2(156.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GhostSlash", Vector2(0.f, 0.f), Vector2(156.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GhostSlash", Vector2(0.f, 0.f), Vector2(134.f, 8.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GhostSlash", Vector2(0.f, 0.f), Vector2(86.f, 6.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("GhostSlash", Vector2(0.f, 0.f), Vector2(80.f, 6.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("GhostSlash");
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.6f, 0.5f);
        Sequence->AddFramePivot(0.6f, 0.5f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 혈흔 터질때 아래 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BloodDown"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Blood/2DEffect_BloodDownLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BloodDown", "BloodDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(7.f, 5.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(12.f, 8.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(19.f, 10.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(21.f, 11.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(22.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(22.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(22.f, 11.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(21.f, 10.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodDown", Vector2(0.f, 0.f), Vector2(19.f, 6.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BloodDown");
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 혈흔 터질때 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BloodLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Blood/2DEffect_BloodLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BloodLeft", "BloodLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(6.f, 8.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(15.f, 10.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(18.f, 11.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(17.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(21.f, 15.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(19.f, 16.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(16.f, 16.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(14.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeft", Vector2(0.f, 0.f), Vector2(13.f, 11.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BloodLeft");
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 혈흔 터질때 왼쪽 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BloodLeftDown"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Blood/2DEffect_BloodLeftDown020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BloodLeftDown", "BloodLeftDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftDown", Vector2(0.f, 0.f), Vector2(10.f, 6.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftDown", Vector2(0.f, 0.f), Vector2(20.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftDown", Vector2(0.f, 0.f), Vector2(22.f, 16.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftDown", Vector2(0.f, 0.f), Vector2(23.f, 16.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftDown", Vector2(0.f, 0.f), Vector2(24.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftDown", Vector2(0.f, 0.f), Vector2(24.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftDown", Vector2(0.f, 0.f), Vector2(24.f, 11.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BloodLeftDown");
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 혈흔 터질때 왼쪽 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BloodLeftUp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/Blood/2DEffect_BloodLeftUp020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BloodLeftUp", "BloodLeftUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftUp", Vector2(0.f, 0.f), Vector2(12.f, 11.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftUp", Vector2(0.f, 0.f), Vector2(18.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftUp", Vector2(0.f, 0.f), Vector2(22.f, 22.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftUp", Vector2(0.f, 0.f), Vector2(23.f, 18.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftUp", Vector2(0.f, 0.f), Vector2(23.f, 18.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftUp", Vector2(0.f, 0.f), Vector2(22.f, 16.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BloodLeftUp", Vector2(0.f, 0.f), Vector2(21.f, 15.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BloodLeftUp");
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);
        Sequence->AddFramePivot(0.5, 0.5f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
}

void CDefaultSetting::LoadResourceMonster()
{
    std::vector<const TCHAR*>   vecFileName;

    // 좀비 경계 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAlertRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Alert/Enemy_ZombieAction010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieAlertRight", "ZombieAlertRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAlertRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 경계 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAlertLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Alert/Enemy_ZombieAction_Left010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieAlertLeft", "ZombieAlertLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAlertLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 정지 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieStandRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Stand/Enemy_ZombieStand0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieStandRight", "ZombieStandRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandRight", Vector2(0.f, 0.f), Vector2(21.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandRight", Vector2(0.f, 0.f), Vector2(21.f, 41.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieStandRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    
    // 좀비 정지 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieStandLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Stand/Enemy_ZombieStand_Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieStandLeft", "ZombieStandLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandLeft", Vector2(0.f, 0.f), Vector2(21.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieStandLeft", Vector2(0.f, 0.f), Vector2(21.f, 41.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieStandLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 달리기 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieRunningRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Running/Enemy_ZombieRunning_Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieRunningRight", "ZombieRunningRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningRight", Vector2(0.f, 0.f), Vector2(24.f, 41.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieRunningRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 달리기 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieRunningLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Running/Enemy_ZombieRunning_Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieRunningLeft", "ZombieRunningLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieRunningLeft", Vector2(0.f, 0.f), Vector2(24.f, 41.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieRunningLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 공격 준비 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackReadyRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Attack/Enemy_ZombieSlashReady_Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieAttackReadyRight", "ZombieAttackReadyRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(26.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(30.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(30.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(29.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyRight", Vector2(0.f, 0.f), Vector2(29.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackReadyRight");
        Sequence->AddFramePivot(0.538f, 0.f);
        Sequence->AddFramePivot(0.558f, 0.f);
        Sequence->AddFramePivot(0.566f, 0.f);
        Sequence->AddFramePivot(0.551f, 0.f);
        Sequence->AddFramePivot(0.551f, 0.f);
        Sequence->AddFramePivot(0.551f, 0.f);
        Sequence->AddFramePivot(0.551f, 0.f);
        Sequence->AddFramePivot(0.551f, 0.f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 공격 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Attack/Enemy_ZombieSlash_Right%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 8)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieAttackRight", "ZombieAttackRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(34.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(45.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(64.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackRight", Vector2(0.f, 0.f), Vector2(44.f, 30.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackRight");
        Sequence->AddFramePivot(0.823f, 0.f);
        Sequence->AddFramePivot(0.777f, 0.f);
        Sequence->AddFramePivot(0.562f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);
        Sequence->AddFramePivot(0.431f, 0.f);

        for (int i = 0; i < 18; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 공격 준비 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackReadyLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Attack/Enemy_ZombieSlashReady_Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieAttackReadyLeft", "ZombieAttackReadyLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyLeft", Vector2(0.f, 0.f), Vector2(26.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyLeft", Vector2(0.f, 0.f), Vector2(30.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyLeft", Vector2(0.f, 0.f), Vector2(30.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackReadyLeft", Vector2(0.f, 0.f), Vector2(29.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackReadyLeft");
        Sequence->AddFramePivot(0.462f, 0.f);
        Sequence->AddFramePivot(0.442f, 0.f);
        Sequence->AddFramePivot(0.434f, 0.f);
        Sequence->AddFramePivot(0.449f, 0.f);

        for (int i = 0; i < 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }


    // 좀비 공격 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Attack/Enemy_ZombieSlash_Left%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 8)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieAttackLeft", "ZombieAttackLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(34.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(45.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(64.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieAttackLeft", Vector2(0.f, 0.f), Vector2(44.f, 30.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieAttackLeft");
        Sequence->AddFramePivot(0.177f, 0.f);
        Sequence->AddFramePivot(0.223f, 0.f);
        Sequence->AddFramePivot(0.438f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);
        Sequence->AddFramePivot(0.569f, 0.f);

        for (int i = 0; i < 18; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 히트 by 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieHitByRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Hit/Enemy_ZombieHitby_Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieHitByRight", "ZombieHitByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(26.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(25.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByRight", Vector2(0.f, 0.f), Vector2(20.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieHitByRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, -0.4f);
        Sequence->AddFramePivot(0.5f, -0.2f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 히트 by 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieHitByLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Hit/Enemy_ZombieHitby_Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieHitByLeft", "ZombieHitByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(26.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(25.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(20.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieHitByLeft", Vector2(0.f, 0.f), Vector2(20.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieHitByLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, -0.4f);
        Sequence->AddFramePivot(0.5f, -0.2f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 사망 by 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieKilledByRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Killed/Enemy_ZombieKilled_Right0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieKilledByRight", "ZombieKilledByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByRight", Vector2(0.f, 0.f), Vector2(30.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByRight", Vector2(0.f, 0.f), Vector2(39.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByRight", Vector2(0.f, 0.f), Vector2(44.f, 16.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByRight", Vector2(0.f, 0.f), Vector2(39.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByRight", Vector2(0.f, 0.f), Vector2(44.f, 16.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieKilledByRight");
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);

        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 사망 by 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieKilledByLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Killed/Enemy_ZombieKilled_Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieKilledByLeft", "ZombieKilledByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByLeft", Vector2(0.f, 0.f), Vector2(30.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByLeft", Vector2(0.f, 0.f), Vector2(39.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByLeft", Vector2(0.f, 0.f), Vector2(44.f, 16.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByLeft", Vector2(0.f, 0.f), Vector2(39.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieKilledByLeft", Vector2(0.f, 0.f), Vector2(44.f, 16.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieKilledByLeft");
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);

        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    
    // 좀비 한방 사망 by 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieOneKilledByRight"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Killed/Enemy_ZombieKilled0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieOneKilledByRight", "ZombieOneKilledByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(20.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(22.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(24.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByRight", Vector2(0.f, 0.f), Vector2(27.f, 7.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieOneKilledByRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.2f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 한방 사망 by 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieOneKilledByLeft"))
    {
        vecFileName.clear();
        for (int i = 0; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Killed/Enemy_ZombieOneKilled_Left0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieOneKilledByLeft", "ZombieOneKilledByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(20.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(22.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(23.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(24.f, 12.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieOneKilledByLeft", Vector2(0.f, 0.f), Vector2(27.f, 7.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieOneKilledByLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.8f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드준비 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardLeft", "ZombieGuardLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardLeft", Vector2(0.f, 0.f), Vector2(23.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardLeft", Vector2(0.f, 0.f), Vector2(23.f, 37.f));
        
        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardLeft");
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.45f, 0.f);
        
        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드준비 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardRight", "ZombieGuardRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardRight", Vector2(0.f, 0.f), Vector2(23.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardRight", Vector2(0.f, 0.f), Vector2(23.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardRight");
        Sequence->AddFramePivot(0.55f, 0.f);
        Sequence->AddFramePivot(0.55f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드준비 위쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardUp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockUp0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardUp", "ZombieGuardUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardUp");
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.3f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드준비 왼쪽 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardLeftUp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockLeftUp0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardLeftUp", "ZombieGuardLeftUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardLeftUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardLeftUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardLeftUp");
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.7f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 왼쪽 1 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeft1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedLeft010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockLeft1", "ZombieBlockLeft1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeft1", Vector2(0.f, 0.f), Vector2(20.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeft1", Vector2(0.f, 0.f), Vector2(20.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeft1");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 왼쪽 2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeft2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedLeft020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockLeft2", "ZombieBlockLeft2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeft2", Vector2(0.f, 0.f), Vector2(21.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeft2", Vector2(0.f, 0.f), Vector2(21.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeft2");
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.45f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 오른쪽 1
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockRight1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedRight010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockRight1", "ZombieBlockRight1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockRight1", Vector2(0.f, 0.f), Vector2(20.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockRight1", Vector2(0.f, 0.f), Vector2(20.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockRight1");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 오른쪽 2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockRight2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedRight020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockRight2", "ZombieBlockRight2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockRight2", Vector2(0.f, 0.f), Vector2(21.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockRight2", Vector2(0.f, 0.f), Vector2(21.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockRight2");
        Sequence->AddFramePivot(0.55f, 0.f);
        Sequence->AddFramePivot(0.55f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 위쪽 1
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockUp1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedUp010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockUp1", "ZombieBlockUp1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockUp1", Vector2(0.f, 0.f), Vector2(21.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockUp1", Vector2(0.f, 0.f), Vector2(20.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockUp1");
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.3f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 위쪽 2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockUp2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedUp020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockUp2", "ZombieBlockUp2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockUp2", Vector2(0.f, 0.f), Vector2(24.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockUp2", Vector2(0.f, 0.f), Vector2(24.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockUp2");
        Sequence->AddFramePivot(0.35f, 0.f);
        Sequence->AddFramePivot(0.35f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 왼쪽 위 1
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeftUp1"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedLeftUp010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockLeftUp1", "ZombieBlockLeftUp1", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeftUp1", Vector2(0.f, 0.f), Vector2(21.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeftUp1", Vector2(0.f, 0.f), Vector2(20.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeftUp1");
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.7f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드성공 왼쪽 위 2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeftUp2"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Block/Enemy_ZombieBlockedLeftUp020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieBlockLeftUp2", "ZombieBlockLeftUp2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeftUp2", Vector2(0.f, 0.f), Vector2(24.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieBlockLeftUp2", Vector2(0.f, 0.f), Vector2(24.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieBlockLeftUp2");
        Sequence->AddFramePivot(0.65f, 0.f);
        Sequence->AddFramePivot(0.65f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 회피 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieDashRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Dash/Enemy_ZombieAction020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieDashRight", "ZombieDashRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashRight", Vector2(0.f, 0.f), Vector2(26.f, 26.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieDashRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 회피 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieDashLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/Dash/Enemy_ZombieAction_Left020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieDashLeft", "ZombieDashLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieDashLeft", Vector2(0.f, 0.f), Vector2(26.f, 26.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieDashLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드브레이크 by 오른쪽 (오른쪽 아래. 아래)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/BlockBreak/Enemy_ZombieBlockBreakUp0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardBreakRight", "ZombieGuardBreakRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakRight", Vector2(0.f, 0.f), Vector2(40.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakRight", Vector2(0.f, 0.f), Vector2(35.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakRight", Vector2(0.f, 0.f), Vector2(35.f, 40.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakRight");
        Sequence->AddFramePivot(0.75f, 0.f);
        Sequence->AddFramePivot(0.714f, 0.f);
        Sequence->AddFramePivot(0.714f, 0.f);
     
        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드브레이크 by 왼쪽 (왼쪽 아래)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/BlockBreak/Enemy_ZombieBlockBreakUp020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardBreakLeft", "ZombieGuardBreakLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakLeft", Vector2(0.f, 0.f), Vector2(40.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakLeft", Vector2(0.f, 0.f), Vector2(35.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakLeft", Vector2(0.f, 0.f), Vector2(35.f, 40.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakLeft");
        Sequence->AddFramePivot(0.25f, 0.f);
        Sequence->AddFramePivot(0.286f, 0.f);
        Sequence->AddFramePivot(0.286f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드브레이크 by 왼쪽위 (위)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakLeftUp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/BlockBreak/Enemy_ZombieBlockBreak0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardBreakLeftUp", "ZombieGuardBreakLeftUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakLeftUp", Vector2(0.f, 0.f), Vector2(29.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakLeftUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakLeftUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakLeftUp");
        Sequence->AddFramePivot(0.344f, 0.f);
        Sequence->AddFramePivot(0.4f, 0.f);
        Sequence->AddFramePivot(0.4f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 좀비 가드브레이크 by 오른쪽 위
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakRightUp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 3; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Zombie/BlockBreak/Enemy_ZombieBlockBreak020%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("ZombieGuardBreakRightUp", "ZombieGuardBreakRightUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakRightUp", Vector2(0.f, 0.f), Vector2(29.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakRightUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("ZombieGuardBreakRightUp", Vector2(0.f, 0.f), Vector2(25.f, 37.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("ZombieGuardBreakRightUp");
        Sequence->AddFramePivot(0.656f, 0.f);
        Sequence->AddFramePivot(0.6f, 0.f);
        Sequence->AddFramePivot(0.6f, 0.f);

        for (int i = 0; i < 3; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    
    // 암살자 경계 왼쪽 1
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertLeft"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); 
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Alert/Enemy_AssassinAction01%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 8)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinAlertLeft", "AssassinAlertLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(22.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(22.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 26.f)); //
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(21.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(22.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(22.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft", Vector2(0.f, 0.f), Vector2(23.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 18; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 경계 오른쪽 1
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertRight"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Alert/Enemy_AssassinActionRight01%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 8)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinAlertRight", "AssassinAlertRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(22.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(22.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 26.f)); //
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(21.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(22.f, 29.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(22.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight", Vector2(0.f, 0.f), Vector2(23.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 18; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 경계 왼쪽 2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertLeft2"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Alert/Enemy_AssassinAction02%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 4)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinAlertLeft2", "AssassinAlertLeft2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(20.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(20.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(20.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(20.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(20.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(20.f, 32.f)); //
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(20.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertLeft2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertLeft2");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 14; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 경계 오른쪽 2
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertRight2"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Alert/Enemy_AssassinActionRight02%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 4)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinAlertRight2", "AssassinAlertRight2", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(20.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(20.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(20.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(20.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(20.f, 33.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(20.f, 32.f)); //
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(20.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAlertRight2", Vector2(0.f, 0.f), Vector2(23.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAlertRight2");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 14; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 정지 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinStandLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Stand/Enemy_AssassinStand0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinStandLeft", "AssassinStandLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandLeft", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandLeft", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandLeft", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandLeft", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandLeft", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandLeft", Vector2(0.f, 0.f), Vector2(23.f, 34.f));


        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinStandLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 정지 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinStandRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Stand/Enemy_AssassinStandRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinStandRight", "AssassinStandRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandRight", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandRight", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandRight", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandRight", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandRight", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinStandRight", Vector2(0.f, 0.f), Vector2(23.f, 34.f));


        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinStandRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 달리기 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinRunningLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Running/Enemy_AssassinRunning0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinRunningLeft", "AssassinRunningLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningLeft", Vector2(0.f, 0.f), Vector2(31.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningLeft", Vector2(0.f, 0.f), Vector2(31.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningLeft", Vector2(0.f, 0.f), Vector2(33.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningLeft", Vector2(0.f, 0.f), Vector2(30.f, 40.f));
        //CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningLeft", Vector2(0.f, 0.f), Vector2(33.f, 38.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinRunningLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.05f);
        //Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 달리기 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinRunningRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Running/Enemy_AssassinRunningRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinRunningRight", "AssassinRunningRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningRight", Vector2(0.f, 0.f), Vector2(31.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningRight", Vector2(0.f, 0.f), Vector2(31.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningRight", Vector2(0.f, 0.f), Vector2(33.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinRunningRight", Vector2(0.f, 0.f), Vector2(30.f, 40.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinRunningRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.55f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.05f);

        for (int i = 0; i < 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 공격 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAttackLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Attack/Enemy_AssassinAttack010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinAttackLeft", "AssassinAttackLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(30.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(32.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(32.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(55.f, 64.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(55.f, 63.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(55.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(51.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(34.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackLeft", Vector2(0.f, 0.f), Vector2(34.f, 45.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAttackLeft");
        Sequence->AddFramePivot(0.38f, 0.f);
        Sequence->AddFramePivot(0.343f, 0.f);
        Sequence->AddFramePivot(0.343f, 0.f);
        Sequence->AddFramePivot(0.509f, 0.157f);
        Sequence->AddFramePivot(0.509f, 0.159f);
        Sequence->AddFramePivot(0.509f, 0.186f);
        Sequence->AddFramePivot(0.470f, 0.223f);
        Sequence->AddFramePivot(0.205f, 0.223f);
        Sequence->AddFramePivot(0.205f, 0.223f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 공격 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAttackRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Attack/Enemy_AssassinAttackRight010%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinAttackRight", "AssassinAttackRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(30.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(32.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(32.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(55.f, 64.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(55.f, 63.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(55.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(51.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(34.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinAttackRight", Vector2(0.f, 0.f), Vector2(34.f, 45.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinAttackRight");
        Sequence->AddFramePivot(0.62f, 0.f);
        Sequence->AddFramePivot(0.657f, 0.f);
        Sequence->AddFramePivot(0.657f, 0.f);
        Sequence->AddFramePivot(0.491f, 0.157f);
        Sequence->AddFramePivot(0.491f, 0.159f);
        Sequence->AddFramePivot(0.491f, 0.186f);
        Sequence->AddFramePivot(0.530f, 0.223f);
        Sequence->AddFramePivot(0.795f, 0.223f);
        Sequence->AddFramePivot(0.795f, 0.223f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 히트 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinHitLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Hit/Enemy_AssassinHitby0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinHitLeft", "AssassinHitLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitLeft", Vector2(0.f, 0.f), Vector2(25.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitLeft", Vector2(0.f, 0.f), Vector2(24.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitLeft", Vector2(0.f, 0.f), Vector2(23.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitLeft", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitLeft", Vector2(0.f, 0.f), Vector2(21.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitLeft", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitLeft", Vector2(0.f, 0.f), Vector2(21.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinHitLeft");
        Sequence->AddFramePivot(0.5f, -0.15f);
        Sequence->AddFramePivot(0.5f, -0.075f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 히트 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinHitRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Hit/Enemy_AssassinHitbyRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinHitRight", "AssassinHitRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitRight", Vector2(0.f, 0.f), Vector2(25.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitRight", Vector2(0.f, 0.f), Vector2(24.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitRight", Vector2(0.f, 0.f), Vector2(23.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitRight", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitRight", Vector2(0.f, 0.f), Vector2(21.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitRight", Vector2(0.f, 0.f), Vector2(22.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinHitRight", Vector2(0.f, 0.f), Vector2(21.f, 31.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinHitRight");
        Sequence->AddFramePivot(0.5f, -0.15f);
        Sequence->AddFramePivot(0.5f, -0.075f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }


    // 암살자 대쉬 아래 (왼쪽 아래)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashDown"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Dash/Enemy_AssassinEvadeDown%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 0)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinDashDown", "AssassinDashDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(19.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(18.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(21.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(21.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(24.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(17.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(18.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(24.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashDown", Vector2(0.f, 0.f), Vector2(24.f, 40.f)); //
     

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashDown");
        Sequence->AddFramePivot(0.578f, 0.f);
        Sequence->AddFramePivot(0.521f, 0.f);
        Sequence->AddFramePivot(0.833f, 0.f);
        Sequence->AddFramePivot(0.523f, 0.f); 
        Sequence->AddFramePivot(0.523f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.647f, 0.f);
        Sequence->AddFramePivot(0.766f, 0.f);
        Sequence->AddFramePivot(0.708f, 0.f);
        Sequence->AddFramePivot(0.708f, 0.f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 대쉬 오른쪽 아래
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashRightDown"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Dash/Enemy_AssassinEvadeDownRight%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 0)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinDashRightDown", "AssassinDashRightDown", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(19.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(18.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(21.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(21.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(24.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(17.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(18.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(24.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashRightDown", Vector2(0.f, 0.f), Vector2(24.f, 40.f)); //


        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashRightDown");
        Sequence->AddFramePivot(0.63f, 0.f);
        Sequence->AddFramePivot(0.65f, 0.f);
        Sequence->AddFramePivot(0.388f, 0.f);
        Sequence->AddFramePivot(0.666f, 0.f);
        Sequence->AddFramePivot(0.714f, 0.f);
        Sequence->AddFramePivot(0.4f, 0.f);
        Sequence->AddFramePivot(0.43f, 0.f);
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.583f, 0.f);
        Sequence->AddFramePivot(0.625f, 0.f);

        for (int i = 0; i < 10; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 대쉬 위 (오른쪽 위,  오른쪽)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashUp"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Dash/Enemy_AssassinEvadeUp%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinDashUp", "AssassinDashUp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(19.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(18.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(23.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(25.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(24.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(22.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(21.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(23.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(27.f, 38.f)); 
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashUp", Vector2(0.f, 0.f), Vector2(23.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashUp");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.348f, 0.05f);
        Sequence->AddFramePivot(0.556f, 0.f);
        Sequence->AddFramePivot(0.592f, 0.f); // 
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.472f, 0.f);
        Sequence->AddFramePivot(0.45f, 0.f);
        Sequence->AddFramePivot(0.386f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 대쉬 왼쪽 (왼쪽 위)
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashLeft"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Dash/Enemy_AssassinEvadeLeft%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinDashLeft", "AssassinDashLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(19.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(23.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(18.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(23.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(25.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(24.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(22.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(21.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(23.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(27.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(23.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinDashLeft", Vector2(0.f, 0.f), Vector2(23.f, 34.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinDashLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.652f, 0.05f);
        Sequence->AddFramePivot(0.444f, 0.f);
        Sequence->AddFramePivot(0.408f, 0.f); // 
        Sequence->AddFramePivot(0.55f, 0.f);
        Sequence->AddFramePivot(0.528f, 0.f);
        Sequence->AddFramePivot(0.55f, 0.f);
        Sequence->AddFramePivot(0.614f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 12; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }


    // 암살자 사망 by 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinKilledByLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Killed/Enemy_AssassinKilled0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinKilledByLeft", "AssassinKilledByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByLeft", Vector2(0.f, 0.f), Vector2(27.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByLeft", Vector2(0.f, 0.f), Vector2(27.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByLeft", Vector2(0.f, 0.f), Vector2(29.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByLeft", Vector2(0.f, 0.f), Vector2(43.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByLeft", Vector2(0.f, 0.f), Vector2(42.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByLeft", Vector2(0.f, 0.f), Vector2(38.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByLeft", Vector2(0.f, 0.f), Vector2(38.f, 17.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinKilledByLeft");
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);
        Sequence->AddFramePivot(0.1f, 0.f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 사망 by 오른쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinKilledByRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/Killed/Enemy_AssassinKilledByRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinKilledByRight", "AssassinKilledByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByRight", Vector2(0.f, 0.f), Vector2(27.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByRight", Vector2(0.f, 0.f), Vector2(27.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByRight", Vector2(0.f, 0.f), Vector2(29.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByRight", Vector2(0.f, 0.f), Vector2(43.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByRight", Vector2(0.f, 0.f), Vector2(42.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByRight", Vector2(0.f, 0.f), Vector2(38.f, 17.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinKilledByRight", Vector2(0.f, 0.f), Vector2(38.f, 17.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinKilledByRight");
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);
        Sequence->AddFramePivot(0.9f, 0.f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 빅킬 by 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinBigKilledByLeft"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/BigKilled/Enemy_AssassinBigKill%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 9)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinBigKilledByLeft", "AssassinBigKilledByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(37.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(37.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(37.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(37.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(37.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(37.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(38.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(40.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(43.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(44.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(46.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(48.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(49.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(47.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(46.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(46.f, 22.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(46.f, 18.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(46.f, 14.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByLeft", Vector2(0.f, 0.f), Vector2(46.f, 14.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinBigKilledByLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.091f);
        Sequence->AddFramePivot(0.5f, 0.091f);
        Sequence->AddFramePivot(0.5f, 0.112f);
        Sequence->AddFramePivot(0.5f, 0.112f);
        Sequence->AddFramePivot(0.52f, 0.114f);
        Sequence->AddFramePivot(0.54f, 0.117f);
        Sequence->AddFramePivot(0.56f, 0.120f);
        Sequence->AddFramePivot(0.59f, 0.129f);
        Sequence->AddFramePivot(0.6f, 0.162f);
        Sequence->AddFramePivot(0.62f, 0.167f);
        Sequence->AddFramePivot(0.64f, 0.167f);
        Sequence->AddFramePivot(0.62f, 0.167f);
        Sequence->AddFramePivot(0.62f, 0.2f);
        Sequence->AddFramePivot(0.62f, 0.228f);
        Sequence->AddFramePivot(0.62f, 0.278f);
        Sequence->AddFramePivot(0.62f, 0.358f);
        Sequence->AddFramePivot(0.62f, 0.358f);

        for (int i = 0; i < 19; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 빅킬 by 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinBigKilledByRight"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/BigKilled/Enemy_AssassinBigKillByRight%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 9)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinBigKilledByRight", "AssassinBigKilledByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(37.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(37.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(37.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(37.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(37.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(37.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(38.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(40.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(43.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(44.f, 39.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(46.f, 31.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(48.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(49.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(47.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(46.f, 25.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(46.f, 22.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(46.f, 18.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(46.f, 14.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinBigKilledByRight", Vector2(0.f, 0.f), Vector2(46.f, 14.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinBigKilledByRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.091f);
        Sequence->AddFramePivot(0.5f, 0.091f);
        Sequence->AddFramePivot(0.5f, 0.112f);
        Sequence->AddFramePivot(0.5f, 0.112f);
        Sequence->AddFramePivot(0.48f, 0.114f);
        Sequence->AddFramePivot(0.46f, 0.117f);
        Sequence->AddFramePivot(0.44f, 0.120f);
        Sequence->AddFramePivot(0.41f, 0.129f);
        Sequence->AddFramePivot(0.4f, 0.162f);
        Sequence->AddFramePivot(0.38f, 0.167f);
        Sequence->AddFramePivot(0.36f, 0.167f);
        Sequence->AddFramePivot(0.38f, 0.167f);
        Sequence->AddFramePivot(0.38f, 0.2f);
        Sequence->AddFramePivot(0.38f, 0.228f);
        Sequence->AddFramePivot(0.38f, 0.278f);
        Sequence->AddFramePivot(0.38f, 0.358f);
        Sequence->AddFramePivot(0.38f, 0.358f);

        for (int i = 0; i < 19; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 가드브레이크 by 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinReflectByLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/BlockBreak/Enemy_AssassinSwordReflect0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinReflectByLeft", "AssassinReflectByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByLeft", Vector2(0.f, 0.f), Vector2(40.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByLeft", Vector2(0.f, 0.f), Vector2(40.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByLeft", Vector2(0.f, 0.f), Vector2(25.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByLeft", Vector2(0.f, 0.f), Vector2(25.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByLeft", Vector2(0.f, 0.f), Vector2(25.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByLeft", Vector2(0.f, 0.f), Vector2(25.f, 42.f));
        

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinReflectByLeft");
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.7f, 0.f);
        Sequence->AddFramePivot(0.52f, 0.f);
        Sequence->AddFramePivot(0.52f, 0.f);
        Sequence->AddFramePivot(0.52f, 0.f);
        Sequence->AddFramePivot(0.52f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 암살자 가드브레이크 by 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("AssassinReflectByRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Assassin/BlockBreak/Enemy_AssassinSwordReflectByRight0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("AssassinReflectByRight", "AssassinReflectByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByRight", Vector2(0.f, 0.f), Vector2(40.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByRight", Vector2(0.f, 0.f), Vector2(40.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByRight", Vector2(0.f, 0.f), Vector2(25.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByRight", Vector2(0.f, 0.f), Vector2(25.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByRight", Vector2(0.f, 0.f), Vector2(25.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("AssassinReflectByRight", Vector2(0.f, 0.f), Vector2(25.f, 42.f));


        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("AssassinReflectByRight");
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.3f, 0.f);
        Sequence->AddFramePivot(0.48f, 0.f);
        Sequence->AddFramePivot(0.48f, 0.f);
        Sequence->AddFramePivot(0.48f, 0.f);
        Sequence->AddFramePivot(0.48f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 달리기 오른쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossRunningRight"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Running/Boss_Niug_Running%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 4)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossRunningRight", "BossRunningRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(51.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(49.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(38.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(39.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(45.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(47.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(54.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(55.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(53.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(44.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(33.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(37.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(45.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningRight", Vector2(0.f, 0.f), Vector2(50.f, 58.f));
        

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossRunningRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 14; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 달리기 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossRunningLeft"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 1; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Running/Boss_Niug_RunningLeft%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 1 && j == 4)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossRunningLeft", "BossRunningLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(51.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(49.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(38.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(39.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(45.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(47.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(54.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(55.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(53.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(44.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(33.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(37.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(45.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRunningLeft", Vector2(0.f, 0.f), Vector2(50.f, 58.f));


        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossRunningLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 14; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 사망 by 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossKilledByRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Killed/Boss_Niug_KilledNormal0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossKilledByRight", "BossKilledByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(66.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(66.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(61.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(61.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(54.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(54.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(55.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(55.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByRight", Vector2(0.f, 0.f), Vector2(43.f, 39.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossKilledByRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 사망 by 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossKilledByLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Killed/Boss_Niug_KilledNormalByLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossKilledByLeft", "BossKilledByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(66.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(66.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(61.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(61.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(54.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(54.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(55.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(55.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossKilledByLeft", Vector2(0.f, 0.f), Vector2(43.f, 39.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossKilledByLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 히트 By 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossHitByLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Hit/Boss_Niug_HitbyLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossHitByLeft", "BossHitByLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(52.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(52.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(52.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(47.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(46.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(44.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(49.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(48.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByLeft", Vector2(0.f, 0.f), Vector2(48.f, 47.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossHitByLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 히트 By 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossHitByRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Hit/Boss_Niug_Hitby0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossHitByRight", "BossHitByRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(52.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(52.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(52.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(47.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(46.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(44.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(49.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(48.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossHitByRight", Vector2(0.f, 0.f), Vector2(48.f, 47.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossHitByRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 가드 준비 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossGuardRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Guard/Boss_Niug_EnduranceOfIsno0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossGuardRight", "BossGuardRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardRight", Vector2(0.f, 0.f), Vector2(43.f, 59.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardRight", Vector2(0.f, 0.f), Vector2(45.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardRight", Vector2(0.f, 0.f), Vector2(44.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardRight", Vector2(0.f, 0.f), Vector2(44.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardRight", Vector2(0.f, 0.f), Vector2(47.f, 47.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossGuardRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
 
        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 가드 준비 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossGuardLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Guard/Boss_Niug_EnduranceOfIsnoLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossGuardLeft", "BossGuardLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardLeft", Vector2(0.f, 0.f), Vector2(43.f, 59.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardLeft", Vector2(0.f, 0.f), Vector2(45.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardLeft", Vector2(0.f, 0.f), Vector2(44.f, 53.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardLeft", Vector2(0.f, 0.f), Vector2(44.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossGuardLeft", Vector2(0.f, 0.f), Vector2(47.f, 47.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossGuardLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 가드 성공 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Block/Boss_Niug_BlockedLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossBlockLeft", "BossBlockLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockLeft", Vector2(0.f, 0.f), Vector2(46.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockLeft", Vector2(0.f, 0.f), Vector2(45.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockLeft", Vector2(0.f, 0.f), Vector2(45.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockLeft", Vector2(0.f, 0.f), Vector2(47.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockLeft", Vector2(0.f, 0.f), Vector2(46.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockLeft", Vector2(0.f, 0.f), Vector2(46.f, 49.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 가드 성공 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Block/Boss_Niug_Blocked0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossBlockRight", "BossBlockRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockRight", Vector2(0.f, 0.f), Vector2(46.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockRight", Vector2(0.f, 0.f), Vector2(45.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockRight", Vector2(0.f, 0.f), Vector2(45.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockRight", Vector2(0.f, 0.f), Vector2(47.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockRight", Vector2(0.f, 0.f), Vector2(46.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockRight", Vector2(0.f, 0.f), Vector2(46.f, 49.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 가드브레이크 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockBreakLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/BlockBreak/Boss_Niug_BlockBreakLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossBlockBreakLeft", "BossBlockBreakLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockBreakLeft", Vector2(0.f, 0.f), Vector2(56.f, 64.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockBreakLeft", Vector2(0.f, 0.f), Vector2(56.f, 64.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockBreakLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 가드브레이크 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockBreakRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/BlockBreak/Boss_Niug_BlockBreak0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossBlockBreakRight", "BossBlockBreakRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockBreakRight", Vector2(0.f, 0.f), Vector2(56.f, 64.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossBlockBreakRight", Vector2(0.f, 0.f), Vector2(56.f, 64.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossBlockBreakRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 어택-펀치 오른쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackPunchRight"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Punch/Boss_Niug_WheelOfLinot01%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 2 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackPunchRight", "BossAttackPunchRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(46.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(51.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(55.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(61.f, 62.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(46.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(69.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(63.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(43.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(38.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(41.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(32.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(32.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(36.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(36.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(36.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(45.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(66.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(75.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(59.f, 62.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(58.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
 
        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackPunchRight");
        Sequence->AddFramePivot(0.673f, 0.f);
        Sequence->AddFramePivot(0.588f, 0.f);
        Sequence->AddFramePivot(0.636f, 0.f);
        Sequence->AddFramePivot(0.655f, 0.f);
        Sequence->AddFramePivot(0.804f, 0.f);
        Sequence->AddFramePivot(0.521f, 0.f);
        Sequence->AddFramePivot(0.523f, 0.f);
        Sequence->AddFramePivot(0.720f, 0.f);
        Sequence->AddFramePivot(0.473f, 0.f);
        Sequence->AddFramePivot(0.512f, 0.f);
        Sequence->AddFramePivot(0.812f, 0.f);
        Sequence->AddFramePivot(0.875f, 0.f);
        Sequence->AddFramePivot(0.875f, 0.f);
        Sequence->AddFramePivot(0.875f, 0.f);
        Sequence->AddFramePivot(0.875f, 0.f);
        Sequence->AddFramePivot(0.666f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.613f, 0.f);
        Sequence->AddFramePivot(0.745f, 0.f);
        Sequence->AddFramePivot(0.689f, 0.f);
        Sequence->AddFramePivot(0.673f, 0.f);
        Sequence->AddFramePivot(0.653f, 0.f);

        for (int i = 0; i < 22; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
   
    // 보스 어택-펀치 왼쪽 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackPunchLeft"))
    {
        vecFileName.clear();

        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                if (i == 0 && j == 0)
                    j = 1;

                TCHAR* FileName = new TCHAR[MAX_PATH];

                memset(FileName, 0, sizeof(TCHAR) * MAX_PATH);
                wsprintf(FileName,
                    TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Punch/Boss_Niug_WheelOfLinotLeft01%d%d.png"), i, j);

                vecFileName.push_back(FileName);

                if (i == 2 && j == 2)
                    break;
            }
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackPunchLeft", "BossAttackPunchLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(46.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(51.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(55.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(61.f, 62.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(46.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(69.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(63.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(43.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(38.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(41.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(32.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(32.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(36.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(36.f, 57.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(36.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(45.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(66.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(75.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(59.f, 62.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(58.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackPunchLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackPunchLeft");
        Sequence->AddFramePivot(0.327f, 0.f);
        Sequence->AddFramePivot(0.412f, 0.f);
        Sequence->AddFramePivot(0.364f, 0.f);
        Sequence->AddFramePivot(0.345f, 0.f);
        Sequence->AddFramePivot(0.196f, 0.f);
        Sequence->AddFramePivot(0.479f, 0.f);
        Sequence->AddFramePivot(0.477f, 0.f);
        Sequence->AddFramePivot(0.280f, 0.f);
        Sequence->AddFramePivot(0.527f, 0.f);
        Sequence->AddFramePivot(0.488f, 0.f);
        Sequence->AddFramePivot(0.188f, 0.f);
        Sequence->AddFramePivot(0.125f, 0.f);
        Sequence->AddFramePivot(0.125f, 0.f);
        Sequence->AddFramePivot(0.125f, 0.f);
        Sequence->AddFramePivot(0.125f, 0.f);
        Sequence->AddFramePivot(0.334f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.387f, 0.f);
        Sequence->AddFramePivot(0.255f, 0.f);
        Sequence->AddFramePivot(0.311f, 0.f);
        Sequence->AddFramePivot(0.327f, 0.f);
        Sequence->AddFramePivot(0.347f, 0.f);

        for (int i = 0; i < 22; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 스톰프 준비
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackStompReady"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp_Ready/Boss_Niug_RageOfIsno0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackStompReady", "BossAttackStompReady", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStompReady", Vector2(0.f, 0.f), Vector2(57.f, 54.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStompReady", Vector2(0.f, 0.f), Vector2(53.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStompReady", Vector2(0.f, 0.f), Vector2(44.f, 65.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStompReady", Vector2(0.f, 0.f), Vector2(40.f, 70.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStompReady", Vector2(0.f, 0.f), Vector2(40.f, 70.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackStompReady");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 스톰프 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackStomp"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 7; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp/Boss_Niug_RageOfIsno0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackStomp", "BossAttackStomp", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStomp", Vector2(0.f, 0.f), Vector2(50.f, 64.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStomp", Vector2(0.f, 0.f), Vector2(39.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStomp", Vector2(0.f, 0.f), Vector2(37.f, 52.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStomp", Vector2(0.f, 0.f), Vector2(37.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStomp", Vector2(0.f, 0.f), Vector2(37.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStomp", Vector2(0.f, 0.f), Vector2(37.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackStomp", Vector2(0.f, 0.f), Vector2(37.f, 51.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackStomp");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.1f);
        Sequence->AddFramePivot(0.5f, 0.1f);
        Sequence->AddFramePivot(0.5f, 0.1f);
        Sequence->AddFramePivot(0.5f, 0.1f);
        Sequence->AddFramePivot(0.5f, 0.1f);
        Sequence->AddFramePivot(0.5f, 0.1f);

        for (int i = 0; i < 7; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 러쉬 준비 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushReadyRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Rush_Ready/Boss_Niug_BallistaShoulder0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackRushReadyRight", "BossAttackRushReadyRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushReadyRight", Vector2(0.f, 0.f), Vector2(39.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushReadyRight", Vector2(0.f, 0.f), Vector2(39.f, 56.f));
       

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushReadyRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
     
        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 러쉬 준비 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushReadyLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 2; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Rush_Ready/Boss_Niug_BallistaShoulderLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackRushReadyLeft", "BossAttackRushReadyLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushReadyLeft", Vector2(0.f, 0.f), Vector2(39.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushReadyLeft", Vector2(0.f, 0.f), Vector2(39.f, 56.f));


        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushReadyLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 2; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 러쉬 오른쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushRight"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Rush/Boss_Niug_BallistaShoulder0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackRushRight", "BossAttackRushRight", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(48.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushRight", Vector2(0.f, 0.f), Vector2(48.f, 49.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushRight");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 러쉬 왼쪽
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushLeft"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 9; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Rush/Boss_Niug_BallistaShoulderLeft0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAttackRushLeft", "BossAttackRushLeft", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(49.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(48.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAttackRushLeft", Vector2(0.f, 0.f), Vector2(48.f, 49.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAttackRushLeft");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 9; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 등장
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAppear"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 19; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Appear/Boss_Niug_IntroApear%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAppear", "BossAppear", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(43.f, 59.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(45.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(46.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(48.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(49.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(49.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppear", Vector2(0.f, 0.f), Vector2(50.f, 47.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAppear");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 19; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 보스 점프 등장
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossAppearJump"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 20; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Appear/Jump/Boss_Niug_Jump%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossAppearJump", "BossAppearJump", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(59.f, 75.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(59.f, 75.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(59.f, 75.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(59.f, 75.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(59.f, 75.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(59.f, 75.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(52.f, 55.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(41.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(41.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(41.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(41.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(41.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(41.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(41.f, 45.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(40.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(40.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(40.f, 42.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(45.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(55.f, 48.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossAppearJump", Vector2(0.f, 0.f), Vector2(53.f, 49.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossAppearJump");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 20; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 스톰프 써클 이펙트 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossStompCircle"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 6; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp/Effect/Boss_Niug_Ki_Circle0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossStompCircle", "BossStompCircle", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompCircle", Vector2(0.f, 0.f), Vector2(73.f, 73.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompCircle", Vector2(0.f, 0.f), Vector2(80.f, 80.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompCircle", Vector2(0.f, 0.f), Vector2(50.f, 50.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompCircle", Vector2(0.f, 0.f), Vector2(39.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompCircle", Vector2(0.f, 0.f), Vector2(13.f, 13.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompCircle", Vector2(0.f, 0.f), Vector2(8.f, 8.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossStompCircle");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 6; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 스톰프 더스트 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossStompDust"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 13; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp/Effect/Boss_Niug_RageOfIsno_Dust%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossStompDust", "BossStompDust", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(39.f, 18.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(64.f, 21.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(101.f, 34.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(112.f, 35.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(118.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(122.f, 41.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(126.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(129.f, 40.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(131.f, 37.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(133.f, 36.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(117.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(95.f, 28.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompDust", Vector2(0.f, 0.f), Vector2(2.f, 2.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossStompDust");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 13; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 스톰프 스파크
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossStompSpark"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp/Effect/Boss_Niug_RageOfIsno_Spark0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossStompSpark", "BossStompSpark", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(64.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(82.f, 46.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(93.f, 56.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(103.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(109.f, 61.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(116.f, 63.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(119.f, 68.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompSpark", Vector2(0.f, 0.f), Vector2(5.f, 5.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossStompSpark");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 스톰프 웨이브
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossStompWave"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 5; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp/Effect/Boss_Niug_RageOfIsno_GroundWave0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossStompWave", "BossStompWave", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompWave", Vector2(0.f, 0.f), Vector2(24.f, 51.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompWave", Vector2(0.f, 0.f), Vector2(63.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompWave", Vector2(0.f, 0.f), Vector2(80.f, 32.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompWave", Vector2(0.f, 0.f), Vector2(110.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompWave", Vector2(0.f, 0.f), Vector2(140.f, 22.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossStompWave");
        Sequence->AddFramePivot(0.5f, 0.15f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 5; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }

    // 스톰프 타겟 더스트
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossStompTargetDust"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 13; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp/Target/Boss_Niug_RageOfIsno_Explosion_InnerDust%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossStompTargetDust", "BossStompTargetDust", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(16.f, 43.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(35.f, 60.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(40.f, 67.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(45.f, 63.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(53.f, 64.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(56.f, 66.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(58.f, 63.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(60.f, 63.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(62.f, 59.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(67.f, 49.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(56.f, 30.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(46.f, 27.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetDust", Vector2(0.f, 0.f), Vector2(42.f, 28.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossStompTargetDust");
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);
        Sequence->AddFramePivot(0.5f, 0.f);

        for (int i = 0; i < 13; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
    
    // 스톰프 타겟 익스플로젼 
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossStompTargetExplosion"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 4; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Stomp/Target/Boss_Niug_RageOfIsno_Explosion_Ground0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossStompTargetExplosion", "BossStompTargetExplosion", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetExplosion", Vector2(0.f, 0.f), Vector2(34.f, 14.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetExplosion", Vector2(0.f, 0.f), Vector2(64.f, 26.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetExplosion", Vector2(0.f, 0.f), Vector2(102.f, 38.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossStompTargetExplosion", Vector2(0.f, 0.f), Vector2(144.f, 60.f)); 

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossStompTargetExplosion");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 4; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
   
    // 러쉬 소닉붐
    if (!CResourceManager::GetInst()->FindAnimationSequence2D("BossRushSonicBoom"))
    {
        vecFileName.clear();
        for (int i = 1; i <= 8; ++i)
        {
            TCHAR* FileName = new TCHAR[MAX_PATH];

            memset(FileName, 0, sizeof(TCHAR) * MAX_PATH); wsprintf(FileName,
                TEXT("Unsouled_Resource_Used/Sprite/Monster/Boss/Attack_Rush/Effect/Boss_Niug_Effect_SonicBoom0%d.png"), i);

            vecFileName.push_back(FileName);
        }

        CResourceManager::GetInst()->CreateAnimationSequence2D("BossRushSonicBoom", "BossRushSonicBoom", vecFileName);

        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(18.f, 44.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(24.f, 58.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(30.f, 72.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(34.f, 80.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(34.f, 80.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(34.f, 80.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(15.f, 80.f));
        CResourceManager::GetInst()->AddAnimationSequence2DFrame("BossRushSonicBoom", Vector2(0.f, 0.f), Vector2(14.f, 58.f));

        CAnimationSequence2D* Sequence = CResourceManager::GetInst()->FindAnimationSequence2D("BossRushSonicBoom");
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);
        Sequence->AddFramePivot(0.5f, 0.5f);

        for (int i = 0; i < 8; ++i)
        {
            SAFE_DELETE_ARRAY(vecFileName[i]);
        }
    }
}

void CDefaultSetting::SetInput()
{
    // 키 등록

    // 이동
    CInput::GetInst()->AddBindKey("Rotation", VK_RIGHT);
    CInput::GetInst()->AddBindKey("RotationInv", VK_LEFT);
    CInput::GetInst()->AddBindKey("MoveUp", VK_UP);
    CInput::GetInst()->AddBindKey("MoveDown", VK_DOWN);
    // 공격
    CInput::GetInst()->AddBindKey("Fire", 'A');
    // 대쉬
    CInput::GetInst()->AddBindKey("Dash", 'D');
    // 가드 
    CInput::GetInst()->AddBindKey("Guard", 'S');
    // 양날베기
    CInput::GetInst()->AddBindKey("DoubleEdge", 'Q');

    // 귀신베기 
    CInput::GetInst()->AddBindKey("GhostSlash", 'W');

    // 귀신달리기
    CInput::GetInst()->AddBindKey("GhostMove", 'E');

    CInput::GetInst()->AddBindKey("MoveClick", VK_RBUTTON);
}

void CDefaultSetting::SetCollision()
{
    // 충돌 채널 생성 
    CCollisionManager::GetInst()->CreateChannel("Default", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Object", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Player", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("Monster", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterAttack", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->CreateChannel("MonsterCognition", ECollision_Interaction::Collision);
    // 단일 대상 공격 충돌체를 의미한다. 
    CCollisionManager::GetInst()->CreateChannel("Single", ECollision_Interaction::Ignore);
    // 단일 대상 공격 충돌체의 타겟을 의미한다. (Single, PlayerAttack 모두 충돌 가능)
    CCollisionManager::GetInst()->CreateChannel("Target", ECollision_Interaction::Ignore);

    // 충돌 프로파일 생성 
    CCollisionManager::GetInst()->CreateProfile("Default", "Default", true, ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateProfile("Object", "Object", true);
    CCollisionManager::GetInst()->CreateProfile("Player", "Player", true);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", "PlayerAttack", true);
    CCollisionManager::GetInst()->CreateProfile("Monster", "Monster", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterAttack", "MonsterAttack", true);
    CCollisionManager::GetInst()->CreateProfile("MonsterCognition", "MonsterCognition", true);
    CCollisionManager::GetInst()->CreateProfile("Single", "Single", true, ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateProfile("Target", "Target", true, ECollision_Interaction::Ignore);

    // 충돌 상호작용 세팅
    CCollisionManager::GetInst()->SetCollisionInteraction("Single", "Target", ECollision_Interaction::Collision);

    CCollisionManager::GetInst()->SetCollisionInteraction("Target", "Single", ECollision_Interaction::Collision);
    CCollisionManager::GetInst()->SetCollisionInteraction("Target", "PlayerAttack", ECollision_Interaction::Collision);

    CCollisionManager::GetInst()->SetCollisionInteraction("Obejct", "Default", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Obejct", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Obejct", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Obejct", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Obejct", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Obejct", "MonsterCognition", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Default", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Object", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Player", "Player", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Default", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Object", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "MonsterCognition", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("PlayerAttack", "Target", ECollision_Interaction::Collision);

    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Default", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Object", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Monster", "Monster", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Default", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Object", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterAttack", "PlayerAttack", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterCognition", "Default", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterCognition", "Object", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterCognition", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterCognition", "Monster", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterCognition", "MonsterAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("MonsterCognition", "MonsterCognition", ECollision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetCollisionInteraction("Default", "PlayerAttack", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Default", "Object", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Default", "Player", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Default", "Single", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Default", "Target", ECollision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetCollisionInteraction("Default", "Default", ECollision_Interaction::Ignore);
}
