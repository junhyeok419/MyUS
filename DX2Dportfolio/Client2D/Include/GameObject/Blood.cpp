#include "Blood.h"
#include "Resource/Material/Material.h"
#include "Component/Effect.h"
#include "Scene/Scene.h"
#include "Afterimage.h"
#include "BloodMark.h"

CBlood::CBlood()
{
	SetTypeID<CBlood>();

	m_ObjectTypeName = "Blood";
}

CBlood::CBlood(const CBlood& Obj) :
	CGameObject(Obj)
{
}

CBlood::~CBlood()
{
	m_Effect->Destroy();
}

CEffect* CBlood::GetEffect()
{
	return m_Effect;
}

void CBlood::Start()
{
	CGameObject::Start();
}

bool CBlood::Init()
{
	CGameObject::Init();

	m_Effect = CreateComponent<CEffect>("Effect");

	m_Effect->SetPivot(0.5f, 0.5f);
	m_Effect->SetRelativeScale(50.f, 50.f);

	m_MarkCount = 5;

	return true;
}

void CBlood::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CBlood::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	// 방향에 따라 피의 이동 위치를 조정한다. 

	float speed = 250.f;

	switch (m_Dir)
	{
	case EObjectDir::Up:
		AddWorldPosition(Vector2(0.f, speed * DeltaTime));
		break;
	case EObjectDir::Left:
		AddWorldPosition(Vector2(-speed * DeltaTime, 0.f));
		break;
	case EObjectDir::Down:
		AddWorldPosition(Vector2(0.f, -speed * DeltaTime));
		break;
	case EObjectDir::Right:
		AddWorldPosition(Vector2(speed * DeltaTime, 0.f));
		break;
	case EObjectDir::LeftUp:
		AddWorldPosition(Vector2(0.f, speed * DeltaTime * 0.5f));
		AddWorldPosition(Vector2(-speed * DeltaTime * 0.5f, 0.f));
		break;
	case EObjectDir::LeftDown:
		AddWorldPosition(Vector2(-speed * DeltaTime * 0.5f, 0.f));
		AddWorldPosition(Vector2(0.f, -speed * DeltaTime * 0.5f));
		break;
	case EObjectDir::RightUp:
		AddWorldPosition(Vector2(speed * DeltaTime * 0.5f, 0.f));
		AddWorldPosition(Vector2(0.f, speed * DeltaTime * 0.5f));
		break;
	case EObjectDir::RightDown:
		AddWorldPosition(Vector2(speed * DeltaTime * 0.5f, 0.f));
		AddWorldPosition(Vector2(0.f, -speed * DeltaTime * 0.5f));
		break;
	default:
		break;
	};
	

	// 일정 간격을두고 블러드레벨만큼 마크를 남긴다. 

	m_MarkTime += DeltaTime;

	if (m_MarkTime > 0.05f && m_MarkCount != 0)
	{
		CreateMark();

		m_MarkTime = 0.f;
		--m_MarkCount;
	}
}

CBlood* CBlood::Clone() const
{
	return new CBlood(*this);
}

void CBlood::SetBloodLevel(EBloodLevel Level)
{
	m_BloodLevel = Level;

	if (Level == EBloodLevel::Low)
	{
		m_MarkCount = 7;

		m_SmallMarkCount = 3;
		m_MidiumMarkCount = 2;
		m_BigMarkCount = 2;
	}
	else if (Level == EBloodLevel::Middle)
	{
		m_MarkCount = 10;

		m_SmallMarkCount = 3;
		m_MidiumMarkCount = 3;
		m_BigMarkCount = 4;
	}
	else if (Level == EBloodLevel::High)
	{
		m_MarkCount = 13;

		m_SmallMarkCount = 2;
		m_MidiumMarkCount = 3;
		m_BigMarkCount = 8;
	}
	else
	{
		m_MarkCount = 0;
	}
		
}


void CBlood::CreateBloodArea(Vector3 Pos, Vector2 Offset)
{
	Vector2 pos(Pos.x, Pos.y);

	Vector2 areaScale(300.f, 300.f);

	m_AreaLT.x = Pos.x + Offset.x - areaScale.x / 2;
	m_AreaLT.y = Pos.y + Offset.y + areaScale.y / 2;

	m_AreaRB.x = Pos.x + Offset.x + areaScale.x / 2;
	m_AreaRB.y = Pos.y + Offset.y - areaScale.y / 2;
}

