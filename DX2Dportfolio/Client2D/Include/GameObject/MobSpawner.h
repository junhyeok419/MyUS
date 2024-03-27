#pragma once
#include "GameObject\GameObject.h"

class CMobSpawner :
    public CGameObject
{
    friend class CScene;

protected:
    CMobSpawner();
    CMobSpawner(const CMobSpawner& Obj);
    virtual ~CMobSpawner();

private:
    CSharedPtr<class CColliderBox2D>	m_SpawnArea;
    int m_SpawnCount;
    int m_PrevKillCount;
    float m_SSibal;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual CMobSpawner* Clone()    const;
public:
    void CreateSpawnArea(Vector2 LT);
private:
    Vector2 GetRandomPosInArea();
};

