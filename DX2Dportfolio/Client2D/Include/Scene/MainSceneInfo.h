#pragma once

#include "Scene/SceneInfo.h"

class CMainSceneInfo :
    public CSceneInfo
{
public:
    CMainSceneInfo();
    ~CMainSceneInfo();
private:
    class CMainHUD* m_MainHUD;
    bool m_StartBossFight;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

public:
    virtual void CreateBoss();
    void AddHitCount();
    void AddChainCount();
    void SetJustGuardMessage();
    void SetCounterMessage();
};

