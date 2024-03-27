#include "MainHUD.h"
#include "UI/UIProgressBar.h"
#include "UI/UIImage.h"
#include "UI/UIText.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameObject/Player2D.h"

CMainHUD::CMainHUD()
{
    m_WindowTypeName = "MainHUD";
}

CMainHUD::CMainHUD(const CMainHUD& Window) :
    CUIWindow(Window)
{
}

CMainHUD::~CMainHUD()
{
}

void CMainHUD::OnScreenEffect(EScreenEffect ScreenEffect)
{
    // ��ũ�� ����Ʈ
    if (ScreenEffect == EScreenEffect::RedHitBox)
    {
        m_ScreenEffect->SetTexture("HitRedBox", TEXT("Unsouled_Resource_Used/Sprite/Game/ScreenEffect/ScreenEffect_HitRedBox.png"));
        m_ScreenEffectDuration = 1.5f;
        m_ScreenEffect->SetOpacity(1.f);
    }
    else
    {
        m_ScreenEffect->SetTexture("WhiteFlash", TEXT("Unsouled_Resource_Used/Sprite/Game/ScreenEffect/ScreenEffect_WhiteFlash.png"));
        m_ScreenEffectDuration = 2.5f;
        m_ScreenEffect->SetOpacity(0.9f);
    }
}

void CMainHUD::StartCutScene(float Time)
{
    // �ƾ��� �ڽ��� �������� �ð� 
    m_CutSceneBoxTime = 1.f;

    // �ƾ��� ���ӵǴ� Ÿ�̸� ���� 
    m_CutSceneDuration = Time;
}

void CMainHUD::AddHitCount()
{
    ++m_HitCountBuffer;
    m_MessageTime = 0.f;
}

void CMainHUD::AddChainCount()
{
    ++m_ChainCountBuffer;
    m_MessageTime = 0.f;
}

void CMainHUD::SetCounterMessage()
{
    m_IsCounter = true;
    m_MessageTime = 0.f;
}

void CMainHUD::SetJustGuardMessage()
{
    m_IsJustGuard = true;
    m_MessageTime = 0.f;
}

void CMainHUD::Start()
{
    CUIWindow::Start();
}

