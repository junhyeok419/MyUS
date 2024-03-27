#pragma once

#include "EngineSetting.h"

class CDefaultSetting :
    public CEngineSetting
{
public:
    CDefaultSetting();
    virtual ~CDefaultSetting();

public:
    virtual void Init();

private:
    void CreateCDO();
    void LoadSound();
    void LoadResource();
    void LoadResourceMonster();
    void SetInput();
    void SetCollision();
};

