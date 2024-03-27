#pragma once

#include "SceneComponent.h"

class CCameraComponent :
    public CSceneComponent
{
    friend class CCameraManager;
	friend class CGameObject;
	friend class CScene;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& component);
	virtual ~CCameraComponent();

protected:
	ECameraType	m_CameraType;
	Matrix		m_matView;
	Matrix		m_matProj;

	float		m_CameraViewDistance;

	bool		m_Fix;
	float		m_FixDuration;
	Vector3		m_FixPos;

    bool        m_Patrol;
    float       m_StayDuration;   // 머무는시간임 
    float       m_PatrolDuration; // 이동하는 시간 
    Vector3     m_PatrolSrcPos;
    Vector3     m_PatrolDestPos;
    Vector3     m_PatrolDistance;
public:
	const Matrix& GetViewMatrix()	const
	{
		return m_matView;
	}

	const Matrix& GetProjMatrix()	const
	{
		return m_matProj;
	}


public:
	void SetCameraType(ECameraType Type)
	{
		m_CameraType = Type;

		ComputeProjectionMatrix();
	}

	void SetCameraViewDistance(float Distance)
	{
		m_CameraViewDistance = Distance;

		ComputeProjectionMatrix();
	}

	void ComputeProjectionMatrix();

public:
	void FixCameraPos(float Duration, Vector3 Pos);
    // 카메라에 명령 - 패트롤 시작 (원래위치, 목적지, 속도, 머무는시간)
    void PatrolCameraPos(Vector3 SrcPos, Vector3 DestPos, float Duration);
public:
	virtual void Destroy();
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CCameraComponent* Clone()    const;
	virtual void Save(FILE* File);
	virtual void Load(FILE* File);
};

