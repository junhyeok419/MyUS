#include "Afterimage.h"
#include "Resource/Material/Material.h"
#include "Component/Effect.h"

CAfterimage::CAfterimage()
{
	SetTypeID<CAfterimage>();

	m_ObjectTypeName = "Afterimage";

    m_Time = 0.7f;
}

CAfterimage::CAfterimage(const CAfterimage& Obj) :
	CGameObject(Obj)
{
}

CAfterimage::~CAfterimage()
{
	m_Effect->Destroy();
}

CEffect* CAfterimage::GetEffect()
{
	return m_Effect;
}

void CAfterimage::Start()
{
	CGameObject::Start();
}

bool CAfterimage::Init()
{
	CGameObject::Init();

	m_Effect = CreateComponent<CEffect>("Effect");

	m_Effect->SetPivot(0.5f, 0.5f);
	m_Effect->SetRelativeScale(50.f, 50.f);

	return true;
}

void CAfterimage::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	CMaterial* Material = m_Effect->GetMaterial(0);

    Material->AddOpacity(-DeltaTime * 1.3f);

    if (Material->GetOpacity() < 0.f)
        Destroy();
}

void CAfterimage::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CAfterimage* CAfterimage::Clone() const
{
	return new CAfterimage(*this);
}
