
#include "CameraComponent.h"
#include "../Device.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneInfo.h"
#include "../GameObject/GameObject.h"

CCameraComponent::CCameraComponent()	:
	m_CameraViewDistance(1000.f),
	m_CameraType(ECameraType::Camera2D)
{
	SetTypeID<CCameraComponent>();

	m_ComponentTypeName = "CameraComponent";
}

CCameraComponent::CCameraComponent(const CCameraComponent& component)	:
	CSceneComponent(component)
{
	m_CameraViewDistance = component.m_CameraViewDistance;
	m_matView = component.m_matView;
	m_matProj = component.m_matProj;
	m_CameraType = component.m_CameraType;

	ComputeProjectionMatrix();
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::ComputeProjectionMatrix()
{
	Resolution	RS = CDevice::GetInst()->GetResolution();

	switch (m_CameraType)
	{
	case ECameraType::Camera2D:
		m_matProj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, (float)RS.Width, 0.f,
			(float)RS.Height, 0.f, m_CameraViewDistance);
		break;
	case ECameraType::Camera3D:
		//m_matProj = DirectX::XMMatrixPerspectiveFovLH()
		break;
	case ECameraType::CameraUI:
		m_matProj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, (float)RS.Width, 0.f,
			(float)RS.Height, 0.f, m_CameraViewDistance);
		break;
	}
}

void CCameraComponent::FixCameraPos(float Duration, Vector3 Pos)
{
	if (m_FixDuration > 0.f)
		return;

	m_Fix = true;
	m_FixDuration = Duration;
	m_FixPos = Pos;

	AddWorldPosition(m_FixPos);
}

void CCameraComponent::PatrolCameraPos(Vector3 SrcPos, Vector3 DestPos, float Duration)
{
    if (m_StayDuration > 0.f)
        return;

    m_Patrol = true;
    m_StayDuration = Duration;
    m_PatrolDuration = 3.f;
    m_PatrolSrcPos = SrcPos;
    m_PatrolDestPos = DestPos;

    // �Ÿ� ���� 
    m_PatrolDistance = DestPos - SrcPos;
}

void CCameraComponent::Destroy()
{
	CSceneComponent::Destroy();
}

void CCameraComponent::Start()
{
	CSceneComponent::Start();

	ComputeProjectionMatrix();
}

bool CCameraComponent::Init()
{
	CSceneComponent::Init();

	return true;
}

void CCameraComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CCameraComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	/*
	ī�޶� �佺���̽� ��ȯ : ������� ��� ��ü�� ī�޶� 0, 0, 0���� �̵��ϴ� ��ŭ
	�̵���Ű�� ī�޶� �ٶ󺸴� ����(Z��)�� Z+ ������ �ٶ� �� �ְ� ȸ����Ű�� ��ŭ �̵���
	��� ��ü���� ���� �������� �׸�ŭ ���������ش�.

	�׷��� ī�޶�� ��������� ��ȯ�� �Ͼ ��� ����������� ī�޶��� x, y, z ����
	X : 1, 0, 0
	Y : 0, 1, 0
	Z : 0, 0, 1
	�� �ɰ��̴�.

	ī�޶��� ������ : WX, WY, WZ ���̶�� �Ѵ�.
	WX * ����� = 1, 0, 0
	WY * ����� = 0, 1, 0
	WZ * ����� = 0, 0, 1

	WXX WXY WXZ   11 12 13   1 0 0
	WYX WYY WYZ * 21 22 23 = 0 1 0
	WZX WZY WZZ   31 32 33   0 0 1

	�������� �̿��Ͽ� ������ ����� ������� �����ָ� �׵������ ���´�.
	������� �������� �̿��Ͽ� ������ ����� ������� �ȴٴ� ���̴�.

	�������� �̿��Ͽ� ������ ����� �������̱� ������ ���� �������Ѵ�.
	�̷��� ���� �������ϴ� ���� �̿��Ͽ� ������ ����� ��������̶�� �Ѵ�.

	��������� Ư¡ : ����İ� ��ġ����� ����.
	������� �������� �̿��Ͽ� ������ ����� ��ġ��İ� ���ٴ� �ǹ��̴�.
	WXX WXY WXZ    WXX WYX WZX
	WYX WYY WYZ => WXY WYY WZY
	WZX WZY WZZ    WXZ WYZ WZZ

	ī�޶��� ��ġ : PX, PY, PZ

	�̵����
	1    0   0  0
	0    1   0  0
	0    0   1  0
	-PX -PY -PZ 0

	ȸ�����
	WXX WYX WZX 0
	WXY WYY WZY 0
	WXZ WYZ WZZ 0
	0   0   0   1

	1    0   0  0   WXX WYX WZX 0   WXX   WYX    WZX  0
	0    1   0  0 * WXY WYY WZY 0 = WXY   WYY    WZY  0
	0    0   1  0	WXZ WYZ WZZ 0   WXZ   WYZ    WZZ  0
	-PX -PY -PZ 0	0   0   0   1   -P.WX -P.WY -P.WZ 1
	*/
	if (m_CameraType != ECameraType::CameraUI)
	{
		m_matView.Identity();

		/*
		WXX WXY WXZ 0
		WYX WYY WYZ 0
		WZX WZY WZZ 0
		0   0   0   1

		��ġ
		WXX WYX WZX 0
		WXY WYY WZY 0
		WXZ WYZ WZZ 0
		0   0   0   1
		*/
		for (int i = 0; i < 3; ++i)
		{
			Vector3	Axis = GetWorldAxis((AXIS)i);
			memcpy(&m_matView[i][0], &Axis, sizeof(Vector3));
		}

		m_matView.Transpose();

		Vector3	Pos = GetWorldPos();

		for (int i = 0; i < 3; ++i)
		{
			m_matView[3][i] = -Pos.Dot(GetWorldAxis((AXIS)i));
		}
	}


	// FixCameraPos
	if (m_Fix)
	{
		if (m_FixDuration > 0.f)
		{
			m_FixDuration -= DeltaTime;
		}
		else
        {
			AddWorldPosition(-m_FixPos.x, -m_FixPos.y, -m_FixPos.z);
			m_FixDuration = 0.f;
			m_Fix = false;
		}
	}

    // PatrolCameraPos
    if (m_Patrol)
    {
        // �Ÿ��� ���ϰ� �ӵ��� �����Ѵ�. 
        // �ش� �Ÿ��� 3�ʰ� �̵��� �� �ֵ��� ���� 
        if (m_PatrolDuration > 0.f)
        {
            AddWorldPosition(m_PatrolDistance * (DeltaTime * 0.333));

            m_PatrolDuration -= DeltaTime;

        }
        else
        {
            if (m_StayDuration > 0.f)
            {
                // �̶� ���� ����
                if(m_StayDuration == 5.f)     
                    GetScene()->GetSceneInfo()->CreateBoss();

                m_StayDuration -= DeltaTime;   
            }
            else
            {
                // ĳ������ ���߾ӿ� ī�޶� ���� ����,... 
                Resolution RS = CDevice::GetInst()->GetResolution();
                float Width = (float)RS.Width / 2.f;
                float Height = (float)RS.Height / 2.f;

                m_Patrol = false;
                m_PatrolDuration = 3.f;
                m_PatrolDistance = GetScene()->GetSceneInfo()->GetPlayerObject()->GetWorldPos() - GetWorldPos() - Vector3(Width, Height, 0.f);
            }
        }
    }
    else if (m_PatrolDuration > 0.f)
    {
        AddWorldPosition(m_PatrolDistance * (DeltaTime * 0.333));

        m_PatrolDuration -= DeltaTime;
    }
    else
        m_PatrolDuration = 0.f;

    
}

void CCameraComponent::Render()
{
	CSceneComponent::Render();
}

CCameraComponent* CCameraComponent::Clone() const
{
	return new CCameraComponent(*this);
}

void CCameraComponent::Save(FILE* File)
{
	CSceneComponent::Save(File);

	fwrite(&m_CameraType, sizeof(ECameraType), 1, File);
	fwrite(&m_CameraViewDistance, sizeof(float), 1, File);

	fwrite(&m_matView, sizeof(Matrix), 1, File);
	fwrite(&m_matProj, sizeof(Matrix), 1, File);
}

void CCameraComponent::Load(FILE* File)
{
	CSceneComponent::Load(File);

	fread(&m_CameraType, sizeof(ECameraType), 1, File);
	fread(&m_CameraViewDistance, sizeof(float), 1, File);

	fread(&m_matView, sizeof(Matrix), 1, File);
	fread(&m_matProj, sizeof(Matrix), 1, File);
}