void CBlood::CreateMark()
{
	// 애리어 내의 랜덤 위치를 생성한다. 
	int randomX = (rand() % 100) + (int)m_AreaLT.x;
	int randomY = (rand() % 100) + (int)m_AreaRB.y;

	// 혈흔 생성
	CBloodMark* BloodMark = GetScene()->CreateObject<CBloodMark>("BloodMark");
	CEffect* Effect = BloodMark->GetEffect();

	if (m_BigMarkCount != 0)
	{
		--m_BigMarkCount;

		int random = rand() % 9 + 1;

		switch (random)
		{
		case 1:
			Effect->SetTexture("BloodMark1", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig06.png"));
			Effect->SetRelativeScale(19.f, 8.f);
			break;
		case 2:
			Effect->SetTexture("BloodMark2", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig07.png"));
			Effect->SetRelativeScale(21.f, 10.f);
			break;
		case 3:
			Effect->SetTexture("BloodMark3", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig08.png"));
			Effect->SetRelativeScale(18.f, 8.f);
			break;
		case 4:
			Effect->SetTexture("BloodMark4", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig09.png"));
			Effect->SetRelativeScale(20.f, 9.f);
			break;
		case 5:
			Effect->SetTexture("BloodMark5", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig10.png"));
			Effect->SetRelativeScale(15.f, 10.f);
			break;
		case 6:
			Effect->SetTexture("BloodMark6", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig11.png"));
			Effect->SetRelativeScale(20.f, 9.f);
			break;
		case 7:
			Effect->SetTexture("BloodMark7", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig12.png"));
			Effect->SetRelativeScale(27.f, 9.f);
			break;
		case 8:
			Effect->SetTexture("BloodMark8", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig13.png"));
			Effect->SetRelativeScale(19.f, 9.f);
			break;
		case 9:
			Effect->SetTexture("BloodMark9", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkBig14.png"));
			Effect->SetRelativeScale(18.f, 10.f);
			break;
		}
	}
	else if (m_MidiumMarkCount != 0)
	{
		--m_MidiumMarkCount;

		int random = rand() % 10 + 1;

		switch (random)
		{
		case 1:
			Effect->SetTexture("BloodMark10", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal01.png"));
			Effect->SetRelativeScale(10.f, 5.f);
			break;
		case 2:
			Effect->SetTexture("BloodMark11", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal02.png"));
			Effect->SetRelativeScale(12.f, 7.f);
			break;
		case 3:
			Effect->SetTexture("BloodMark12", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal03.png"));
			Effect->SetRelativeScale(12.f, 6.f);
			break;
		case 4:
			Effect->SetTexture("BloodMark13", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal04.png"));
			Effect->SetRelativeScale(11.f, 6.f);
			break;
		case 5:
			Effect->SetTexture("BloodMark14", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal05.png"));
			Effect->SetRelativeScale(16.f, 7.f);
			break;
		case 6:
			Effect->SetTexture("BloodMark15", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal06.png"));
			Effect->SetRelativeScale(12.f, 6.f);
			break;
		case 7:
			Effect->SetTexture("BloodMark16", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal07.png"));
			Effect->SetRelativeScale(12.f, 6.f);
			break;
		case 8:
			Effect->SetTexture("BloodMark17", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal08.png"));
			Effect->SetRelativeScale(10.f, 7.f);
			break;
		case 9:
			Effect->SetTexture("BloodMark18", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal09.png"));
			Effect->SetRelativeScale(10.f, 5.f);
			break;
		case 10:
			Effect->SetTexture("BloodMark19", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkNormal10.png"));
			Effect->SetRelativeScale(22.f, 7.f);
			break;
		}
	}
	else if (m_SmallMarkCount != 0)
	{
		--m_SmallMarkCount;

		int random = rand() % 7 + 1;

		switch (random)
		{
		case 1:
			Effect->SetTexture("BloodMark20", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkSmall01.png"));
			Effect->SetRelativeScale(5.f, 2.f);
			break;
		case 2:
			Effect->SetTexture("BloodMark21", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkSmall02.png"));
			Effect->SetRelativeScale(6.f, 2.f);
			break;
		case 3:
			Effect->SetTexture("BloodMark22", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkSmall03.png"));
			Effect->SetRelativeScale(4.f, 5.f);
			break;
		case 4:
			Effect->SetTexture("BloodMark23", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkSmall04.png"));
			Effect->SetRelativeScale(6.f, 4.f);
			break;
		case 5:
			Effect->SetTexture("BloodMark24", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkSmall05.png"));
			Effect->SetRelativeScale(11.f, 3.f);
			break;
		case 6:
			Effect->SetTexture("BloodMark25", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkSmall06.png"));
			Effect->SetRelativeScale(6.f, 4.f);
			break;
		case 7:
			Effect->SetTexture("BloodMark26", TEXT("Unsouled_Resource_Used/Sprite/Player/Effect/BloodMark/2DEffect_BloodMarkSmall07.png"));
			Effect->SetRelativeScale(6.f, 3.f);
			break;
		}
	}

	// 너무 작게나와서 크기 두배로 함
	Effect->SetRelativeScale(Effect->GetRelativeScale() * 2);

	BloodMark->SetLifeTime(6.f);

	//Effect->SetRenderLayerName("Monster");

	BloodMark->SetWorldPosition(randomX, randomY);
}