bool CMainHUD::Init()
{
    CUIWindow::Init();

    // ScreenEffect
    m_ScreenEffect = CreateWidget<CUIImage>("ScreenEffect");
    m_ScreenEffect->SetSize(1280.f, 720.f);
    m_ScreenEffect->SetTexture("HitRedBox", TEXT("Unsouled_Resource_Used/Sprite/Game/ScreenEffect/ScreenEffect_HitRedBox.png"));
    m_ScreenEffect->SetOpacity(0.f);

    // CutScene
    m_vecCutSceneBox1 = CreateWidget<CUIImage>("CutSceneBox1");
    m_vecCutSceneBox2 = CreateWidget<CUIImage>("CutSceneBox2");
    m_vecCutSceneBox1->SetSize(1280.f, 80.f); 
    m_vecCutSceneBox2->SetSize(1280.f, 80.f); 
    m_vecCutSceneBox1->SetPos(0.f, -80.f); // 0  
    m_vecCutSceneBox2->SetPos(0.f, 720.f); // 640
    m_vecCutSceneBox1->SetTexture("CutSceneBox1", TEXT("Unsouled_Resource_Used/Sprite/Game/CutScene/CutScene.png"));
    m_vecCutSceneBox2->SetTexture("CutSceneBox1", TEXT("Unsouled_Resource_Used/Sprite/Game/CutScene/CutScene.png"));
    
    // Message
    m_MsgCount = CreateWidget<CUIText>("MsgCount");

    m_MsgCount->SetSize(100.f, 100.f);
    m_MsgCount->SetPos(1065.f, 380.f);

    m_MsgCount->SetFontSize(45.f);
    m_MsgCount->SetText(TEXT("0"));
    m_MsgCount->SetColor(255, 255, 255);
    m_MsgCount->SetTransparency(true);

    m_MsgCount->SetShadowEnable(true);
    m_MsgCount->SetShadowColor(0, 0, 0);
    m_MsgCount->SetShadowTransparency(true);
    m_MsgCount->SetShadowOpacity(1.f);

    m_Message = CreateWidget<CUIImage>("Message");
    m_Message->SetSize(250.f, 80.f);
    m_Message->SetPos(1110.f, 400.f);
    m_Message->SetTexture("Message_Hits", TEXT("Unsouled_Resource_Used/Sprite/UI/Message/Message_Hits.png"));
    
    // Bar Brace
    m_BraceLT = CreateWidget<CUIImage>("BraceLT");
    m_BraceLT->SetSize(6.f, 6.f);
    m_BraceLT->SetPos(20.f, 690.f);
    m_BraceLT->SetTexture("BraceLT",
        TEXT("Unsouled_Resource_Used/Sprite/UI/Gauge/Used/UI_BraceLetfUp.png"));

    m_BraceLB = CreateWidget<CUIImage>("BraceLB");
    m_BraceLB->SetSize(6.f, 6.f);
    m_BraceLB->SetPos(20.f, 640.f);
    m_BraceLB->SetTexture("BraceLB",
        TEXT("Unsouled_Resource_Used/Sprite/UI/Gauge/Used/UI_BraceLetfDown.png"));

    m_BraceRT = CreateWidget<CUIImage>("BraceRT");
    m_BraceRT->SetSize(6.f, 6.f);
    m_BraceRT->SetPos(400.f, 690.f);
    m_BraceRT->SetTexture("BraceRT",
        TEXT("Unsouled_Resource_Used/Sprite/UI/Gauge/Used/UI_BraceRightUp.png"));

    m_BraceRB = CreateWidget<CUIImage>("BraceRB");
    m_BraceRB->SetSize(6.f, 6.f);
    m_BraceRB->SetPos(400.f, 640.f);
    m_BraceRB->SetTexture("BraceRB",
        TEXT("Unsouled_Resource_Used/Sprite/UI/Gauge/Used/UI_BraceRightDown.png"));

    // HP Bar
    m_HPBar = CreateWidget<CUIProgressBar>("HPBar");

    m_HPBar->SetPos(25.f, 661.f);
    m_HPBar->SetSize(375.f, 26.f);

    m_HPBar->SetImageTint(EProgressBarTextureType::Back, 255, 255, 255, 0);
    m_HPBar->SetImageTint(EProgressBarTextureType::Bar, 255, 255, 255, 255);

    m_HPBar->SetOpacity(1.2f);
    
    m_HPBar->SetTexture(EProgressBarTextureType::Bar, "HPBar1",
        TEXT("Unsouled_Resource_Used/Sprite/UI/Gauge/Used/UI_HPBar.png"));

    m_HPBar->SetProgressBarMin(0.f);
    m_HPBar->SetProgressBarMax(100.f);
    m_HPBar->SetValue(70.f);
    m_HPBar->SetBarDir(EProgressBarDir::RightToLeft);

    // STAMINA BAR
    m_STBar = CreateWidget<CUIProgressBar>("STBar");

    m_STBar->SetPos(25.f, 648.f);
    m_STBar->SetSize(375.f, 12.f);

    m_STBar->SetImageTint(EProgressBarTextureType::Back, 173, 173, 173, 180);
    m_STBar->SetImageTint(EProgressBarTextureType::Bar, 255, 255, 255, 255);

    m_STBar->SetOpacity(1.2f);

    m_STBar->SetTexture(EProgressBarTextureType::Bar, "STBar",
        TEXT("Unsouled_Resource_Used/Sprite/UI/Gauge/Used/UI_STBar.png"));

    m_STBar->SetProgressBarMin(0.f);
    m_STBar->SetProgressBarMax(100.f);
    m_STBar->SetValue(70.f);
    m_STBar->SetBarDir(EProgressBarDir::RightToLeft);

    return true;
}

void CMainHUD::Update(float DeltaTime)
{
    CUIWindow::Update(DeltaTime);

    // �޽����� ��µǰ� 1.2�ʰ� ������ 
    if (m_CurrentMessageType != EMessageType::None)
    {
        m_MessageTime += DeltaTime;
        if (m_MessageTime > 1.2f)
        {
            // 1�ʰ� ���̵�ƿ� ���� 
            m_Message->AddOpacity(-1.f * DeltaTime);
            
            if (m_CurrentMessageType != EMessageType::JustGuard && m_CurrentMessageType != EMessageType::Counter)
            {
                m_MsgCount->SetOpacity(m_Message->GetOpacity());
                m_MsgCount->SetShadowOpacity(m_Message->GetOpacity());
            }

            // ī��Ʈ �ʱ�ȭ (�� 2.2��)
            if (m_MessageTime > 2.2f)
            {
                m_CurrentMessageType = EMessageType::None;
                m_HitCount = 0;
                m_ChainCount = 0;
                m_MessageTime = 0.f;
            }

        }
    }

    
    // �÷��̾� hp�� ������ �����Ѵ� 
    if (m_Player)
    {
        m_HPBar->SetValue((m_Player->GetHP() / 10));
        m_STBar->SetValue(m_Player->GetST());
    }
    else
        m_Player = dynamic_cast<CPlayer2D*>(m_Scene->GetSceneInfo()->GetPlayerObject());
    
}

