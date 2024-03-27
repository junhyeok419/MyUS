#pragma once

#include "../EngineInfo.h"

class CSceneInfo
{
	friend class CScene;
	friend class CSceneManager;

protected:
	CSceneInfo();
	CSceneInfo(const CSceneInfo& Info);
	virtual ~CSceneInfo();

protected:
	class CScene* m_Owner;
	CSharedPtr<class CGameObject> m_PlayerObject;
	std::string	m_ClassTypeName;
	std::string	m_PlayerObjectName;

    int m_KillCount;
    bool m_CleanMonster;
protected:
	void SetClassTypeName(const std::string& Name)
	{
		m_ClassTypeName = Name;
	}

public:
	void SetPlayerObject(class CGameObject* Player);
	CGameObject* GetPlayerObject();
	void LoadComplete();

public:
    void AddKillCount()
    {
        ++m_KillCount;
    }
    int GetKillCount() const
    {
        return m_KillCount;
    }
    void CleanMonster()
    {
        m_CleanMonster = true;
    }
    bool IsCleanMonster()
    {
        return m_CleanMonster;
    }
    virtual void CreateBoss()
    {

    }

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CSceneInfo* Clone();
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
	virtual void SceneChangeComplete();
};

