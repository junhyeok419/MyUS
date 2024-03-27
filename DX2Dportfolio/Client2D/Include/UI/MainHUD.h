#pragma once
#include "UI\UIWindow.h"
#include "UI\UIProgressBar.h"

enum class EScreenEffect
{
	None,
	RedHitBox,
	WhiteFlash,
	End
};

enum class EMessageType
{
    None,
    Hits,
    Chain,
    JustGuard,
    Counter,
    End
};

class CMainHUD :
    public CUIWindow
{
	friend class CSceneViewport;
	friend class CScene;

protected:
	CMainHUD();
	CMainHUD(const CMainHUD& Window);
	virtual ~CMainHUD();

protected:
    // Screen
	CSharedPtr<class CUIImage>	m_ScreenEffect;			// ½ºÅ©¸°¿¡ ³ªÅ¸³ª´Â ÀÌÆåÆ® (·¹µå, È­ÀÌÆ®)
	float						m_ScreenEffectDuration; // ½ºÅ©¸°ÀÌÆåÆ® ¹è¼Ó

    // CutScene
    CSharedPtr<class CUIImage>	m_vecCutSceneBox1;          // ÄÆ¾À ºí·¢ ¹Ú½º1
    CSharedPtr<class CUIImage>	m_vecCutSceneBox2;          // ÄÆ¾À ºí·¢ ¹Ú½º2
    float                       m_CutSceneDuration;         // ÄÆ¾À Áö¼Ó½Ã°£
    float                        m_CutSceneBoxTime;         // ÄÆ¾À ¹Ú½º »ý¼º½Ã°£ 

    // Message
    int                         m_HitCountBuffer = 0;
    int                         m_HitCount = 0;
    float                       m_CountBufferClearTime = 0.f;
    int                         m_ChainCountBuffer = 0;
    int                         m_ChainCount = 0;
    CSharedPtr<class CUIText>   m_MsgCount;
    CSharedPtr<class CUIImage>	m_Message;  
    float                       m_MessageTime = 0.f;
    EMessageType                m_CurrentMessageType;
    EMessageType                m_NextMessageType;
    bool                        m_ChangeCount;
    float                       m_ChangeCountTime = 0.f;
    bool                        m_IsJustGuard;
    bool                        m_IsCounter;

    // HP, STAMINA Bar
    CSharedPtr<class CUIProgressBar>	m_HPBar;
    CSharedPtr<class CUIProgressBar>	m_STBar;

    // BAR Brace
    CSharedPtr<class CUIImage> m_BraceLT;
    CSharedPtr<class CUIImage> m_BraceLB;
    CSharedPtr<class CUIImage> m_BraceRT;
    CSharedPtr<class CUIImage> m_BraceRB;

    // Soul orb

    // Player
    CSharedPtr<class CPlayer2D> m_Player;
public:
	void OnScreenEffect(EScreenEffect ScreenEffect);
    void StartCutScene(float Time);
    //void SetCountText();
    void AddHitCount();
    void AddChainCount();
    void SetCounterMessage();
    void SetJustGuardMessage();
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CMainHUD* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

