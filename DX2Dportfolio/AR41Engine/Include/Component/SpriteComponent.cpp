
#include "SpriteComponent.h"
#include "../Resource/Material/Material.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Shader/Animation2DConstantBuffer.h"

CSpriteComponent::CSpriteComponent()
{
	SetTypeID<CSpriteComponent>();

	m_ComponentTypeName = "SpriteComponent";
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& component)	:
	CPrimitiveComponent(component)
{
	if (component.m_Animation)
		m_Animation = component.m_Animation->Clone();
}

CSpriteComponent::~CSpriteComponent()
{
}

void CSpriteComponent::GetAnimationNames(std::vector<std::string>& vecNames)
{
	if (m_Animation)
		m_Animation->GetAnimationNames(vecNames);
}

bool CSpriteComponent::SetTexture(CTexture* Texture)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel,
		Texture->GetName(), Texture);

	return true;
}

bool CSpriteComponent::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Name, FileName, PathName);

	return true;
}

bool CSpriteComponent::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, Name, FullPath);

	return true;
}

bool CSpriteComponent::SetTexture(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTexture(0, 0, (int)EShaderBufferType::Pixel, Name, vecFileName, PathName);

	return true;
}

bool CSpriteComponent::SetTextureFullPath(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	if (m_vecMaterial.empty())
		return false;

	m_vecMaterial[0]->SetTextureFullPath(0, 0, (int)EShaderBufferType::Pixel, Name, vecFullPath);

	return true;
}

void CSpriteComponent::SetTextureFrameIndex(int Index)
{
	m_vecMaterial[0]->SetTextureFrameIndex(0, Index);
}

CTexture* CSpriteComponent::GetTexture(int Index) const
{
	if (m_vecMaterial.empty())
		return nullptr;

	return m_vecMaterial[0]->GetTexture(Index);
}

void CSpriteComponent::ClearAnimation()
{
	m_Animation = nullptr;
	SetTextureFrameIndex(0);
}

void CSpriteComponent::UpdateAnimScale()
{
	// 매 프레임마다 텍스쳐의 사이즈를 파악해서 스프라이트 컴포넌트의 크기를 바꿔준다.
	// 애니메이션이 있을 경우 이미지 사이즈로 컴포넌트 사이즈를 결정하기 때문에 다시 구해주도록 한다.
	if (GetAnimation())
	{
		// 플레이어의 현재 애니메이션 프레임을 받아온다. 
		int CurrentFrame = GetAnimation()->GetCurrentFrame("");

		// 플레이어의 현재 애니메이션 시퀀스를 받아온다 
		CAnimationSequence2D* CurrentSequence = GetAnimation()->GetCurrentAnimationSequence("");

		// 위 두가지 정보를 이용해 현재 애니메이션 시퀀스의 프레임의 x,y 정보를 받아온다.
		Animation2DFrameData FrameData = CurrentSequence->GetFrameData(CurrentFrame);

		// 받아온 x, y 정보를 이용해 컴포넌트 크기를 변경한다. 
		//SetRelativeScale((FrameData.End));
		SetRelativeScale((FrameData.End) * 2.5);

		// 현재 프레임에 해당하는 피봇 정보를 트랜스폼에 넘겨준다.
		Vector2 CurrentFramePivot = CurrentSequence->GetFramePivot(CurrentFrame);
		SetPivot(CurrentFramePivot);
	}
}

void CSpriteComponent::Start()
{
	CPrimitiveComponent::Start();

	if (m_Animation)
		m_Animation->Start();
}

bool CSpriteComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	SetMesh("LBUVRect");

	m_Transform->Set2D(true);

	return true;
}

void CSpriteComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);

	if (m_Animation)
		m_Animation->Update(DeltaTime);
}

void CSpriteComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
}

void CSpriteComponent::Render()
{
	CPrimitiveComponent::Render();

	// 매 프레임마다 텍스쳐의 사이즈를 파악해서 스프라이트 컴포넌트의 크기를 바꿔준다.
	// 애니메이션이 있을 경우 이미지 사이즈로 컴포넌트 사이즈를 결정하기 때문에 다시 구해주도록 한다.
	if (m_Animation)
	{
		
		// 플레이어의 현재 애니메이션 프레임을 받아온다. 
		int CurrentFrame = GetAnimation()->GetCurrentFrame("");

		// 플레이어의 현재 애니메이션 시퀀스를 받아온다 
		CAnimationSequence2D* CurrentSequence = GetAnimation()->GetCurrentAnimationSequence("");

		// 위 두가지 정보를 이용해 현재 애니메이션 시퀀스의 프레임의 x,y 정보를 받아온다.
		Animation2DFrameData FrameData = CurrentSequence->GetFrameData(CurrentFrame);

		// 받아온 x, y 정보를 이용해 컴포넌트 크기를 변경한다. 
		//SetRelativeScale((FrameData.End));
		SetRelativeScale((FrameData.End) * 2.5);
		//SetRelativeScale((FrameData.End) * 2);

		// 현재 프레임에 해당하는 피봇 정보를 트랜스폼에 넘겨준다.
		Vector2 CurrentFramePivot = CurrentSequence->GetFramePivot(CurrentFrame);
		SetPivot(CurrentFramePivot);
	}

	

	if (m_Animation)
		m_Animation->SetShader();

	else
	{
		CAnimation2DConstantBuffer* Buffer = CResourceManager::GetInst()->GetAnim2DConstantBuffer();

		Buffer->SetAnim2DEnable(false);

		Buffer->UpdateBuffer();
	}
}

CSpriteComponent* CSpriteComponent::Clone() const
{
	return new CSpriteComponent(*this);
}

void CSpriteComponent::Save(FILE* File)
{
	CPrimitiveComponent::Save(File);

	bool	Animation = false;

	if (m_Animation)
		Animation = true;

	fwrite(&Animation, 1, 1, File);

	if (m_Animation)
	{
		int	Length = (int)m_Animation->m_ClassName.length();

		fwrite(&Length, 4, 1, File);
		fwrite(m_Animation->m_ClassName.c_str(), 1, Length, File);
		
		m_Animation->Save(File);
	}
}

void CSpriteComponent::Load(FILE* File)
{
	CPrimitiveComponent::Load(File);

	bool	Animation = false;

	fread(&Animation, 1, 1, File);

	if (Animation)
	{
		int	Length = 0;
		char	ClassName[256] = {};

		fread(&Length, 4, 1, File);
		fread(ClassName, 1, Length, File);

		CAnimation2D* CDO = CAnimation2D::FindCDO(ClassName);

		m_Animation = CDO->Clone();

		m_Animation->m_Owner = this;

		m_Animation->Load(File);
	}
}