void CMainHUD::PostUpdate(float DeltaTime)
{
    CUIWindow::PostUpdate(DeltaTime);

    // ��ũ�� ����Ʈ
    if (m_ScreenEffect->GetOpacity() > 0.f)
    {
        m_ScreenEffect->AddOpacity(-m_ScreenEffectDuration * DeltaTime);
    }
    else
    {
        m_ScreenEffect->SetOpacity(0.f);
    }


    // �ƾ�
    // ������ �ڽ� ���̰� �ϱ� 
    if (m_CutSceneBoxTime > 0.f && m_CutSceneDuration > 0.f)
    {
        m_CutSceneBoxTime -= DeltaTime;
        m_vecCutSceneBox1->AddPos(0.f, DeltaTime * 80.f);
        m_vecCutSceneBox2->AddPos(0.f, DeltaTime * -80.f);
    }
    // ������ �ڽ� ���ֱ� 
    else if (m_CutSceneBoxTime > 0.f && m_CutSceneDuration == 0.f)
    {
        m_CutSceneBoxTime -= DeltaTime;
        m_vecCutSceneBox1->AddPos(0.f, DeltaTime * -80.f);
        m_vecCutSceneBox2->AddPos(0.f, DeltaTime * 80.f);
    }

    // �ƾ� Ÿ��
    if (m_CutSceneDuration > 0.f)
    {
        m_CutSceneDuration -= DeltaTime;
    }
    else if (m_CutSceneDuration < 0.f)
    {
        m_CutSceneDuration = 0.f;
        m_CutSceneBoxTime = 1.f;
    }

    /************* �޽��� ****************/

    // �޽��� ī��Ʈ�� 0.3�ʸ��� �ѹ��� �����Ѵ�. 
    // �޽��� �ִϸ��̼��� �����̴� �ð��� Ȯ���ϱ� ���� 
    m_CountBufferClearTime += DeltaTime;

    if (m_CountBufferClearTime > 0.2f)
    {
        m_ChangeCount = false;
        // �̰� �ּ� Ǯ�� Ÿ�� �ٲ𶧐� �޽����̵� 
        //m_CurrentMessageType = m_NextMessageType;
        m_NextMessageType = EMessageType::None;

        m_CountBufferClearTime = 0.f;
        m_MsgCount->SetPos(1065.f, 380.f);

        if(m_CurrentMessageType == EMessageType::JustGuard)
            m_Message->SetPos(1000.f, 400.f);
        else if(m_CurrentMessageType == EMessageType::Counter)
            m_Message->SetPos(1050.f, 400.f);
        else
            m_Message->SetPos(1110.f, 400.f);

        m_HitCount += m_HitCountBuffer;

        m_ChainCount += m_ChainCountBuffer;

        // ü��ī��Ʈ�� ��Ʈī��Ʈ �߿� �����ؾ��ϴµ�, �� �� ���������� �ִ� ������
        // �� �� �����Ǿ��ٸ� ��Ʈ�� �켱����
        // �� �� �ݿ����� ���� ���� ���۸� ����� �ʴ´�. 
         
        // ���۰� 0�� �ƴϾ��� ���->������ �־��ٴ� �ǹ�->���� �ؽ�Ʈ ����
        if (m_IsJustGuard)
        {
            m_CurrentMessageType = EMessageType::None;

            // �ִϸ��̼� �� �޽��� �̹����� �ٲ��ֱ� ����
            m_NextMessageType = EMessageType::JustGuard;

            // �� ���� ü�θ޽����� ����ϸ� �ȵǹǷ�
            // ü�� ���۴� ����ش�.
            m_ChainCountBuffer = 0;
        }
        else if (m_IsCounter)
        {
            m_CurrentMessageType = EMessageType::None;

            // �ִϸ��̼� �� �޽��� �̹����� �ٲ��ֱ� ����
            m_NextMessageType = EMessageType::Counter;

            // �� ���� ��Ʈ�޽����� ����ϸ� �ȵǹǷ� 
            // ��Ʈ ���۴� ����ش� 
            m_HitCountBuffer = 0;
        }
        else if (m_HitCountBuffer > 0)
        {
            m_CurrentMessageType = EMessageType::None;

            int _cnt = m_HitCount;
            wchar_t cnt[3];
            _itow_s(_cnt, cnt, 10);

            m_MsgCount->SetText(cnt);

            m_HitCountBuffer = 0;

            // ī��Ʈ ���� �ִϸ��̼� �� �޽��� �̹����� �ٲ��ֱ� ����
            m_ChangeCount = true;
            m_NextMessageType = EMessageType::Hits;

            m_MsgCount->SetColor(255, 255, 255);
        }
        else if (m_ChainCountBuffer > 0)
        {
            m_CurrentMessageType = EMessageType::None;

            int _cnt = m_ChainCount;
            wchar_t cnt[3];
            _itow_s(_cnt, cnt, 10);

            m_MsgCount->SetText(cnt);

            m_ChainCountBuffer = 0;

            // ī��Ʈ ���� �ִϸ��̼� �� �޽��� �̹����� �ٲ��ֱ� ����
            m_ChangeCount = true;
            m_NextMessageType = EMessageType::Chain;

            m_MsgCount->SetColor(255, 255, 0);
        }
    } 

    if (m_NextMessageType == EMessageType::JustGuard)
    {
        m_IsJustGuard = false;

        // �޽����� �����ʿ��� �������� ������. 
        if (m_CountBufferClearTime == 0.f)
        {
            m_Message->SetOpacity(1.f);

            m_MsgCount->SetOpacity(0.f);
            m_MsgCount->SetShadowOpacity(0.f);

            m_Message->SetTexture("Message_JustGuard", TEXT("Unsouled_Resource_Used/Sprite/UI/Message/Message_JustGuard.png"));
           
            m_Message->SetPos(1150.f, 400.f);

            m_CurrentMessageType = m_NextMessageType;
        }

        //if (m_CurrentMessageType != m_NextMessageType)
            m_Message->AddPos(-50 * DeltaTime * 15.f, 0.f);
    }

    if (m_NextMessageType == EMessageType::Counter)
    {
        m_IsCounter = false;

        // �޽����� �����ʿ��� �������� ������. 
        if (m_CountBufferClearTime == 0.f)
        {
            m_Message->SetOpacity(1.f);

            m_MsgCount->SetOpacity(0.f);
            m_MsgCount->SetShadowOpacity(0.f);

            m_Message->SetTexture("Message_Counter", TEXT("Unsouled_Resource_Used/Sprite/UI/Message/Message_Counter.png"));

            m_Message->SetPos(1200.f, 400.f);

            m_CurrentMessageType = m_NextMessageType;
        }

       // if (m_CurrentMessageType != m_NextMessageType)
            m_Message->AddPos(-50 * DeltaTime * 15.f, 0.f);
    }

    // �޽��� ���� �ִϸ��̼� ��� �� �޽����̹��� �ٲ�
    if (m_ChangeCount)
    {
        // ���ڸ� ���ʿ��� ���������� 
        // �޽����� �����ʿ��� �������� ������. 
        if (m_CountBufferClearTime == 0.f)
        {
            if (m_NextMessageType == EMessageType::Hits)
            {
                m_Message->SetOpacity(1.f);

                m_MsgCount->SetOpacity(1.f);
                m_MsgCount->SetShadowOpacity(1.f);
                m_Message->SetTexture("Message_Hits", TEXT("Unsouled_Resource_Used/Sprite/UI/Message/Message_Hits.png"));
            }
            else if (m_NextMessageType == EMessageType::Chain)
            {
                m_Message->SetOpacity(1.f);

                m_MsgCount->SetOpacity(1.f);
                m_MsgCount->SetShadowOpacity(1.f);
                m_Message->SetTexture("Message_Chain", TEXT("Unsouled_Resource_Used/Sprite/UI/Message/Message_Chain.png"));
            }
            
            if (m_CurrentMessageType != m_NextMessageType)
            {
                m_Message->SetPos(1210.f, 400.f);
                m_CurrentMessageType = m_NextMessageType;
            }
           
            m_MsgCount->SetPos(1065.f, 460.f);

            m_CurrentMessageType = m_NextMessageType;
        }

       // if (m_CurrentMessageType != m_NextMessageType)
             m_Message->AddPos(-75 * DeltaTime * 6.66f, 0.f);

        m_MsgCount->AddPos(0.f, -60 * DeltaTime * 6.66f);
    }
}

void CMainHUD::Render()
{
    CUIWindow::Render();
}

CMainHUD* CMainHUD::Clone()
{
    return new CMainHUD(*this);
}

void CMainHUD::Save(FILE* File)
{
    CUIWindow::Save(File);
}

void CMainHUD::Load(FILE* File)
{
    CUIWindow::Load(File);
}
