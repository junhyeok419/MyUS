#include "BloodMark.h"
#include "Resource/Material/Material.h"
#include "Component/Effect.h"
#include "Scene/Scene.h"
#include "Afterimage.h"

CBloodMark::CBloodMark()
{
	SetTypeID<CBloodMark>();

	m_ObjectTypeName = "BloodMark";
}

CBloodMark::CBloodMark(const CBloodMark& Obj) :
	CGameObject(Obj)
{
}

CBloodMark::~CBloodMark()
{
	m_Effect->Destroy();
}

CEffect* CBloodMark::GetEffect()
{
	return m_Effect;
}

void CBloodMark::Start()
{
	CGameObject::Start();
}

bool CBloodMark::Init()
{
	CGameObject::Init();

	m_Effect = CreateComponent<CEffect>("Effect");

	m_Effect->SetPivot(0.5f, 0.5f);
	m_Effect->SetRelativeScale(20.f, 9.f);

	return true;
}

void CBloodMark::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	// 점점 흐려지게 만든다. 
	CMaterial* Material = m_Effect->GetMaterial(0);

	Material->AddOpacity(-(DeltaTime / 300.f));
}

void CBloodMark::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

}

CBloodMark* CBloodMark::Clone() const
{
	return new CBloodMark(*this);
}
