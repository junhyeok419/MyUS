
#include "Monster.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderPixel.h"
#include "Resource/Material/Material.h"

CMonster::CMonster()
{
	SetTypeID<CMonster>();

	m_ObjectTypeName = "Monster";
}

CMonster::CMonster(const CMonster& Obj) :
	CGameObject(Obj)
{
	m_Body = (CSpriteComponent*)FindComponent("Body");
	//m_Sprite = (CSpriteComponent*)FindComponent("Sprite");
}

CMonster::~CMonster()
{
}

void CMonster::Start()
{
	CGameObject::Start();

	//m_Body->SetInfo("PixelCollision", TEXT("PixelCollision.png"));
	//m_Body->SetPixelColorCollisionType(EPixelCollision_Type::Color_Ignore);
	//m_Body->SetPixelColor(255, 0, 255);
}

bool CMonster::Init()
{
	CGameObject::Init();

	//m_Body = CreateComponent<CColliderPixel>("Body");
	m_Body = CreateComponent<CSpriteComponent>("sddsd");
	//m_Sprite = CreateComponent<CSpriteComponent>("sdaprite");

	//m_Body->AddChild(m_Sprite);

	//m_Body->SetCollisionProfile("Back");

    SetRootComponent(m_Body);
	//m_Sprite->SetPivot(0.5f, 0.f);
	//m_Sprite->SetRelativeScale(1000.f, 1000.f);
	//m_Sprite->SetRelativePosition(0.f, -50.f);
	m_Body->SetWorldPosition(-1300.f, -776.f);
	m_Body->SetWorldScale(13300, 7700.f);

	CMaterial* Material = m_Body->GetMaterial(0);

    

	Material->SetTexture(0,0, (int)EShaderBufferType::Pixel, "sdsd",
		TEXT("Unsouled_Resource_Used/Sprite/Player/Act04_BG_RoadToJung2.png"));
	
	m_Body->SetTexture("sdsd", TEXT("Unsouled_Resource_Used/Sprite/Game/Maps/Back.png"));

	m_Body->SetRenderLayerName("Back");

	Material->SetRenderState("DepthDisable");

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMonster* CMonster::Clone() const
{
	return new CMonster(*this);
}
