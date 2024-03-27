#pragma once

#include "Scene/SceneInfo.h"

class CTestSceneInfo :
    public CSceneInfo
{
public:
    CTestSceneInfo();
    ~CTestSceneInfo();
private:
    class CMainHUD* m_MainHUD;
public:
    virtual bool Init();
};

