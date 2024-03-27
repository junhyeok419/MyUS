
#include "Player2D.h"
#include "Component/SpriteComponent.h"
#include "Component/CameraComponent.h"
#include "Component/TargetArm.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"
#include "Component/NavigationAgent.h"
#include "Component/Effect.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "../Scene/MainSceneInfo.h"
#include "Scene/CameraManager.h"
#include "Scene/SceneViewport.h"
#include "Device.h"
#include "../UI/MainHUD.h"
#include "Bullet.h"
#include "Afterimage.h"
#include "Resource/Material/Material.h"
#include "Animation/Animation2D.h"
#include "Blood.h"

CPlayer2D::CPlayer2D()
	: m_Attack(false)
	, m_AttackCount(0)
	, m_AttackTime(0.f)
	, m_MoveAttack(0.f)
	, m_PressUpKey(false)
	, m_PressDownKey(false)
	, m_PressRightKey(false)
	, m_PressLeftKey(false)
	, m_BlockTime(0.f)
	, m_CounterAttackTime(0.f)
	, m_JustGuard(false)
	, m_MoveSoundTime(0.f)
{
	SetTypeID<CPlayer2D>();

	m_ObjectTypeName = "Player2D";
}

CPlayer2D::CPlayer2D(const CPlayer2D& Obj)	:
	CGameObject(Obj)
{
	m_Sprite = (CSpriteComponent*)FindComponent("sprite");
	//m_RightChild = (CSceneComponent*)FindComponent("RightChild");
	//m_SpriteChild = (CSpriteComponent*)FindComponent("spriteChild");
	m_Camera = (CCameraComponent*)FindComponent("Camera");
	m_Arm = (CTargetArm*)FindComponent("Arm");
	m_Body = (CColliderBox2D*)FindComponent("Body");
	m_HitCollider = (CColliderBox2D*)FindComponent("HitCollider");
	//m_NavAgent = (CNavigationAgent*)FindComponent("NavAgent");
}

CPlayer2D::~CPlayer2D()
{
}

void CPlayer2D::Start()
{
	CGameObject::Start();

	if (m_Scene)
		m_Scene->GetCameraManager()->SetCurrentCamera(m_Camera);

	// ī�޶���ġ ����
	m_Scene->GetCameraManager()->GetCurrentCamera()->AddWorldPositionY(50.f);

	// �̵�
	CInput::GetInst()->AddBindFunction<CPlayer2D>("RotationInv", Input_Type::Push,
		this, &CPlayer2D::RotationInv, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Rotation", Input_Type::Push,
		this, &CPlayer2D::Rotation, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Push,
		this, &CPlayer2D::MoveUp, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Push,
		this, &CPlayer2D::MoveDown, m_Scene);

	// Ű����
	CInput::GetInst()->AddBindFunction<CPlayer2D>("RotationInv", Input_Type::Up,
		this, &CPlayer2D::ResetLeftKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Rotation", Input_Type::Up,
		this, &CPlayer2D::ResetRightKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveUp", Input_Type::Up,
		this, &CPlayer2D::ResetUpKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveDown", Input_Type::Up,
		this, &CPlayer2D::ResetDownKey, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Fire", Input_Type::Up,
		this, &CPlayer2D::ResetAttackKey, m_Scene);

	// ���
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Fire", Input_Type::Down,
		this, &CPlayer2D::Fire, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Dash", Input_Type::Down,
		this, &CPlayer2D::Dash, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("Guard", Input_Type::Down,
		this, &CPlayer2D::Guard, m_Scene);
	CInput::GetInst()->AddBindFunction<CPlayer2D>("Guard", Input_Type::Up,
		this, &CPlayer2D::ResetGuardKey, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("DoubleEdge", Input_Type::Down,
		this, &CPlayer2D::DoubleEdge_Pre, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("GhostMove", Input_Type::Down,
		this, &CPlayer2D::GhostMove, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("GhostSlash", Input_Type::Down,
		this, &CPlayer2D::GhostSlash, m_Scene);

	CInput::GetInst()->AddBindFunction<CPlayer2D>("MoveClick", Input_Type::Down,
		this, &CPlayer2D::MoveClick, m_Scene);

	
}

bool CPlayer2D::Init()
{
	CGameObject::Init();

	m_Sprite = CreateComponent<CSpriteComponent>("Sprite");
	//m_RightChild = CreateComponent<CSceneComponent>("RightChild");
	//m_SpriteChild = CreateComponent<CSpriteComponent>("spriteChild");
	m_Camera = CreateComponent<CCameraComponent>("Camera");
	m_Arm = CreateComponent<CTargetArm>("Arm");
	m_HitCollider = CreateComponent<CColliderBox2D>("HitCollider");
	m_Body = CreateComponent<CColliderBox2D>("Body");
	//m_NavAgent = CreateComponent<CNavigationAgent>("NavAgent");

	m_HitCollider->SetCollisionProfile("Player");
	m_Body->SetCollisionProfile("Object");

	m_Body->SetCollisionCallback<CPlayer2D>(ECollision_Result::Collision, this, &CPlayer2D::CollisionBeginObject);
	m_Body->SetCollisionCallback<CPlayer2D>(ECollision_Result::Release, this, &CPlayer2D::CollisionEndObject);

	SetRootComponent(m_HitCollider);

	m_HitCollider->AddChild(m_Body);
	m_HitCollider->AddChild(m_Sprite);
	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	m_HitCollider->SetBoxSize(40.f, 100.f);
	m_Body->SetBoxSize(40.f, 50.f);

	m_Body->AddRelativePosition(Vector2(0.f, -25.f));

	m_Sprite->SetPivot(0.5f, 0.f);
	m_Sprite->SetRelativePosition(0.f, -50.f);
	m_HitCollider->SetWorldPosition(500.f, 500.f);

	m_Sprite->SetRenderLayerName("Player");

	CMaterial* Material = m_Sprite->GetMaterial(0);

	Material->SetOpacity(1.f);


	//Material->SetRenderState("AlphaBlend");
	//Material->SetRenderState("DepthDisable");
	//Material->SetRenderState("DepthLessEqual");
	 
	
	//m_Sprite->AddChild(m_RightChild);

	//m_Sprite->GetMaterial(0)->SetBaseColorUnsignedChar(255, 255, 0, 0);


	Resolution RS = CDevice::GetInst()->GetResolution();

	float Width = (float)RS.Width / 2.f;
	float Height = (float)RS.Height / 2.f;

	m_Arm->SetTargetOffset(Vector3(-Width, -Height, 0.f));

	//m_RightChild->AddChild(m_SpriteChild);
	
	//m_HitCollider->SetBoxSize(Vector2(40.f, 100.f));


	
	//m_Sprite->SetRelativeScale(34.f, 80.f);
	//m_Sprite->SetPivot(0.5f, 0.f);
	//m_Sprite->SetInheritRotZ(true);
	//m_Sprite->SetRelativeRotationZ(30.f);

	

	//m_RightChild->SetRelativePosition(150.f, 0.f);
	//m_RightChild->SetInheritRotZ(true);

	//m_SpriteChild->SetRelativeScale(50.f, 50.f);
	//m_SpriteChild->SetRelativePosition(100.f, 0.f);
	//m_SpriteChild->SetInheritRotZ(true);

	CAnimation2D* Anim = m_Sprite->SetAnimation<CAnimation2D>("PlayerAnim");

	// ����
	Anim->AddAnimation("Stand", "PlayerStand", 2.f);
	Anim->SetLoop("Stand", true);

	Anim->AddAnimation("StandBack", "PlayerStandBack", 2.f);
	Anim->SetLoop("StandBack", true);

	Anim->AddAnimation("StandLeft", "PlayerStandLeft", 2.f);
	Anim->SetLoop("StandLeft", true);

	Anim->AddAnimation("StandRight", "PlayerStandRight", 2.f);
	Anim->SetLoop("StandRight", true);

	// �޸���
	Anim->AddAnimation("Running", "PlayerRunning", 0.75f);
	Anim->SetLoop("Running", true);

	Anim->AddAnimation("RunningRight", "PlayerRunningRight", 0.75f);
	Anim->SetLoop("RunningRight", true);

	Anim->AddAnimation("RunningLeft", "PlayerRunningLeft", 0.75f);
	Anim->SetLoop("RunningLeft", true);

	Anim->AddAnimation("RunningBack", "PlayerRunningBack", 0.75f);
	Anim->SetLoop("RunningBack", true);

	// ����1 
	Anim->AddAnimation("Attack1Down", "PlayerAttack1Down", 0.6f);
	Anim->SetLoop("Attack1Down", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1DownChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Down", "Attack1Down", 4, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack1Left", "PlayerAttack1Left", 0.6f);
	Anim->SetLoop("Attack1Left", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1LeftChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Left", "Attack1Left", 4, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack1Right", "PlayerAttack1Right", 0.6f);
	Anim->SetLoop("Attack1Right", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1RightChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Right", "Attack1Right", 4, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack1Up", "PlayerAttack1Up", 0.6f);
	Anim->SetLoop("Attack1Up", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1UpChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack1Up", "Attack1Up", 4, this, &CPlayer2D::Attack);

	// ����2
	Anim->AddAnimation("Attack2Down", "PlayerAttack2Down", 0.6f);
	Anim->SetLoop("Attack2Down", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2DownChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Down", "Attack2Down", 4, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack2Left", "PlayerAttack2Left", 0.6f);
	Anim->SetLoop("Attack2Left", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2LeftChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Left", "Attack2Left", 4, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack2Right", "PlayerAttack2Right", 0.6f);
	Anim->SetLoop("Attack2Right", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2RightChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Right", "Attack2Right", 4, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack2Up", "PlayerAttack2Up", 0.6f);
	Anim->SetLoop("Attack2Up", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2UpChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack2Up", "Attack2Up", 4, this, &CPlayer2D::Attack);

	// ����3
	Anim->AddAnimation("Attack3Down", "PlayerAttack3Down", 0.7f);
	Anim->SetLoop("Attack3Down", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3DownChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Down", "Attack3Down", 5, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack3Left", "PlayerAttack3Left", 0.7f);
	Anim->SetLoop("Attack3Left", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3LeftChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Left", "Attack3Left", 5, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack3Right", "PlayerAttack3Right", 0.7f);
	Anim->SetLoop("Attack3Right", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3RightChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Right", "Attack3Right", 5, this, &CPlayer2D::Attack);

	Anim->AddAnimation("Attack3Up", "PlayerAttack3Up", 0.7f);
	Anim->SetLoop("Attack3Up", false);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3UpChainActive", 6, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("Attack3Up", "Attack3Up", 4, this, &CPlayer2D::Attack);

	// �뽬
	Anim->AddAnimation("DashLeft", "PlayerDashLeft", 0.7f);
	Anim->SetLoop("DashLeft", false);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage11", 10, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage12", 11, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage13", 12, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftAfterimage14", 13, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashLeftChainActive", 15, this, &CPlayer2D::ChainActive);

	Anim->AddAnimation("DashRight", "PlayerDashRight", 0.7f);
	Anim->SetLoop("DashRight", false);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage11", 10, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage12", 11, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage13", 12, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightAfterimage14", 13, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashRightChainActive", 15, this, &CPlayer2D::ChainActive);

	Anim->AddAnimation("DashUp", "PlayerDashUp", 0.7f);
	Anim->SetLoop("DashUp", false);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage11", 10, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage12", 11, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage13", 12, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpAfterimage14", 13, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashUpChainActive", 15, this, &CPlayer2D::ChainActive);

	Anim->AddAnimation("DashDown", "PlayerDashDown", 0.7f);
	Anim->SetLoop("DashDown", false);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage11", 10, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage12", 11, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage13", 12, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownAfterimage14", 13, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashDownChainActive", 15, this, &CPlayer2D::ChainActive);

	// �뽬 ���� 
	Anim->AddAnimation("DashAttackLeft", "PlayerDashAttackLeft", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashLeft", "DashAttackLeft", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeftChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackLeft", "DashAttackLeft", 1, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DashAttackRight", "PlayerDashAttackRight", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashRight", "DashAttackRight", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRightChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackRight", "DashAttackRight", 1, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DashAttackUp", "PlayerDashAttackUp", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashUp", "DashAttackUp", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUpChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUp", "DashAttackUp", 1, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DashAttackDown", "PlayerDashAttackDown", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashDown", "DashAttackDown", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDownChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDown", "DashAttackDown", 1, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DashAttackDownLeft", "PlayerDashAttackDownLeft", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashDownLeft", "DashAttackDownLeft", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeftChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownLeft", "DashAttackDownLeft", 1, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DashAttackDownRight", "PlayerDashAttackDownRight", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashDownRight", "DashAttackDownRight", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRightChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackDownRight", "DashAttackDownRight", 1, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DashAttackUpLeft", "PlayerDashAttackUpLeft", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashUpLeft", "DashAttackUpLeft", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeftChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpLeft", "DashAttackUpLeft", 1, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DashAttackUpRight", "PlayerDashAttackUpRight", 0.6f);
	Anim->AddCurrentNotify<CPlayer2D>("DashUpRight", "DashAttackUpRight", 4, this, &CPlayer2D::DashAttack);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRightChainActive", 3, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DashAttackUpRight", "DashAttackUpRight", 1, this, &CPlayer2D::Attack);

	// ����
	Anim->AddAnimation("BlockLeft", "PlayerBlockLeft", 1.f, true);
	Anim->SetLoop("BlockLeft", true);

	Anim->AddAnimation("BlockRight", "PlayerBlockRight", 1.f, true);
	Anim->SetLoop("BlockRight", true);

	Anim->AddAnimation("BlockUp", "PlayerBlockUp", 1.f, true);
	Anim->SetLoop("BlockUp", true);

	Anim->AddAnimation("BlockDown", "PlayerBlockDown", 1.f, true);
	Anim->SetLoop("BlockDown", true);

	// �糯���� �غ� 
	Anim->AddAnimation("DoubleEdgeRight_Pre", "PlayerDoubleEdgeRight_Pre", 0.35f);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight_Pre", "DoubleEdgeRightChainInactive", 0, this, &CPlayer2D::ChainInactive);

	Anim->AddAnimation("DoubleEdgeDown_Pre", "PlayerDoubleEdgeDown_Pre", 0.35f);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown_Pre", "DoubleEdgeDownChainInactive", 0, this, &CPlayer2D::ChainInactive);

	Anim->AddAnimation("DoubleEdgeLeft_Pre", "PlayerDoubleEdgeLeft_Pre", 0.35f);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft_Pre", "DoubleEdgeLeftChainInactive", 0, this, &CPlayer2D::ChainInactive);

	Anim->AddAnimation("DoubleEdgeUp_Pre", "PlayerDoubleEdgeUp_Pre", 0.35f);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp_Pre", "DoubleEdgeUpChainInactive", 0, this, &CPlayer2D::ChainInactive);

	// �糯���� 
	Anim->AddAnimation("DoubleEdgeRight", "PlayerDoubleEdgeRight", 1.1f);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRightChainActive", 8, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRight1", 1, this, &CPlayer2D::Attack);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeRight", "DoubleEdgeRight2", 6, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DoubleEdgeDown", "PlayerDoubleEdgeDown", 1.1f);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDownChainActive", 8, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDown1", 1, this, &CPlayer2D::Attack);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeDown", "DoubleEdgeDown2", 6, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DoubleEdgeLeft", "PlayerDoubleEdgeLeft", 1.1f);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeftChainActive", 8, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeft1", 1, this, &CPlayer2D::Attack);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeLeft", "DoubleEdgeLeft2", 6, this, &CPlayer2D::Attack);

	Anim->AddAnimation("DoubleEdgeUp", "PlayerDoubleEdgeUp", 1.1f);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage6", 5, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage7", 6, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage8", 7, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpAfterimage10", 9, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUpChainActive", 8, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUp1", 1, this, &CPlayer2D::Attack);
	Anim->AddCurrentNotify<CPlayer2D>("DoubleEdgeUp", "DoubleEdgeUp2", 6, this, &CPlayer2D::Attack);

	// ��Ʈ
	Anim->AddAnimation("HitByLeft", "PlayerHitByLeft", 0.2f);
	Anim->AddCurrentNotify<CPlayer2D>("HitByLeft", "HitByLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("HitByLeft", "HitByLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("HitByLeft", "HitByLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("HitByRight", "PlayerHitByRight", 0.2f);
	Anim->AddCurrentNotify<CPlayer2D>("HitByRight", "HitByRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("HitByRight", "HitByRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("HitByRight", "HitByRightAfterimage3", 2, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("HitByDown", "PlayerHitByDown", 0.2f);
	Anim->AddCurrentNotify<CPlayer2D>("HitByDown", "HitByDownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("HitByDown", "HitByDownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("HitByDown", "HitByDownAfterimage3", 2, this, &CPlayer2D::Afterimage);

	// ���� ���� 
	Anim->AddAnimation("BlockedLeft1", "PlayerBlockedLeft1", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedLeft1", "BlockedLeft1Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedLeft1", "BlockedLeft1Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedLeft2", "PlayerBlockedLeft2", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedLeft2", "BlockedLeft2Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedLeft2", "BlockedLeft2Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedRight1", "PlayerBlockedRight1", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedRight1", "BlockedRight1Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedRight1", "BlockedRight1Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedRight2", "PlayerBlockedRight2", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedRight2", "BlockedRight2Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedRight2", "BlockedRight2Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedUp1", "PlayerBlockedUp1", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedUp1", "BlockedUp1Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedUp1", "BlockedUp1Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedUp2", "PlayerBlockedUp2", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedUp2", "BlockedUp2Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedUp2", "BlockedUp2Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedDown1", "PlayerBlockedDown1", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedDown1", "BlockedDown1Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedDown1", "BlockedDown1Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedDown2", "PlayerBlockedDown2", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedDown2", "BlockedDown2Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedDown2", "BlockedDown2Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedLeftUp1", "PlayerBlockedLeftUp1", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedLeftUp1", "BlockedLeftUp1Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedLeftUp1", "BlockedLeftUp1Afterimage2", 1, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("BlockedRightDown1", "PlayerBlockedRightDown1", 0.3f);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedRightDown1", "BlockedRightDown1Afterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("BlockedRightDown1", "BlockedRightDown1Afterimage2", 1, this, &CPlayer2D::Afterimage);

	// ī���;���
	Anim->AddAnimation("CounterLeft", "PlayerCounterLeft", 0.2f);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterLeft", "CounterLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("CounterDownLeft", "PlayerCounterDownLeft", 0.2f);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownLeft", "CounterDownLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("CounterRight", "PlayerCounterRight", 0.2f);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterRight", "CounterRightAfterimage9", 8, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("CounterDownRight", "PlayerCounterDownRight", 0.2f);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterDownRight", "CounterDownRightAfterimage9", 8, this, &CPlayer2D::Afterimage);

	Anim->AddAnimation("CounterUp", "PlayerCounterUp", 0.2f);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage1", 0, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage2", 1, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage3", 2, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage4", 3, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage5", 4, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("CounterUp", "CounterUpAfterimage9", 8, this, &CPlayer2D::Afterimage);

	//Anim->AddAnimation("CounterSlash", "CounterSlash", 1.f);

	// �ͽź��� �غ�
	Anim->AddAnimation("SlashReadyRight", "PlayerSlashReadyRight", 0.35f);
	//Anim->AddCurrentNotify<CPlayer2D>("SlashReadyRight", "SlashRightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	
	Anim->AddAnimation("SlashReadyRightDown", "PlayerSlashReadyRightDown", 0.35f);
	//Anim->AddCurrentNotify<CPlayer2D>("SlashReadyRightDown", "SlashRightDownChainInactive", 0, this, &CPlayer2D::ChainInactive);

	Anim->AddAnimation("SlashReadyLeft", "PlayerSlashReadyLeft", 0.35f);
	//Anim->AddCurrentNotify<CPlayer2D>("SlashReadyLeft", "SlashLeftChainInactive", 0, this, &CPlayer2D::ChainInactive);

	Anim->AddAnimation("SlashReadyLeftDown", "PlayerSlashReadyLeftDown", 0.35f);
	//Anim->AddCurrentNotify<CPlayer2D>("SlashReadyLeftDown", "SlashLeftDownChainInactive", 0, this, &CPlayer2D::ChainInactive);

	Anim->AddAnimation("SlashReadyUp", "PlayerSlashReadyUp", 0.35f);
	//Anim->AddCurrentNotify<CPlayer2D>("SlashReadyUp", "SlashUpChainInactive", 0, this, &CPlayer2D::ChainInactive);

	// �ͽź���
	Anim->AddAnimation("SlashLeft", "PlayerCounterLeft", 0.2f); // + ���� �� 
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeftChainActive", 9, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeft", "SlashLeft", 0, this, &CPlayer2D::Attack);


	Anim->AddAnimation("SlashLeftDown", "PlayerCounterDownLeft", 0.2f);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDownChainActive", 9, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashLeftDown", "SlashLeftDown", 0, this, &CPlayer2D::Attack);

	Anim->AddAnimation("SlashRight", "PlayerCounterRight", 0.2f); // + ������ �� 
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRightChainActive", 9, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRight", "SlashRight", 0, this, &CPlayer2D::Attack);

	Anim->AddAnimation("SlashRightDown", "PlayerCounterDownRight", 0.2f);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDownChainActive", 9, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashRightDown", "SlashRightDown", 0, this, &CPlayer2D::Attack);

	Anim->AddAnimation("SlashUp", "PlayerCounterUp", 0.2f);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpChainInactive", 0, this, &CPlayer2D::ChainInactive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage1", 0, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage2", 1, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage3", 2, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage4", 3, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage5", 4, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage6", 5, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage7", 6, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage8", 7, this, &CPlayer2D::Afterimage);
    Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpAfterimage9", 8, this, &CPlayer2D::Afterimage);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUpChainActive", 9, this, &CPlayer2D::ChainActive);
	Anim->AddCurrentNotify<CPlayer2D>("SlashUp", "SlashUp", 0, this, &CPlayer2D::Attack);
	

	SetDir(EObjectDir::Up);
	SetMoveSpeed(250.f);

	Anim->SetCurrentAnimation("Stand");

	Anim->SetCurrentEndFunction("Attack1Down", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack1Left", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack1Right", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack1Up", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack2Down", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack2Left", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack2Right", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack2Up", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack3Down", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack3Left", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack3Right", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("Attack3Up", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("DashLeft", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashRight", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashUp", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashDown", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackLeft", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackRight", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackUp", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackDown", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackDownLeft", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackDownRight", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackUpLeft", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DashAttackUpRight", this, &CPlayer2D::DashEnd);
	Anim->SetCurrentEndFunction("DoubleEdgeRight_Pre", this, &CPlayer2D::DoubleEdge);
	Anim->SetCurrentEndFunction("DoubleEdgeRight", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("DoubleEdgeDown_Pre", this, &CPlayer2D::DoubleEdge);
	Anim->SetCurrentEndFunction("DoubleEdgeDown", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("DoubleEdgeLeft_Pre", this, &CPlayer2D::DoubleEdge);
	Anim->SetCurrentEndFunction("DoubleEdgeLeft", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("DoubleEdgeUp_Pre", this, &CPlayer2D::DoubleEdge);
	Anim->SetCurrentEndFunction("DoubleEdgeUp", this, &CPlayer2D::AttackEnd);
	Anim->SetCurrentEndFunction("SlashReadyUp", this, &CPlayer2D::GhostSlash);
	Anim->SetCurrentEndFunction("SlashReadyLeft", this, &CPlayer2D::GhostSlash);
	Anim->SetCurrentEndFunction("SlashReadyRight", this, &CPlayer2D::GhostSlash);
	Anim->SetCurrentEndFunction("SlashReadyLeftDown", this, &CPlayer2D::GhostSlash);
	Anim->SetCurrentEndFunction("SlashReadyRightDown", this, &CPlayer2D::GhostSlash);
	


	m_Sprite->GetMaterial(0)->SetFullColorUnsignedChar(255, 255, 0, 255);

    m_HP = 1000.f;
    m_Stamina = 100.f;

	return true;
}

void CPlayer2D::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	m_Scene;

	// ���� �浹ü�� 0.2 �� �� �����Ѵ�.
	// ���������� �ð��� �������� ���� �� �����Ƿ� 
	if (m_AttackCollider/* && !m_CounterAttack*/)
	{
		if (m_UseSkill == EPlayerSkills::GhostSlash)
			m_AttackColliderLifeTime += (DeltaTime * 0.7f);
		else
			m_AttackColliderLifeTime += DeltaTime;

		if (m_AttackColliderLifeTime > 0.2f)
		{
			m_AttackColliderLifeTime = 0.f;
			m_AttackCollider->Destroy();
		}
	}


	if(m_AttackSingleCollider)
	{
		m_AttackSingleColliderLifeTime += DeltaTime;

		if (m_AttackSingleColliderLifeTime > 0.3f)
		{
			m_AttackSingleColliderLifeTime = 0.f;
			m_AttackSingleCollider->Destroy();
		}
	}

	// ����Ʈ���� Ÿ�̸Ӱ� ���ư��� ���̶�� 
	if (m_JustGuardTime != 0.f)
	{
		m_JustGuardTime -= DeltaTime;
		
		// ����Ʈ���� ���¶��
		if (m_JustGuard)
		{
			// ó�� ������ ������� 
			m_Sprite->GetMaterial(0)->SetFullColorUnsignedChar(255, 255, 255, 0);
			m_Sprite->GetMaterial(0)->SetOnlyColor(true);
			
		}

		if (m_JustGuardTime <= 0.f)
		{
			m_Sprite->GetMaterial(0)->SetOnlyColor(false);
			m_JustGuard = false;
			m_JustGuardTime = 0.f;
		}
	}

	// ����Ʈ���尡 ������ �� ī���;��� �ߵ� ���� �ð��� ���� ������
	// ���� �����ð� ���ʹ� �ʷϻ�����
	if (m_Invincible != 0.f && m_JustGuardTime == 0.f)
	{
		m_Invincible -= DeltaTime;

		m_Sprite->GetMaterial(0)->SetFullColorUnsignedChar(101, 255, 94, 0);
		m_Sprite->GetMaterial(0)->SetOnlyColor(true);

		if (m_Invincible <= 0.f)
		{
			m_Invincible = 0.f;
			m_Sprite->GetMaterial(0)->SetOnlyColor(false);
		}
	}
		
	// �￬���� 1ȸ �̻� ������� ���, 0.3�� ���Ŀ� ��Ÿ�� �����ϰ� �� ���̴�. 
	if (0 < m_AttackCount)
		m_AttackTime += DeltaTime;

	// �밢�� �̵��� ���
	if (m_PressLeftKey && m_PressUpKey || m_PressLeftKey && m_PressDownKey || m_PressRightKey && m_PressUpKey || m_PressRightKey && m_PressDownKey)
	{
		m_DiagonalMove = true;

		// �⺻ �̵��ÿ� �ӵ��� ���δ�. 
		if(!m_Attack && !m_Dash && m_HitTime == 0.f && (!m_Guard || m_BlockTime == 0.f) && !m_CounterAttack && m_GhostSlashUsable == 0.f && m_GhostSlashTime == 0.f)
			m_MoveSpeed = 275.f;
	}
	else
		m_DiagonalMove = false;

	// ü�� ���� ������ ��� �÷��̾ 0.5�ʰ� ��������� �����δ�. 
	if (m_Chain)
	{
		m_Sprite->GetMaterial(0)->SetFullColorUnsignedChar(255, 255, 0, 255);

		m_ChainTime += DeltaTime;

		if (m_ChainTime > 0.04f)
		{
			m_ChainTime = 0.f;
			
			switch (m_Sprite->GetMaterial(0)->GetOnlyColor())
			{
			case 0:
				m_Sprite->GetMaterial(0)->SetOnlyColor(true);
				break;
			case 1:
				m_Sprite->GetMaterial(0)->SetOnlyColor(false);
				break;
			}
		}
	}
	// �����ð��� ������ ����Ʈ���� ���µ� �ƴ϶�� �ǵ�����. 
	else if(!m_JustGuard && m_Invincible == 0.f)
		m_Sprite->GetMaterial(0)->SetOnlyColor(false);

	// ī���;��� ���� Ÿ�̸Ӹ� ������. 
	if (m_CounterTime > 0.f)
	{
		m_CounterTime -= DeltaTime;
		
		if (m_CounterTime <= 0.f)
		{
			// �ٽ� �ǵ�����. 
			m_Body->SetCollisionProfile("Object");

			m_CounterTime = 0.f;
		}
	}

	// �ͽź��� ���� Ÿ�̸Ӹ� ������. 
	if (m_GhostSlashUsable > 0.f)
	{
		m_GhostSlashUsable -= DeltaTime;

		if (m_GhostSlashUsable <= 0.f)
		{
			// �ٽ� �ǵ�����. 
			m_Body->SetCollisionProfile("Object");

			m_GhostSlashUsable = 0.f;
			m_GhostSlashCount = 0;
			m_GhostSlashTime = 0.f;

			ChainInactive();

			m_UseSkill = EPlayerSkills::None;
			//AttackEnd();
		}
	}

	//m_Sprite->AddRelativeRotationZ(180.f * DeltaTime);

	//m_RightChild->AddRelativeRotationZ(360.f * DeltaTime);
}

void CPlayer2D::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	// ������ ��� 
	if (m_BlockTime > 0.f && m_CounterAttackTime == 0.f && m_GhostSlashUsable == 0.f && m_GhostSlashTime == 0.f)
	{
		// ���� Ÿ�ֿ̹� �ִϸ��̼� ����
		if (m_BlockTime == 0.6f)
		{
			// �з����� ���� (����Ʈ ������ ���� �����Ѵ�.)
			if(m_JustGuard)
				m_MoveSpeed = 0.f;
            else
            {
                if (m_HitTypeByBoss == EPlayerHitTypeByBoss::Punch)
                {
                    m_MoveSpeed = 600.f;
                }
                else if (m_HitTypeByBoss == EPlayerHitTypeByBoss::Stomp)
                {
                    m_MoveSpeed = 0.f;
                }
                else if (m_HitTypeByBoss == EPlayerHitTypeByBoss::Rush)
                {
                    m_MoveSpeed = 1500.f;
                }
                else
                    m_MoveSpeed = 600.f;
                
            }
	
			m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

			int Random = (rand() % 2) + 1;

			// ���Ͱ� �ڽ��� �����̶��
			if (m_EnemyDir == EObjectDir::Left)
			{
				if(Random == 1)
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedLeft1");
				else
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedLeft2");

				m_Dir = EObjectDir::Left;
			}
			else if (m_EnemyDir == EObjectDir::LeftUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("BlockedLeftUp1");
				m_Dir = EObjectDir::LeftUp;
			}
			else if (m_EnemyDir == EObjectDir::LeftDown)
			{
				if (Random == 1)
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedDown1");
				else
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedDown2");

				m_Dir = EObjectDir::LeftDown;
			}
			// ���Ͱ� �ڽ��� �������̶�� 
			else if (m_EnemyDir == EObjectDir::Right)
			{
				if (Random == 1)
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedRight1");
				else
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedRight2");

				m_Dir = EObjectDir::Right;
			}
			else if (m_EnemyDir == EObjectDir::RightUp)
			{
				if (Random == 1)
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedUp1");
				else
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedUp2");

				m_Dir = EObjectDir::RightUp;
			}
			else if (m_EnemyDir == EObjectDir::RightDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("BlockedRightDown1");
				m_Dir = EObjectDir::RightDown;
			}
			// ���Ͱ� �ڽ��� ����� 
			else if (m_EnemyDir == EObjectDir::Up)
			{
				if (Random == 1)
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedUp1");
				else
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedUp2");

				m_Dir = EObjectDir::Up;
			}
			// ���Ͱ� �ڽ��� �Ʒ���� 
			else if (m_EnemyDir == EObjectDir::Down)
			{
				if (Random == 1)
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedDown1");
				else
					m_Sprite->GetAnimation()->ChangeAnimation("BlockedDown2");

				m_Dir = EObjectDir::Down;
			}

			// �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
			if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
				|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
				m_MoveSpeed *= (3.f / 4.f);
		}

		if (m_BlockTime > 0.f)
		{
			// �ڿ������� ����
			m_MoveSpeed -= 2000.f * DeltaTime;

			if (m_MoveSpeed < 0.f)
				m_MoveSpeed = 0.f;
			

			// ���� �ǰ� �̵� �κ� 
			switch (m_Dir)
			{
			case EObjectDir::Up:
				m_HitCollider->AddWorldPosition(Vector3(0.f, -m_MoveSpeed * g_DeltaTime, 0.f));
				break;
			case EObjectDir::Left:
				m_HitCollider->AddWorldPosition(Vector3(m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
				break;
			case EObjectDir::Down:
				m_HitCollider->AddWorldPosition(Vector3(0.f, m_MoveSpeed * g_DeltaTime, 0.f));
				break;
			case EObjectDir::Right:
				m_HitCollider->AddWorldPosition(Vector3(-m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
				break;
			case EObjectDir::LeftUp:
				m_HitCollider->AddWorldPosition(Vector3(0.f, -m_MoveSpeed * g_DeltaTime, 0.f));
				m_HitCollider->AddWorldPosition(Vector3(m_MoveSpeed* g_DeltaTime, 0.f, 0.f));
				break;
			case EObjectDir::LeftDown:
				m_HitCollider->AddWorldPosition(Vector3(m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
				m_HitCollider->AddWorldPosition(Vector3(0.f, m_MoveSpeed* g_DeltaTime, 0.f));
				break;
			case EObjectDir::RightUp:
				m_HitCollider->AddWorldPosition(Vector3(-m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
				m_HitCollider->AddWorldPosition(Vector3(0.f, -m_MoveSpeed * g_DeltaTime, 0.f));
				break;
			case EObjectDir::RightDown:
				m_HitCollider->AddWorldPosition(Vector3(-m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
				m_HitCollider->AddWorldPosition(Vector3(0.f, m_MoveSpeed* g_DeltaTime, 0.f));
				break;
			}

			m_BlockTime -= DeltaTime;

			if (m_BlockTime <= 0.f)
			{
				m_BlockTime = 0.f;
				m_MoveSpeed = 200.f;

				// �ִϸ��̼� �ٲ��ֱ����� 
				switch (m_Dir)
				{
				case EObjectDir::Up:
				case EObjectDir::LeftUp:
				case EObjectDir::RightUp:
					m_Sprite->GetAnimation()->ChangeAnimation("BlockUp");
					break;
				case EObjectDir::Left:
					m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
					break;
				case EObjectDir::Down:
				case EObjectDir::LeftDown:
				case EObjectDir::RightDown:
					m_Sprite->GetAnimation()->ChangeAnimation("BlockDown");
					break;
				case EObjectDir::Right:
					m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
					break;
				}
			}
		}
	}
	// �ǰ� ������ ��� 
	else if (m_HitTime > 0.f && m_CounterAttack == false && m_GhostSlashUsable == 0.f && m_GhostSlashTime == 0.f)
	{
		// �ڽ��� ��ġ ��� ���� ��ġ�� ���Ͽ� �з��� ������ ���Ѵ�. 
		if (m_HitTime == 0.8f)
		{
			m_AttackCount = 0;

			// �˹� �̵��ӵ� 
            if (m_HitTypeByBoss == EPlayerHitTypeByBoss::Punch)
            {
                m_MoveSpeed = 1000.f;
            }
            else if (m_HitTypeByBoss == EPlayerHitTypeByBoss::Stomp)
            {
                m_MoveSpeed = 0.f;
            }
            else if (m_HitTypeByBoss == EPlayerHitTypeByBoss::Rush)
            {
                m_MoveSpeed = 2750.f;
            }
            else
                m_MoveSpeed = 1300.f;

			m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

			// ���Ͱ� �ڽ��� �����̶��
			if (m_EnemyDir == EObjectDir::Left)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
				m_Dir = EObjectDir::Right;
			}
			else if (m_EnemyDir == EObjectDir::LeftUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
				m_Dir = EObjectDir::RightDown;
			}
			else if (m_EnemyDir == EObjectDir::LeftDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByDown");
				m_Dir = EObjectDir::RightUp;
			}
			// ���Ͱ� �ڽ��� �������̶�� 
			else if (m_EnemyDir == EObjectDir::Right)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
				m_Dir = EObjectDir::Left;
			}
			else if (m_EnemyDir == EObjectDir::RightUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
				m_Dir = EObjectDir::LeftDown;
			}
			else if (m_EnemyDir == EObjectDir::RightDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByRight");
				m_Dir = EObjectDir::LeftUp;
			}
			// ���Ͱ� �ڽ��� ����� 
			else if (m_EnemyDir == EObjectDir::Up)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByLeft");
				m_Dir = EObjectDir::Down;
			}
			// ���Ͱ� �ڽ��� �Ʒ���� 
			else if (m_EnemyDir == EObjectDir::Down)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("HitByDown");
				m_Dir = EObjectDir::Up;
			}

			// �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
			if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
				|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
				m_MoveSpeed *= (2.f / 3.f);
		}

		// �ڿ������� ����
		if (m_HitTime > 0.f)
		{
			m_MoveSpeed -= 5000.f * DeltaTime;

			if (m_MoveSpeed < 0.f)
				m_MoveSpeed = 0.f;
		}

		m_HitTime -= DeltaTime;

		if (m_HitTime <= 0.f)
		{
			m_HitTime = 0.f;
			m_MoveSpeed = 250.f;

			m_PressDownKeyForGhostMove = false;
			m_PressUpKeyForGhostMove = false;
			m_PressRightKeyForGhostMove = false;
			m_PressLeftKeyForGhostMove = false;
		}

		// ���� �ǰ� �̵� �κ� 
		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::Left:
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::Down:
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::Right:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::LeftUp:
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::LeftDown:
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::RightUp:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::RightDown:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		}	
	}
	// ī���� ���� �ߵ����� �� �̵� ����
	else if (m_CounterAttack)
	{
		// �ڽ��� ��ġ ��� ���� ��ġ�� ���Ͽ� �з��� ������ ���Ѵ�. 
		if (m_CounterAttackTime == 0.7f)
		{
			// Ű�� �ϴ� �����Ѵ�. �ڲ� �밢���⴩���鼭 ī���;��� ������
			ResetRightKey();
			ResetLeftKey();
			ResetUpKey();
			ResetDownKey();

			// ���� �̵��ӵ� 
			m_MoveSpeed = 8000.f;

			//m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

			// ���Ͱ� �ڽ��� �����̶��
			if (m_TargetDir == EObjectDir::Left)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterLeft");
				m_Dir = EObjectDir::Left;
			}
			else if (m_TargetDir == EObjectDir::LeftUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterLeft");
				m_Dir = EObjectDir::LeftUp;
			}
			else if (m_TargetDir == EObjectDir::LeftDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterDownLeft");
				m_Dir = EObjectDir::LeftDown;
			}
			// ���Ͱ� �ڽ��� �������̶�� 
			else if (m_TargetDir == EObjectDir::Right)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterRight");
				m_Dir = EObjectDir::Right;
			}
			else if (m_TargetDir == EObjectDir::RightUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterRight");
				m_Dir = EObjectDir::RightUp;
			}
			else if (m_TargetDir == EObjectDir::RightDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterDownRight");
				m_Dir = EObjectDir::RightDown;
			}
			// ���Ͱ� �ڽ��� ����� 
			else if (m_TargetDir == EObjectDir::Up)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterUp");
				m_Dir = EObjectDir::Up;
			}
			// ���Ͱ� �ڽ��� �Ʒ���� 
			else if (m_TargetDir == EObjectDir::Down)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("CounterDownRight");
				m_Dir = EObjectDir::Down;
			}

			// �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
			if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
				|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
				m_MoveSpeed *= (3.f / 4.f);
		}

		// �ڿ������� ����
		if (m_CounterAttackTime > 0.f)
		{
			if (m_Dir==EObjectDir::LeftUp || m_Dir == EObjectDir::LeftDown || 
				m_Dir == EObjectDir::RightUp || m_Dir == EObjectDir::RightDown)
			{
				m_MoveSpeed -= 80000.f * DeltaTime;
			}
			else
				m_MoveSpeed -= 100000.f * DeltaTime;

			

			if (m_MoveSpeed < 0.f)
				m_MoveSpeed = 0.f;
		}

		m_CounterAttackTime -= DeltaTime;

		if (m_CounterAttackTime <= 0.f)
		{
			m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

			m_TargetDir = EObjectDir::None;

			
			m_Body->SetCollisionProfile("Object");

			m_CounterAttackTime = 0.f;
			m_MoveSpeed = 250.f;
			m_BlockTime = 0.f;
			m_UseSkill = EPlayerSkills::None;
			m_CounterAttack = false;
		}

		// ���� �ǰ� �̵� �κ� 
		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::Left:
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::Down:
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::Right:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::LeftUp:
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::LeftDown:
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::RightUp:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::RightDown:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		}	
	}
	// �ͽź��� �ߵ����� �� �̵� ���� 
	else if (m_GhostSlashTime > 0.f || m_GhostSlashReady || m_GhostSlashUsable > 0.f)
	{
		// �غ��ڼ��� ���������� 
		if (m_GhostSlashReady || (m_GhostSlashTime == 0.f && m_GhostSlashUsable > 0.f))
			return;

		// �ڽ��� ��ġ ��� ���� ��ġ�� ���Ͽ� �з��� ������ ���Ѵ�. 
		if (m_GhostSlashTime == 0.5f)
		{
			// Ű�� �ϴ� �����Ѵ�. �ڲ� �밢���⴩���鼭 ������
			ResetRightKey();
			ResetLeftKey();
			ResetUpKey();
			ResetDownKey();

			// ���� �̵��ӵ� 
			m_MoveSpeed = 10000.f;

			// ���Ͱ� �ڽ��� �����̶��
			if (m_TargetDir == EObjectDir::Left)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashLeft");
				m_Dir = EObjectDir::Left;
			}
			else if (m_TargetDir == EObjectDir::LeftUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashLeft");
				m_Dir = EObjectDir::LeftUp;
			}
			else if (m_TargetDir == EObjectDir::LeftDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashLeftDown");
				m_Dir = EObjectDir::LeftDown;
			}
			// ���Ͱ� �ڽ��� �������̶�� 
			else if (m_TargetDir == EObjectDir::Right)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashRight");
				m_Dir = EObjectDir::Right;
			}
			else if (m_TargetDir == EObjectDir::RightUp)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashRight");
				m_Dir = EObjectDir::RightUp;
			}
			else if (m_TargetDir == EObjectDir::RightDown)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashRightDown");
				m_Dir = EObjectDir::RightDown;
			}
			// ���Ͱ� �ڽ��� ����� 
			else if (m_TargetDir == EObjectDir::Up)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashUp");
				m_Dir = EObjectDir::Up;
			}
			// ���Ͱ� �ڽ��� �Ʒ���� 
			else if (m_TargetDir == EObjectDir::Down)
			{
				m_Sprite->GetAnimation()->ChangeAnimation("SlashRightDown");
				m_Dir = EObjectDir::Down;
			}

			// �밢���� �����Լ��� �ι� ȣ���ϹǷ� �̵��ӵ��� ���δ�.  
			if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::RightUp
				|| m_Dir == EObjectDir::LeftDown || m_Dir == EObjectDir::RightDown)
				m_MoveSpeed *= (3.f / 4.f);
		}

		// �ڿ������� ����
		if (m_GhostSlashTime > 0.f)
		{
			if (m_Dir == EObjectDir::LeftUp || m_Dir == EObjectDir::LeftDown ||
				m_Dir == EObjectDir::RightUp || m_Dir == EObjectDir::RightDown)
			{
				m_MoveSpeed -= 100000.f * DeltaTime;
			}
			else
				m_MoveSpeed -= 110000.f * DeltaTime;



			if (m_MoveSpeed < 0.f)
				m_MoveSpeed = 0.f;
		}

		m_GhostSlashTime -= DeltaTime;

		// �������� ����Ʈ : ������� �÷��̾ �������� �� ����ؾ� �ڿ������� ������ �̰����� �Ѵ�. 
		if (m_GhostSlashTime < 0.35 && m_GhostSlashSwipe)
		{
			m_GhostSlashSwipe = false;

			// �Ʒ��� �������� ����Ʈ

			CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerGhostSlash");

			CEffect* Effect = Afterimage->GetEffect();

			Effect->SetAnimation<CAnimation2D>("Effect");

			Effect->SetWorldPosition(GetWorldPos());

			// �÷��̾� ���⿡ ���� �� ����Ʈ�� ȸ���� �ʿ� 
			if (m_Dir == EObjectDir::Right)
			{
				Effect->AddWorldRotationZ(180.f);
				Effect->AddWorldPositionX(-250.f);
				Effect->AddWorldPositionY(20.f);
			}
			else if (m_Dir == EObjectDir::RightDown)
			{
				Effect->AddWorldRotationZ(135.f);
				Effect->AddWorldPositionX(-180.f);
				Effect->AddWorldPositionY(180.f);

			}
			else if (m_Dir == EObjectDir::Down)
			{
				Effect->AddWorldRotationZ(90.f);
				Effect->AddWorldPositionY(250.f);
			}
			else if (m_Dir == EObjectDir::LeftDown)
			{
				Effect->AddWorldRotationZ(45.f);
				Effect->AddWorldPositionX(180.f);
				Effect->AddWorldPositionY(180.f);

			}
			else if (m_Dir == EObjectDir::Left)
			{
				Effect->AddWorldRotationZ(0.f);
				Effect->AddWorldPositionX(250.f);
			}
			else if (m_Dir == EObjectDir::LeftUp)
			{
				Effect->AddWorldRotationZ(-45.f);
				Effect->AddWorldPositionX(180.f);
				Effect->AddWorldPositionY(-180.f);
			}
			else if (m_Dir == EObjectDir::Up)
			{
				Effect->AddWorldRotationZ(-90.f);
				Effect->AddWorldPositionY(-250.f);
			}
			else if (m_Dir == EObjectDir::RightUp)
			{
				Effect->AddWorldRotationZ(-135.f);
				Effect->AddWorldPositionX(-180.f);
				Effect->AddWorldPositionY(-180.f);

			}

			Effect->GetAnimation()->AddAnimation("GhostSlash", "GhostSlash", 0.15f);

			Effect->SetEffectType(EEffectType::Once);
		}
		

		if (m_GhostSlashTime <= 0.f)
		{
			//m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");

			m_TargetDir = EObjectDir::None;

			m_Body->SetCollisionProfile("Object");

			m_GhostSlashTime = 0.f;
			m_MoveSpeed = 250.f;
			m_BlockTime = 0.f;
			m_UseSkill = EPlayerSkills::None;
			m_Attack = false;
		}

		// ���� �ǰ� �̵� �κ� 
		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::Left:
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::Down:
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::Right:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::LeftUp:
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			break;
		case EObjectDir::LeftDown:
			m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::RightUp:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		case EObjectDir::RightDown:
			m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));
			break;
		}
	}
	else
	{
		// �̵����� ���ٸ� ����, �ִٸ� �������� �ٲ��ش�. 
		if (!m_Attack && !m_Dash && !m_Guard && !m_ObjectCollision)
		{
			if (m_Sprite->GetMove() != Vector3(0.f, 0.f, 0.f))
			{
				switch (m_Dir)
				{
				case EObjectDir::Up:
				case EObjectDir::LeftUp:
				case EObjectDir::RightUp:
					m_Sprite->GetAnimation()->ChangeAnimation("Running");
					break;
				case EObjectDir::Left:
					m_Sprite->GetAnimation()->ChangeAnimation("RunningLeft");
					break;
				case EObjectDir::Down:
				case EObjectDir::LeftDown:
				case EObjectDir::RightDown:
					m_Sprite->GetAnimation()->ChangeAnimation("RunningBack");
					break;
				case EObjectDir::Right:
					m_Sprite->GetAnimation()->ChangeAnimation("RunningRight");
					break;
				}
			}
			else
			{
				switch (m_Dir)
				{
				case EObjectDir::Up:
				case EObjectDir::LeftUp:
				case EObjectDir::RightUp:
					m_Sprite->GetAnimation()->ChangeAnimation("Stand");
					break;
				case EObjectDir::Left:
					m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");
					break;
				case EObjectDir::Down:
				case EObjectDir::LeftDown:
				case EObjectDir::RightDown:
					m_Sprite->GetAnimation()->ChangeAnimation("StandBack");
					break;
				case EObjectDir::Right:
					m_Sprite->GetAnimation()->ChangeAnimation("StandRight");
					break;
				}
			}
		}

		// ������ �ε巴�� �Ѵ�. 
		if (m_MoveAttack != 0.f)
		{
			if (m_DiagonalMove)
			{
				if (m_MoveAttack < 0.2f)
				{
					m_MoveSpeed -= 1800.f * DeltaTime;

					if (m_MoveSpeed < 0.f)
						m_MoveSpeed = 0.f;
				}
			}
			else if (m_MoveAttack < 0.15f)
			{
				m_MoveSpeed -= 2000.f * DeltaTime;

				if (m_MoveSpeed < 0.f)
					m_MoveSpeed = 0.f;
			}
		}
	}

	if (m_Dash)
	{
		if (m_DiagonalMove)
		{
			if (m_DashTime < 0.4)
			{
				// ���⼭ ��ŸŸ���� �ƴ� 5.f���� ���������� ���� �ȵ�. 
				// ���α׷� ���ſ����� �ε巴�� ���� �Ȱɸ��� ����
				m_MoveSpeed -= 10000.f * DeltaTime;

				if (m_MoveSpeed < 0.f)
					m_MoveSpeed = 0.f;
			}
		}
		else if (m_DashTime < 0.25)
		{
			// 0.25�ʵ��� 2500��ŭ �����Ѵٴ� �ǹ� 
			m_MoveSpeed -= 10000.f * DeltaTime;

			if (m_MoveSpeed < 0.f)
				m_MoveSpeed = 0.f;
		}
	}

	// ���� �̵���(�뽬 �̵���)�� �����ִٸ� 0�� �ɶ����� ������ ���� �������� �̵��Ѵ�. 
	// �ι�� �̵��Ǵ°��� �������� �̵� Ű�� �ȴ����� ��쿡��. 
	if (m_MoveAttack != 0.f || m_DashTime > 0.f)
	{
		switch (m_Dir)
		{
		case EObjectDir::Up:
			if (!m_PressUpKey)
			{
				m_AutoMove = true;
				MoveUp();
			}
			break;

		case EObjectDir::Left:
			if (!m_PressLeftKey)
			{
				m_AutoMove = true;
				RotationInv();
			}
			break;

		case EObjectDir::Down:
			if (!m_PressDownKey)
			{
				m_AutoMove = true;
				MoveDown();
			}
			break;

		case EObjectDir::Right:
			if (!m_PressRightKey)
			{
				m_AutoMove = true;
				Rotation();
			}
			break;

		case EObjectDir::LeftUp:
			if (!m_PressLeftKey)
			{
				m_AutoMove = true;
				RotationInv();
			}
			if (!m_PressUpKey)
			{
				m_AutoMove = true;
				MoveUp();
			}
			break;

		case EObjectDir::LeftDown:
			if (!m_PressLeftKey)
			{
				m_AutoMove = true;
				RotationInv();
			}
			if (!m_PressDownKey)
			{
				m_AutoMove = true;
				MoveDown();
			}
			break;

		case EObjectDir::RightUp:
			if (!m_PressRightKey)
			{
				m_AutoMove = true;
				Rotation();
			}
			if (!m_PressUpKey)
			{
				m_AutoMove = true;
				MoveUp();
			}
			break;
		case EObjectDir::RightDown:
			if (!m_PressRightKey)
			{
				m_AutoMove = true;
				Rotation();
			}
			if (!m_PressDownKey)
			{
				m_AutoMove = true;
				MoveDown();
			}
			break;
		}

	}
}

CPlayer2D* CPlayer2D::Clone() const
{
	return new CPlayer2D(*this);
}

void CPlayer2D::Save(FILE* File)
{
	CGameObject::Save(File);
}

void CPlayer2D::Load(FILE* File)
{
	CGameObject::Load(File);
}

EHitState CPlayer2D::InflictDamage(int Damage, int IsBoss)
{
    if (IsBoss)
    {
        switch (IsBoss)
        {
        case 1:
            m_HitTypeByBoss = EPlayerHitTypeByBoss::Punch;
            break;
        case 2:
            m_HitTypeByBoss = EPlayerHitTypeByBoss::Stomp;
            break;
        case 3:
            m_HitTypeByBoss = EPlayerHitTypeByBoss::Rush;
            break;
        default:
            break;
        }
    }
    else
        m_HitTypeByBoss = EPlayerHitTypeByBoss::None;

	if (m_Invincible != 0.f || m_CounterAttackTime != 0.f)
		return EHitState::Invincible;

	if (m_Guard)
	{
		// ����Ʈ ����
        // �������� ����Ʈ���� �Ұ��� 
		if (!m_JustGuard && m_JustGuardTime != 0.f && m_CounterAttackTime == 0.f && (m_HitTypeByBoss!=EPlayerHitTypeByBoss::Stomp))
		{
			// ��ũ�� ����Ʈ 
			CMainHUD* mainHUD = m_Scene->GetViewport()->FindUIWindow<CMainHUD>("MainHUD");
			mainHUD->OnScreenEffect(EScreenEffect::WhiteFlash);

			// ��Ȱ�� ������ ���� Body�� �浹���������� �Ͻ������� �����Ѵ�. 
			m_Body->SetCollisionProfile("Default");
		
			// �Ͼ������ �ٲٴ� �ð��� �߰���Ű�� ���� 
			m_JustGuardTime += 0.1f;

			// �����ð� 
			m_Invincible = 0.5f;

			// ī���;��� ���� �ð� 
			m_CounterTime = 0.5f;

			// 0.6�� ��� 
			m_BlockTime = 0.6;

			m_JustGuard = true;

            // ���뿡�� �޽��� ī��Ʈ?
            dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->SetJustGuardMessage();

			m_Scene->GetResource()->SoundPlay("JustGuard");

			// ����Ʈ���� ����Ʈ (�÷��̾� + ���) 
			CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerChain");

			CEffect* Effect = Afterimage->GetEffect();

			Effect->SetAnimation<CAnimation2D>("PlayerChain");

			Effect->SetWorldPosition(m_Sprite->GetWorldPos());
			Effect->AddWorldPosition(Vector3(-10.f, 40.f, 0.f));

			Effect->GetAnimation()->AddAnimation("JustGuardCircle", "PlayerJustGuardCircle", 0.25f);

			Effect->SetEffectType(EEffectType::Once);

			// ����Ʈ���� ����Ʈ2 (�÷��̾� + ���) 
			CEffect* Effect2 = CreateComponent<CEffect>("PlayerHitEffect");

			Effect->AddChild(Effect2);

			Effect2->SetAnimation<CAnimation2D>("PlayerChain2");

			Effect2->GetAnimation()->AddAnimation("JustGuardCircle2", "PlayerChain", 0.25f);

			Effect2->SetRelativePosition(0.f, 0.f);

			Effect2->SetEffectType(EEffectType::Once);

			CMaterial* Material1 = Effect2->GetMaterial(0);
			Material1->SetFullColorUnsignedChar(255, 255, 255, 0);
			Material1->SetOnlyColor(true);

			// ��뿡�� ����극��ũ ���¸� �����Ͽ� ���Ͽ� �ɸ��� �Ұ��̴�. 
			return EHitState::GuardBreak;
		}
		// �븻 ���� 
		else
		{
			// 0.6�� ��� 
			m_BlockTime = 0.6;

			int Random = (rand() % 2) + 1;

			if (Random == 1)
				m_Scene->GetResource()->SoundPlay("Guard1");
			else if (Random == 2)
				m_Scene->GetResource()->SoundPlay("Guard2");
		}

		return EHitState::Block;
	}

	// ī�޶� ���� (�ǰݽ� 0.1f, 20.f / Ÿ�� �� 0.05f, 20.f)
	m_Scene->GetCameraManager()->GetCurrentCamera()->FixCameraPos(0.1, Vector3(0.f, 20.f, 0.f));

	// ��ũ�� ����Ʈ 
	CMainHUD* mainHUD = m_Scene->GetViewport()->FindUIWindow<CMainHUD>("MainHUD");
	mainHUD->OnScreenEffect(EScreenEffect::RedHitBox);

	m_HitTime = 0.8f;
	
	// �ǰݴ��ϸ� ��� ������ �����. 
	m_Dash = false;
	m_Attack = false;
	m_AttackCount = 0;
	m_DoubleEdge = false;
	m_GhostSlashCount = 0;
	m_Chain = false;
	m_ChainTime = 0.f;
	m_UseSkill = EPlayerSkills::End;
	m_MoveAttack = 0.f;
	m_DashTime = 0.f;

	m_GhostSlashCount = 0;
	m_GhostSlashReady = false;
	m_GhostSlashTime = 0.f;
	m_GhostSlashUsable = 0.f;

	int Random = (rand() % 3) + 1;

	if (Random == 1)
		m_Scene->GetResource()->SoundPlay("Hit1");
	else if (Random == 2)
		m_Scene->GetResource()->SoundPlay("Hit2");
	else if (Random == 3)
		m_Scene->GetResource()->SoundPlay("Hit3");


	m_HP -= Damage;


	if (m_HP <= 0)
	{
		m_HP = 0;
		//Destroy();
	}

	// ���� ����Ʈ �׽�Ʈ 

	CBlood* Afterimage = GetScene()->CreateObject<CBlood>("MonsterBlood");

	CEffect* Effect = Afterimage->GetEffect();

	Afterimage->SetRootComponent(Effect);

	Effect->SetAnimation<CAnimation2D>("MonsterBlood");


	/*CBlood* Afterimage2 = GetScene()->CreateObject<CBlood>("MonsterBlood2");

	CEffect* Effect2 = Afterimage2->GetEffect();

	Effect2->SetAnimation<CAnimation2D>("MonsterBlood2");*/

	switch (m_EnemyDir)
	{
	case EObjectDir::Up:
	{
		Afterimage->SetDir(EObjectDir::Down);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(0.f, -30.f, 0.f));

		Effect->GetAnimation()->AddAnimation("BloodDown", "BloodDown", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(90.f, -30.f));
	}
	break;
	case EObjectDir::Left:
	{
		Afterimage->SetDir(EObjectDir::Right);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(50.f, 60.f, 0.f));
		Effect->AddWorldRotationZ(180.f);

		Effect->GetAnimation()->AddAnimation("BloodLeft", "BloodLeft", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(200.f, 40.f));
	}
	break;
	case EObjectDir::Down:
	{
		Afterimage->SetDir(EObjectDir::Up);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(0.f, 110.f, 0.f));
		Effect->AddWorldRotationZ(180.f);

		Effect->GetAnimation()->AddAnimation("BloodDown", "BloodDown", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(90.f, 180.f));
	}
	break;
	case EObjectDir::Right:
	{
		Afterimage->SetDir(EObjectDir::Left);

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-60.f, 50.f, 0.f));

		Effect->GetAnimation()->AddAnimation("BloodLeft", "BloodLeft", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(-20.f, 70.f));
	}
	break;
	case EObjectDir::LeftUp:
	{
		Afterimage->SetDir(EObjectDir::RightDown);

		// �Ϸ� 
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(55.f, -20.f, 0.f));
		Effect->AddWorldRotationZ(180.f);

		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(210.f, 10.f));
	}
	break;
	case EObjectDir::LeftDown:
	{
		Afterimage->SetDir(EObjectDir::RightUp);

		// �Ϸ�
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(65.f, 95.f, 0.f));
		Effect->AddWorldRotationZ(240.f);

		//Effect->GetAnimation()->AddAnimation("BloodLeftDown", "BloodLeftDown", 0.4f);
		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(150.f, 170.f));
	}
	break;
	case EObjectDir::RightUp:
	{
		Afterimage->SetDir(EObjectDir::LeftDown);

		// �Ϸ� 
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-55.f, -30.f, 0.f));
		Effect->AddWorldRotationZ(90.f);

		//Effect->GetAnimation()->AddAnimation("BloodLeftDown", "BloodLeftDown", 0.4f);
		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(-0.f, -10.f));
	}
	break;
	case EObjectDir::RightDown:
	{
		Afterimage->SetDir(EObjectDir::LeftUp);

		// �Ϸ� 
		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-65.f, 100.f, 0.f));

		Effect->GetAnimation()->AddAnimation("BloodLeftUp", "BloodLeftUp", 0.4f);

		Effect->SetEffectType(EEffectType::Once);

		Afterimage->CreateBloodArea(GetWorldPos(), Vector2(-0.f, 150.f));
	}
	break;
	}

	Afterimage->SetBloodLevel(EBloodLevel::Low);

	return EHitState::Normal;
}

void CPlayer2D::ResetUpKey()
{
	m_PressUpKey = false;
}

void CPlayer2D::ResetDownKey()
{
	m_PressDownKey = false;
}

void CPlayer2D::ResetRightKey()
{
	m_PressRightKey = false;
}

void CPlayer2D::ResetLeftKey()
{
	m_PressLeftKey = false;
}

void CPlayer2D::ResetAttackKey()
{
	m_PressAttackKey = false;
}

void CPlayer2D::ResetGuardKey()
{
	if (m_Guard)
	{
		/*
			����(�糯����)-������ ü���� ��� ���ÿ��尡 ȣ����� �ʱ� ������
			�̷��� ���ش�.
		*/
		m_Attack = false;
		m_DoubleEdge = false;
		m_Chain = false;

		// �￬�� �ִϸ��̼��� ������ �Դٸ� �޺��� ó������ �̾���� �� 
		m_AttackCount = 0;

		m_DashTime = 0.f;
		m_Dash = false;
		m_MoveSpeed = 250.f;
	}

	m_Guard = false;
}

void CPlayer2D::MoveUp()
{
	// �뽬 ����� ���乫�� ���¶�� ��ư�� ���� ������ �ƴϹǷ� 
	if (!m_AutoMove)
		m_PressUpKey = true;
	

	if (m_HitTime > 0.f || m_BlockTime > 0.f || m_CounterAttack || m_GhostSlashReady || (m_GhostSlashTime > 0.f && !m_Chain))
	{
		return;
	}

	// �뽬(�̵�����)�߿� ����, ������, �������� ������ �뽬(�̵�����)�� �ƴϸ� ���������� �̵��� �Ұ����ϴ�.
	if (!m_Chain && (m_Dash || m_MoveAttack != 0.f) && (m_Dir != EObjectDir::LeftUp && m_Dir != EObjectDir::RightUp && m_Dir != EObjectDir::Up))
		return;


	m_AutoMove = false;

	// ������ �����Ѵ� 
	// �뽬�߿��� ������ ���ٲ۴�.
	// �����߿��� ���ٲ۴�. 
	if (m_Chain || !m_Dash)
	{
		if (m_PressLeftKey)
			SetDir(EObjectDir::LeftUp);
		else if (m_PressRightKey)
			SetDir(EObjectDir::RightUp);
		else
			SetDir(EObjectDir::Up);
	}

	if (m_GhostSlashCount > 0)
		return;

	// �������̶�� �ִϸ��̼Ǹ� �ٲٰ� ����
	if (m_Guard || m_BlockTime != 0.f)
	{
		switch (m_Dir)
		{
		case EObjectDir::Up:
		case EObjectDir::LeftUp:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockUp");
			break;
		case EObjectDir::Left:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
		case EObjectDir::RightDown:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockDown");
			break;
		case EObjectDir::Right:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
			break;
		}
		return;
	}

	if (m_Dash)
	{
		// �뽬 ���̶��

		if (m_DashTime > 0.f)
		{
			m_DashTime -= g_DeltaTime;
			m_HitCollider->AddWorldPosition(Vector3(0.f, m_MoveSpeed * g_DeltaTime, 0.f));
			return;
		}

		m_DashTime = 0.f;

 		return;
	}

	// �̵� �� �����̶��
	if (m_MoveAttack > 0.f)
	{
		m_MoveAttack -= g_DeltaTime;

		if (m_MoveAttack < 0.f)
			m_MoveAttack = 0.f;

		m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed()* 2.f * g_DeltaTime, 0.f));

		return;
	}

	// �������̶�� ����
	if (m_Attack)
		return;

	m_HitCollider->AddWorldPosition(Vector3(0.f, GetMoveSpeed() * g_DeltaTime, 0.f));

	if (m_DiagonalMove)
		m_MoveSoundTime += (g_DeltaTime / 2);
	else
		m_MoveSoundTime += g_DeltaTime;

	if (m_MoveSoundTime > 0.4f)
	{
		m_Scene->GetResource()->SoundPlay("FootStep_Grass");
		m_MoveSoundTime = 0.f;
	}

	// m_HitCollider->AddWorldPosition(m_HitCollider->GetWorldAxis(AXIS_Y) * 300.f * g_DeltaTime);
}

void CPlayer2D::MoveDown()
{
	// �뽬 ����� ���乫�� ���¶�� ��ư�� ���� ������ �ƴϹǷ� 
	if (!m_AutoMove)
		m_PressDownKey = true;

	if (m_HitTime > 0.f || m_BlockTime > 0.f || m_CounterAttack || m_GhostSlashReady || (m_GhostSlashTime > 0.f && !m_Chain))
	{
		return;
	}

	// �뽬(�̵�����)�߿� �Ʒ���, ���ʾƷ�, �����ʾƷ� ������ �뽬(�̵�����)�� �ƴϸ� �Ʒ��������� �̵��� �Ұ����ϴ�.
	if (!m_Chain && (m_Dash || m_MoveAttack != 0.f) && (m_Dir != EObjectDir::LeftDown && m_Dir != EObjectDir::RightDown && m_Dir != EObjectDir::Down))
		return;

	

	m_AutoMove = false;

	if (m_Chain || !m_Dash)
	{
		if (m_PressLeftKey)
			SetDir(EObjectDir::LeftDown);
		else if (m_PressRightKey)
			SetDir(EObjectDir::RightDown);
		else
			SetDir(EObjectDir::Down);
	}
    
	if (m_GhostSlashCount > 0)
		return;

	// �������̶�� �ִϸ��̼Ǹ� �ٲٰ� ����
	if (m_Guard || m_BlockTime > 0.f)
	{
		switch (m_Dir)
		{
		case EObjectDir::Up:
		case EObjectDir::LeftUp:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockUp");
			break;
		case EObjectDir::Left:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
		case EObjectDir::RightDown:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockDown");
			break;
		case EObjectDir::Right:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
			break;
		}
		return;
	}

	if (m_Dash)
	{
		// �뽬 ���̶��

		if (m_DashTime > 0.f)
		{
			m_DashTime -= g_DeltaTime;
			m_HitCollider->AddWorldPosition(Vector3(0.f, -m_MoveSpeed * g_DeltaTime, 0.f));
			return;
		}

		m_DashTime = 0.f;

		return;
	}

	// �̵� �� �����̶��
	if (m_MoveAttack > 0.f)
	{
		m_MoveAttack -= g_DeltaTime;

		if (m_MoveAttack < 0.f)
			m_MoveAttack = 0.f;

		m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * 2.f * g_DeltaTime, 0.f));

		return;
	}

	// �������̶�� ����
	if (m_Attack)
		return;

	m_HitCollider->AddWorldPosition(Vector3(0.f, -GetMoveSpeed() * g_DeltaTime, 0.f));

	if (m_DiagonalMove)
		m_MoveSoundTime += (g_DeltaTime / 2);
	else
		m_MoveSoundTime += g_DeltaTime;

	if (m_MoveSoundTime > 0.4f)
	{
		m_Scene->GetResource()->SoundPlay("FootStep_Grass");
		m_MoveSoundTime = 0.f;
	}
	
	// m_HitCollider->AddWorldPosition(m_HitCollider->GetWorldAxis(AXIS_Y) * -300.f * g_DeltaTime);

}

// d
void CPlayer2D::Rotation()
{
	// �뽬 ����� ���乫�� ���¶�� ��ư�� ���� ������ �ƴϹǷ� 
	if (!m_AutoMove)
		m_PressRightKey = true;

	if (m_HitTime > 0.f || m_BlockTime > 0.f || m_CounterAttack || m_GhostSlashReady || (m_GhostSlashTime > 0.f && !m_Chain))
	{
		return;
	}

	// �뽬(�̵�����)�߿� ������, ��������, �����ʾƷ� ������ �뽬(�̵�����)�� �ƴϸ� ������������ �̵��� �Ұ����ϴ�.
	if (!m_Chain && (m_Dash || m_MoveAttack != 0.f) && (m_Dir != EObjectDir::Right && m_Dir != EObjectDir::RightUp && m_Dir != EObjectDir::RightDown))
		return;

	
	m_AutoMove = false;

	if (m_Chain || !m_Dash)
	{
		if (m_PressUpKey)
			SetDir(EObjectDir::RightUp);
		else if (m_PressDownKey)
			SetDir(EObjectDir::RightDown);
		else
			SetDir(EObjectDir::Right);
	}


	if (m_GhostSlashCount > 0)
		return;

	// �������̶�� �ִϸ��̼Ǹ� �ٲٰ� ����
	if (m_Guard || m_BlockTime > 0.f)
	{
		switch (m_Dir)
		{
		case EObjectDir::Up:
		case EObjectDir::LeftUp:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockUp");
			break;
		case EObjectDir::Left:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
		case EObjectDir::RightDown:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockDown");
			break;
		case EObjectDir::Right:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
			break;
		}
		return;
	}

	if (m_Dash)
	{
		// �뽬 ���̶��

		if (m_DashTime > 0.f)
		{
			m_DashTime -= g_DeltaTime;
			m_HitCollider->AddWorldPosition(Vector3(m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
			return;
		}

		m_DashTime = 0.f;

		return;
	}

	// �̵� �� �����̶��
	if (m_MoveAttack > 0.f)
	{
		m_MoveAttack -= g_DeltaTime;

		if (m_MoveAttack < 0.f)
			m_MoveAttack = 0.f;

		m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * 2.f * g_DeltaTime, 0.f, 0.f));

		return;
	}

	// �������̶�� ����
	if (m_Attack)
		return;

	m_HitCollider->AddWorldPosition(Vector3(GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));

	if (m_DiagonalMove)
		m_MoveSoundTime += (g_DeltaTime / 2);
	else
		m_MoveSoundTime += g_DeltaTime;

	if (m_MoveSoundTime > 0.4f)
	{
		m_Scene->GetResource()->SoundPlay("FootStep_Grass");
		m_MoveSoundTime = 0.f;
	}
	// m_HitCollider->AddWorldRotationZ(360.f * g_DeltaTime);
}

// a
void CPlayer2D::RotationInv()
{
	// �뽬 ����� ���乫�� ���¶�� ��ư�� ���� ������ �ƴϹǷ� 
	if (!m_AutoMove)
		m_PressLeftKey = true;

	if (m_HitTime > 0.f || m_BlockTime > 0.f || m_CounterAttack || m_GhostSlashReady || (m_GhostSlashTime > 0.f && !m_Chain))
	{
		return;
	}

	// �뽬(�̵�����)�߿� ����, ����, ���ʾƷ� ������ �뽬(�̵�����)�� �ƴϸ� ���������� �̵��� �Ұ����ϴ�.
	if (!m_Chain && (m_Dash || m_MoveAttack != 0.f) && (m_Dir != EObjectDir::Left && m_Dir != EObjectDir::LeftUp && m_Dir != EObjectDir::LeftDown))
		return;

	m_AutoMove = false;

	if (m_Chain || !m_Dash)
	{
		if (m_PressUpKey)
			SetDir(EObjectDir::LeftUp);
		else if (m_PressDownKey)
			SetDir(EObjectDir::LeftDown);
		else
			SetDir(EObjectDir::Left);
	}


	if (m_GhostSlashCount > 0)
		return;
	
	// �������̶�� �ִϸ��̼Ǹ� �ٲٰ� ����
	if (m_Guard || m_BlockTime > 0.f)
	{
		switch (m_Dir)
		{
		case EObjectDir::Up:
		case EObjectDir::LeftUp:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockUp");
			break;
		case EObjectDir::Left:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
		case EObjectDir::RightDown:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockDown");
			break;
		case EObjectDir::Right:
			m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
			break;
		}
		return;
	}

	if (m_Dash)
	{
		// �뽬 ���̶��

		if (m_DashTime > 0.f)
		{
			m_DashTime -= g_DeltaTime;
			m_HitCollider->AddWorldPosition(Vector3(-m_MoveSpeed * g_DeltaTime, 0.f, 0.f));
			return;
		}

		m_DashTime = 0.f;

		return;
	}

	if (m_MoveAttack > 0.f)
	{
		// �̵� �� �����̶��
		m_MoveAttack -= g_DeltaTime;

		if (m_MoveAttack < 0.f)
			m_MoveAttack = 0.f;

		m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * 2.f * g_DeltaTime, 0.f, 0.f));

		return;
	}

	// �������̶�� ����
	if (m_Attack)
		return;

	m_HitCollider->AddWorldPosition(Vector3(-GetMoveSpeed() * g_DeltaTime, 0.f, 0.f));

	if (m_DiagonalMove)
		m_MoveSoundTime += (g_DeltaTime / 2);
	else
		m_MoveSoundTime += g_DeltaTime;

	if (m_MoveSoundTime > 0.4f)
	{
		m_Scene->GetResource()->SoundPlay("FootStep_Grass");
		m_MoveSoundTime = 0.f;
	}
	// m_HitCollider->AddWorldRotationZ(-360.f * g_DeltaTime);
}

void CPlayer2D::Fire()
{
    //m_Scene->CleanMonster();

	// �ͽź��� ���� ü�� ������ ��� 
	if (m_GhostSlashCount > 0 || m_UseSkill == EPlayerSkills::GhostSlash)
	{
		if (!m_Chain)
			return;

		m_UseSkill = EPlayerSkills::None;

		m_GhostSlashCount = 0;
		m_GhostSlashTime = 0.f;
		m_GhostSlashReady = false;
		m_GhostSlashUsable = 0.f;
		m_Attack = false;
		
	}

	// ī���� ���� ���� ��Ȳ�� ��� 
	if (m_CounterTime != 0.f && !m_CounterAttack)
	{
        // ���뿡�� �޽��� ī��Ʈ?
        dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->SetCounterMessage();

		m_CounterAttack = true;

		// ���Ÿ������ �����ִ½ð��� ���ش�
		m_BlockTime = 0.f;
		m_HitTime = 0.f;

		m_PressDownKeyForGhostMove = false;
		m_PressUpKeyForGhostMove = false;
		m_PressRightKeyForGhostMove = false;
		m_PressLeftKeyForGhostMove = false;

		//// ��Ȱ�� ������ ���� Body�� �浹���������� �Ͻ������� �����Ѵ�. 
		m_Body->SetCollisionProfile("Default");

		// ���� ���� �浹ü�� �����Ѵ�. 
		m_AttackSingleCollider = CreateComponent<CColliderBox2D>("PlayerAttackSingle1");

		m_HitCollider->AddChild(m_AttackSingleCollider);

		m_AttackSingleCollider->SetCollisionProfile("Single");
		m_AttackSingleCollider->SetCollisionCallback<CPlayer2D>(ECollision_Result::Collision, this, &CPlayer2D::CollisionBeginAttack);

		m_AttackSingleCollider->SetBoxSize(400.f, 400.f);

		// ���� �ð��� �����ش�. 
		m_CounterAttackTime = 0.7f;

		m_CounterTime = 0.f;

		m_UseSkill = EPlayerSkills::CounterAttack;

		return;
	}

	if (m_HitTime > 0.f || m_BlockTime > 0.f || m_CounterAttackTime > 0.f)
		return;

	// ���� Ű�� ������
	m_PressAttackKey = true;

	// ����Ÿ���� 0.4�ʰ� �Ѿ��ٸ� �ִϸ��̼��� ������ ���� �￬Ÿ�� �̾�� �� �ֵ��� 
	// ���û��¸� false�� �ٲ� ������ �����ϰ� �Ѵ�.
	// ��, 3Ÿ �̻��� ���̻� ������ �̾���� �ȵǹǷ� �����Ѵ�. 
	if (0.35f <= m_AttackTime && 3 != m_AttackCount)
	{
		m_Attack = false;
		m_AttackTime = 0.f;
	}

	if (m_AttackCount == 3 && m_AttackTime != 0.f)
		return;

	// �������̰ų� or �뽬�������� ü���� �ƴ϶�� ���� 5
	if ((m_Guard || m_Attack || m_Dash) && !m_Chain)
	{
		// �糯���� ���϶� ü���� �����ϵ���
		if (!(m_Attack && m_DoubleEdge && m_Chain))
		{
			return;
		}

		/*if (m_Dash && !m_Chain)
			return;*/

		m_DoubleEdge = false;

		// ����
		m_Attack = false;
	
	}
		

	if (m_DiagonalMove)
		m_MoveSpeed = 300.f;
	else
		m_MoveSpeed = 250.f;

	// �뽬-���� ü�ο��� 3��Ÿ ������ �ϱ����� �뽬���¸� ���ش�. 
	if (m_Dash)
	{
		m_DashTime = 0.f;
		m_Dash = false;
		SetMoveSpeed(250.f);

		// ����ī��Ʈ�� �ʱ�ȭ���� ü�� �� ó������ ��Ÿ�� �̾�� �Ѵ�. 
		m_AttackCount = 0;
	}

	// ü���ϰ�� 
	if (m_Chain && m_AttackCount == 0)
	{
        // ��.. ���뿡�� �޽��� ī��Ʈ? 
        dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->AddChainCount();

		// ü�� ����Ʈ�� ����ش�. 
		CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerChain");

		CEffect* Effect = Afterimage->GetEffect();

		Effect->SetAnimation<CAnimation2D>("PlayerChain");

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-10.f, 40.f, 0.f));

		Effect->GetAnimation()->AddAnimation("Chain", "PlayerChain", 0.3f);
		
		Effect->SetEffectType(EEffectType::Once);	
	}

	// �̵� Ű�� ���� ���¶��
	if (m_PressUpKey || m_PressDownKey || m_PressRightKey || m_PressLeftKey)
		m_MoveAttack = 0.2f;

	m_UseSkill = EPlayerSkills::ThreeSequenceSlash;

	m_Attack = true;

	// 3Ÿ�� �Ǿ��ٸ� �ٽ� 1Ÿ���� �ϵ��� ���� 
	if (3 <= m_AttackCount)
	{
		m_AttackCount = 0;
	}
	

	EObjectDir Dir = GetDir();

	switch (m_AttackCount)
	{
	case 0:
		switch (Dir)
		{
		case EObjectDir::Up:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack1Up");
			break;
		case EObjectDir::Left:
		case EObjectDir::LeftUp:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack1Left");
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack1Down");
			break;
		case EObjectDir::Right:
		case EObjectDir::RightDown:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack1Right");
			break;
		}
		break;
	case 1:
		switch (Dir)
		{
		case EObjectDir::Up:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack2Up");
			break;
		case EObjectDir::Left:
		case EObjectDir::LeftUp:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack2Left");
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack2Down");
			break;
		case EObjectDir::Right:
		case EObjectDir::RightDown:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack2Right");
			break;
		}
		break;
	case 2:
		switch (Dir)
		{
		case EObjectDir::Up:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack3Up");
			break;
		case EObjectDir::Left:
		case EObjectDir::LeftUp:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack3Left");
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack3Down");
			break;
		case EObjectDir::Right:
		case EObjectDir::RightDown:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("Attack3Right");
			break;
		}
		break;
	}
	
	// �̰� ������ ��� �����Ҷ� ���δ�. 
	if (m_AttackCount == 0)
		m_AttackTime = 0.f;

	// �￬�� ī��Ʈ ����
	if(m_AttackTime == 0.f)
		++m_AttackCount;

	/*CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

	Bullet->SetWorldPosition(GetWorldPos());
	Bullet->SetWorldRotation(GetWorldRot());
	Bullet->SetCollisionProfileName("PlayerAttack");*/
}

void CPlayer2D::MoveClick()
{
	const Vector2&	MousePos = CInput::GetInst()->GetMouseWorldPos();

	/*if (m_NavAgent)
		m_NavAgent->Move(MousePos);*/
}

void CPlayer2D::Dash()
{
	if (m_UseSkill != EPlayerSkills::GhostMove)
	{
		if (m_HitTime > 0.f || m_BlockTime > 0.f || m_CounterAttackTime > 0.f)
			return;

		// ����Ű ������ �ʾ����� �뽬 ���� / ��, �ͽ� �޸��Ⱑ �ߵ��Ǿ��� ��� ����, �� ���� ������ �����ٰ� ���ϴϱ� (��ƮŸ�ӿ� ���� Ű �Է��� �������Ƿ� )
		if (!m_PressUpKey && !m_PressDownKey && !m_PressRightKey && !m_PressLeftKey)
			return;

		m_UseSkill = EPlayerSkills::End;

		// �������̰ų� �̹� �뽬���̶�� �뽬 ���ϰ� 
		if (m_Attack || m_Dash)
		{
			// + ü�� ���°� �ƴ϶�� �뽬 ���ϰ� 
			if (!m_Chain)
				return;

		}
	}

	// �ͽź��� ���� ü�� ������ ��� 
	if (m_GhostSlashCount > 0)
	{
		if (!m_Chain)
			return;

		m_GhostSlashCount = 0;
		m_GhostSlashTime = 0.f;
		m_GhostSlashReady = false;
		m_GhostSlashUsable = 0.f;
	}

	m_DoubleEdge = false;
	m_Attack = false;
	m_AttackTime = 0.f;
	m_AttackCount = 0;
	
	m_Scene->GetResource()->SoundPlay("Dash");

	if (m_Chain)
	{
        // ��.. ���뿡�� �޽��� ī��Ʈ? 
        dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->AddChainCount();

		/*
			�뽬-�뽬�� ü�ο��� ���� �뽬 �ִϸ��̼������� ��ȯ�� �Ұ����ϹǷ�
			�ٸ� �ִϸ��̼����� ��� �����ش�.
		*/
		m_Sprite->GetAnimation()->ChangeAnimation("Stand");

		// ü�� ����Ʈ�� ����ش�. 
		CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerChain");

		CEffect* Effect = Afterimage->GetEffect();

		Effect->SetAnimation<CAnimation2D>("PlayerChain");

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-10.f, 40.f, 0.f));

		Effect->GetAnimation()->AddAnimation("Chain", "PlayerChain", 0.3f);

		Effect->SetEffectType(EEffectType::Once);
	}

	m_Chain = false;
	m_ChainTime = 0.f;

	m_Dash = true;
	
	if (m_DiagonalMove)
	{
		m_MoveSpeed = 2200.f;
		m_DashTime = 0.45f;
	}
	else
	{
		m_MoveSpeed = 2500.f;
		m_DashTime = 0.3f;
	}

	switch (m_Dir)
	{
	case EObjectDir::Up:
	case EObjectDir::RightUp:
	case EObjectDir::LeftUp:
		m_Sprite->GetAnimation()->ChangeAnimation("DashUp");
		break;
	case EObjectDir::Left:
		m_Sprite->GetAnimation()->ChangeAnimation("DashLeft");
		break;
	case EObjectDir::Down:
	case EObjectDir::RightDown:
	case EObjectDir::LeftDown:
		m_Sprite->GetAnimation()->ChangeAnimation("DashDown");
		break;
	case EObjectDir::Right:
		m_Sprite->GetAnimation()->ChangeAnimation("DashRight");
		break;
	}
}

void CPlayer2D::Guard()
{
	if (m_HitTime > 0.f || m_BlockTime > 0.f || m_CounterAttackTime > 0.f)
		return;

	// �������̰ų� �̹� �뽬���̶�� ���� ���ϰ� 
	if (m_Attack || m_Dash)
	{
		// + ü�� ���°� �ƴ϶�� ���� ���ϰ� (�׷��� ����/�뽬���̾ ü�λ��¶�� ����)
		if (!m_Chain)
			return;
	}

	// �ͽź��� ���� ü�� ������ ��� 
	if (m_GhostSlashCount > 0)
	{
		if (!m_Chain)
			return;

		m_GhostSlashCount = 0;
		m_GhostSlashTime = 0.f;
		m_GhostSlashReady = false;
		m_GhostSlashUsable = 0.f;
	}

	m_Guard = true;

	m_JustGuardTime = 0.2f;

	m_Scene->GetResource()->SoundPlay("GuardStart");

	if (m_Chain)
	{
        // ��.. ���뿡�� �޽��� ī��Ʈ? 
        dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->AddChainCount();

		// ü�� ����Ʈ�� ����ش�. 
		CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerChain");

		CEffect* Effect = Afterimage->GetEffect();

		Effect->SetAnimation<CAnimation2D>("PlayerChain");

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-10.f, 40.f, 0.f));

		Effect->GetAnimation()->AddAnimation("Chain", "PlayerChain", 0.3f);

		Effect->SetEffectType(EEffectType::Once);
	}

	m_Chain = false;
	m_ChainTime = 0.f;

	switch (m_Dir)
	{
	case EObjectDir::Up:
	case EObjectDir::LeftUp:
	case EObjectDir::RightUp:
		m_Sprite->GetAnimation()->ChangeAnimation("BlockUp");
		break;
	case EObjectDir::Left:
		m_Sprite->GetAnimation()->ChangeAnimation("BlockLeft");
		break;
	case EObjectDir::Down:
	case EObjectDir::LeftDown:
	case EObjectDir::RightDown:
		m_Sprite->GetAnimation()->ChangeAnimation("BlockDown");
		break;
	case EObjectDir::Right:
		m_Sprite->GetAnimation()->ChangeAnimation("BlockRight");
		break;
	}
}

void CPlayer2D::DoubleEdge_Pre()
{
	if (m_HitTime > 0.f || m_BlockTime > 0.f || (m_Guard && !m_Chain) || m_CounterAttackTime > 0.f)
		return;

	if (m_Dash && !m_Chain)
		return;

	// �뽬 - �糯���� ü�ο��� �̵��� �����ϰ� �ϱ�����
	m_Dash = false;

	// ������������ ü���� �ƴϰų� or �뽬�������� ü���� �ƴ϶�� ���� 
	// + �糯���� ���� ü���� �Ұ����ϴ�. 
	if (m_Attack && !m_Chain || m_Dash && !m_Chain || m_DoubleEdge)
	{
		return;
	}

	// �ͽź��� ���� ü�� ������ ��� 
	if (m_GhostSlashCount > 0)
	{
		if (!m_Chain)
			return;

		m_GhostSlashCount = 0;
		m_GhostSlashTime = 0.f;
		m_GhostSlashReady = false;
		m_GhostSlashUsable = 0.f;
		m_Attack = false;
	}

	// ü���ϰ�� 
	if (m_Chain)
	{
        // ��.. ���뿡�� �޽��� ī��Ʈ? 
        dynamic_cast<CMainSceneInfo*>(GetScene()->GetSceneInfo())->AddChainCount();

		// ü�� ����Ʈ�� ����ش�. 
		CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerChain");

		CEffect* Effect = Afterimage->GetEffect();

		Effect->SetAnimation<CAnimation2D>("PlayerChain");

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());
		Effect->AddWorldPosition(Vector3(-10.f, 40.f, 0.f));

		Effect->GetAnimation()->AddAnimation("Chain", "PlayerChain", 0.3f);

		Effect->SetEffectType(EEffectType::Once);
	}

	m_UseSkill = EPlayerSkills::DoubleEdge;

	m_AttackCount = 0;
	m_AttackTime = 0.f;
	m_Attack = true;
	m_DoubleEdge = true;
	m_Chain = false;

	switch (m_Dir)
	{
	case EObjectDir::Up:
	case EObjectDir::RightUp:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeUp_Pre");
		break;
	case EObjectDir::Left:
	case EObjectDir::LeftUp:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeLeft_Pre");
		break;
	case EObjectDir::Down:
	case EObjectDir::LeftDown:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeDown_Pre");
		break;
	case EObjectDir::Right:
	case EObjectDir::RightDown:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeRight_Pre");
		break;
	}

	// �ٴ� ���� ����Ʈ�� ����ش�. 
	CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerCircleDust");

	CEffect* Effect = Afterimage->GetEffect();

	Effect->SetAnimation<CAnimation2D>("PlayerCircleDust");

	Effect->SetWorldPosition(m_Sprite->GetWorldPos());

	switch (m_Dir)
	{
	case EObjectDir::Up:
	case EObjectDir::RightUp:
		Effect->AddWorldPosition(Vector3(5.f, -17.f, 0.f));
		break;
	case EObjectDir::Left:
	case EObjectDir::LeftUp:
		Effect->AddWorldPosition(Vector3(-5.f, -17.f, 0.f));
		break;
	case EObjectDir::Down:
	case EObjectDir::LeftDown:
		Effect->AddWorldPosition(Vector3(-5.f, -17.f, 0.f));
		break;
	case EObjectDir::Right:
	case EObjectDir::RightDown:
		Effect->AddWorldPosition(Vector3(10.f, -17.f, 0.f));
		break;
	}

	Effect->GetAnimation()->AddAnimation("CircleDust", "PlayerCircleDust", 0.25f);

	Effect->SetEffectType(EEffectType::Once);

	m_Scene->GetResource()->SoundPlay("GuardStart");

	// Į�� �� ����Ʈ�� ����ش�. 
	/*CAfterimage* Afterimage1 = GetScene()->CreateObject<CAfterimage>("PlayerKiBackground");
	CEffect* Effect1 = Afterimage1->GetEffect();
	Effect1->SetAnimation<CAnimation2D>("PlayerKiBackground");
	Effect1->SetWorldPosition(m_Sprite->GetWorldPos());
	Effect1->GetAnimation()->AddAnimation("KiBackground", "PlayerKiBackground", 10.25f);
	Effect1->SetEffectType(EEffectType::Once);*/

	/*CEffect* Effect2 = Afterimage->GetEffect();
	Effect1->AddChild(Effect2);
	Effect2->SetAnimation<CAnimation2D>("PlayerKi");
	Effect2->SetWorldPosition(m_Sprite->GetWorldPos());
	Effect2->GetAnimation()->AddAnimation("Ki", "PlayerKi", 0.25f);
	Effect2->SetEffectType(EEffectType::Once);*/

	/*switch (m_Dir)
	{
	case EObjectDir::Up:
		Effect1->AddWorldPosition(Vector3(5.f, 17.f, 0.f));
		break;
	case EObjectDir::Left:
		Effect1->AddWorldPosition(Vector3(-5.f, 17.f, 0.f));
		break;
	case EObjectDir::Down:
		Effect1->AddWorldPosition(Vector3(-5.f, 17.f, 0.f));
		break;
	case EObjectDir::Right:
		Effect1->AddWorldPosition(Vector3(10.f, 17.f, 0.f));
		break;
	}*/
}

void CPlayer2D::DoubleEdge()
{
	if (m_DiagonalMove)
	{
		m_MoveSpeed = 485.f;
		m_MoveAttack = 0.45f;
	}
	else
	{
		m_MoveSpeed = 450.f;
		m_MoveAttack = 0.35f;
	}


	switch (m_Dir)
	{
	case EObjectDir::Up:
	case EObjectDir::RightUp:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeUp");
		break;
	case EObjectDir::Left:
	case EObjectDir::LeftUp:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeLeft");
		break;
	case EObjectDir::Down:
	case EObjectDir::LeftDown:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeDown");
		break;
	case EObjectDir::Right:
	case EObjectDir::RightDown:
		m_Sprite->GetAnimation()->ChangeAnimation("DoubleEdgeRight");
		break;
	}
}

void CPlayer2D::GhostMove()
{
	// �ǰ� ������ �ƴϸ� ��� �Ұ� / ����Ű �ȴ����� ��� �Ұ� 
	if (m_HitTime == 0.f || (!m_PressDownKey && !m_PressUpKey && !m_PressLeftKey && !m_PressRightKey))
		return;

	// ��ũ�� ����Ʈ 
	CMainHUD* mainHUD = m_Scene->GetViewport()->FindUIWindow<CMainHUD>("MainHUD");
	mainHUD->OnScreenEffect(EScreenEffect::WhiteFlash);

	// ��Ȱ�� Ż���� ����
	m_Body->SetCollisionProfile("Default");

	m_Invincible = 0.25f;

	// �ٲ���� �뽬 ����� �����ϰ�, ��Ʈ������ ��Ÿ�� �Ұ���
	m_HitTime = 0.f;


	// �����ִ� Ű�� ���� ���� ������ �ٲ������
	// �ȱ׷��� �ǰ� �������� ��Ʈ���갡 ����
	if (m_PressUpKey)
	{
		if (m_PressLeftKey)
			SetDir(EObjectDir::LeftUp);
		else if (m_PressRightKey)
			SetDir(EObjectDir::RightUp);
		else
			SetDir(EObjectDir::Up);
	}
	else if (m_PressDownKey)
	{
		if (m_PressLeftKey)
			SetDir(EObjectDir::LeftDown);
		else if (m_PressRightKey)
			SetDir(EObjectDir::RightDown);
		else
			SetDir(EObjectDir::Down);
	}
	else if(m_PressLeftKey)
		SetDir(EObjectDir::Left);
	else
		SetDir(EObjectDir::Right);

	// �뽬�� ��Ȱ�� 
	Dash();

	// �ͽ� �޸��� ����Ʈ 
	CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("GhostMoveCircle");

	Afterimage->SetLifeTime(1.f);

	CEffect* Effect = CreateComponent<CEffect>("GhostMoveEffect");

	Afterimage->SetRootComponent(Effect);

	Effect->SetAnimation<CAnimation2D>("PlayerGhostMoveCircle");

	Effect->SetWorldPosition(GetWorldPos());

	Effect->GetAnimation()->AddAnimation("GhostMoveCircle", "PlayerChain", 0.25f);

	Effect->SetEffectType(EEffectType::Once);

	CMaterial* Material = Effect->GetMaterial(0);
	Material->SetFullColorUnsignedChar(183, 240, 177, 0);
	Material->SetOnlyColor(true);


	// �ͽ� �޸��� ����
	m_Scene->GetResource()->SoundPlay("GhostMove");
}

void CPlayer2D::GhostSlash()
{
	// �°��ְų�, �����ְų�, ī���;��� �����̸� ��� �Ұ� 
	if (m_HitTime > 0.f || m_BlockTime > 0.f || (m_Guard && !m_Chain) || m_CounterAttackTime > 0.f)
		return;

	if (m_Dash && !m_Chain)
		return;

	// �̹� �ͽź������̶�� ��� ���ϵ��� but ü�� ���¿����� ���� 
	// �￬�����ε� ü���� �ƴϸ� ���� 
	if (m_GhostSlashTime != 0.f || m_DoubleEdge || m_AttackCount > 0)
	{
		if (!m_Chain)
			return;
	}

	

	m_DoubleEdge = false;
	m_Dash = false;
	m_Chain = false;
	m_ChainTime = 0.f;
	
	// �����ݰ��õ� �ʱ�ȭ
	m_AttackTime = 0.f;
	m_AttackCount = 0;

	// �غ� 
	if (m_GhostSlashCount == 0)
	{
		++m_GhostSlashCount;

		m_GhostSlashReady = true;

		m_GhostSlashSwipe = true;

		// ���� ���⿡ �´� �غ��ڼ��� ����. 
		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashReadyUp");
			break;
		case EObjectDir::Left:
		case EObjectDir::LeftUp:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashReadyLeft");
			break;
		case EObjectDir::LeftDown:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashReadyLeftDown");
			break;
		case EObjectDir::Right:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashReadyRight");
			break;
		case EObjectDir::RightDown:
		case EObjectDir::Down:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashReadyRightDown");
		}


		// �߹� ���� ����Ʈ
		CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerCircleDust");

		CEffect* Effect = Afterimage->GetEffect();

		Effect->SetAnimation<CAnimation2D>("PlayerCircleDust");

		Effect->SetWorldPosition(m_Sprite->GetWorldPos());

		switch (m_Dir)
		{
		case EObjectDir::Up:
		case EObjectDir::RightUp:
			Effect->AddWorldPosition(Vector3(5.f, -17.f, 0.f));
			break;
		case EObjectDir::Left:
		case EObjectDir::LeftUp:
			Effect->AddWorldPosition(Vector3(-5.f, -17.f, 0.f));
			break;
		case EObjectDir::Down:
		case EObjectDir::LeftDown:
			Effect->AddWorldPosition(Vector3(-5.f, -17.f, 0.f));
			break;
		case EObjectDir::Right:
		case EObjectDir::RightDown:
			Effect->AddWorldPosition(Vector3(10.f, -17.f, 0.f));
			break;
		}

		Effect->GetAnimation()->AddAnimation("CircleDust", "PlayerCircleDust", 0.25f);

		Effect->SetEffectType(EEffectType::Once);


		// �غ� ����
		m_Scene->GetResource()->SoundPlay("GhostSlashReady");
	}
	// �غ� �ִϸ��̼��� End �Լ��� ���� ������ �̰����� ���´�. 
	// 1Ÿ - 4Ÿ
	else if (m_GhostSlashCount >= 1 && m_GhostSlashCount <= 4)
	{
		m_GhostSlashSwipe = true;

		m_GhostSlashReady = false;

		m_UseSkill = EPlayerSkills::GhostSlash;

		++m_GhostSlashCount;

		m_GhostSlashTime = 0.5;

		// 1Ÿ
		// �� ������ Attack�� ȣ���ϸ� �浹ü�� �����Ѵ� 
		// ���� ���� Ÿ���� 1�ʷ� �����Ͽ�, �ش� �ð� �ȿ� wŰ�� ���Է��� ������ �ͽź��⸦ �ߴ��Ѵ� (ù��° ������ ������ �Ѵ�)
			// ������Ʈ���� ī��Ʈ�� 0���� ����� �ȴ�. 
		// �ͽź�����ð��� ��������, ������Ʈ���� �ش� �ð���ŭ ������ �ϵ��� �Ѵ�. 
		// �ͽź��� �ִϸ��̼��� ����Ѵ�. 
		// �� Ÿ���� ������ �ִϸ��̼��� ���������� �����־�� �Ѵ�. 5Ÿ���� �Ϸ��ϰų� ���Է��� ���� ��쿡�� ���ƿ´�. 

		// ����
		m_GhostSlashUsable = 1.5f;

		// ���� ���⿡ �´� �����ڼ��� ����. 
		m_Sprite->GetAnimation()->ChangeAnimation("StandLeft");
		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashUp");
			break;
		case EObjectDir::Left:
		case EObjectDir::LeftUp:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashLeft");
			break;
		case EObjectDir::LeftDown:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashLeftDown");
			break;
		case EObjectDir::Right:
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashRight");
			break;
		case EObjectDir::RightDown:
		case EObjectDir::Down:
			m_Sprite->GetAnimation()->ChangeAnimation("SlashRightDown");
		}

	}
	else if (m_GhostSlashCount == 5)
	{
		AttackEnd();
		//m_GhostSlashTime = 0.f;
		m_GhostSlashCount = 0;
		m_GhostSlashUsable = 0.f;
		m_UseSkill = EPlayerSkills::None;
	}

	
}

void CPlayer2D::ChainInactive()
{
	m_Chain = false; 
	m_ChainTime = 0.f;
}

void CPlayer2D::ChainActive()
{
	m_Body->SetCollisionProfile("Object");	// �̰� ���ϸ� �ͽź���-���� ü�ο��� �浹�ȵ�
	m_Chain = true;
	m_ChainTime = 0.f;
}

void CPlayer2D::Attack()
{
	if(m_AttackCollider)
		m_AttackCollider->Destroy();

	m_AttackCollider = CreateComponent<CColliderBox2D>("PlayerAttack1");
	
	m_HitCollider->AddChild(m_AttackCollider);

	m_AttackCollider->SetCollisionProfile("PlayerAttack");
	m_AttackCollider->SetCollisionCallback<CPlayer2D>(ECollision_Result::Collision, this, &CPlayer2D::CollisionBeginAttack);
	

	if (m_UseSkill == EPlayerSkills::ThreeSequenceSlash)
	{
		if(m_AttackCount == 3)
			m_Scene->GetResource()->SoundPlay("BigSwing");
		else
			m_Scene->GetResource()->SoundPlay("NormalSwing");

		switch (m_Dir)
		{
		case EObjectDir::Up:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(90.f, 110.f);
				m_AttackCollider->SetRelativePosition(15.f, 55.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(120.f, 80.f);
				m_AttackCollider->SetRelativePosition(0.f, 35.f);
			}
			break;
		case EObjectDir::Left:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(60.f, 120.f);
				m_AttackCollider->SetRelativePosition(-55.f, 0.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(100.f, 100.f);
				m_AttackCollider->SetRelativePosition(-60.f, -20.f);
			}
			break;
		case EObjectDir::Down:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(80.f, 120.f);
				m_AttackCollider->SetRelativePosition(0.f, -75.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(120.f, 60.f);
				m_AttackCollider->SetRelativePosition(0.f, -55.f);
			}
			break;
		case EObjectDir::Right:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(90.f, 120.f);
				m_AttackCollider->SetRelativePosition(50.f, 0.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(90.f, 100.f);
				m_AttackCollider->SetRelativePosition(45.f, -20.f);
			}
			break;
		case EObjectDir::LeftUp:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(110.f, 120.f);
				m_AttackCollider->SetRelativePosition(-55.f, 30.f);
			}
			else if (m_AttackCount == 2)
			{
				m_AttackCollider->SetBoxSize(70.f, 110.f);
				m_AttackCollider->SetRelativePosition(-55.f, 0.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(100.f, 100.f);
				m_AttackCollider->SetRelativePosition(-55.f, 30.f);
			}
			break;
		case EObjectDir::LeftDown:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(80.f, 120.f);
				m_AttackCollider->SetRelativePosition(0.f, -75.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(120.f, 60.f);
				m_AttackCollider->SetRelativePosition(0.f, -55.f);
			}
			break;
		case EObjectDir::RightUp:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(120.f, 120.f);
				m_AttackCollider->SetRelativePosition(50.f, 20.f);
			}
			else if (m_AttackCount == 2)
			{
				m_AttackCollider->SetBoxSize(120.f, 120.f);
				m_AttackCollider->SetRelativePosition(15.f, 15.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(110.f, 90.f);
				m_AttackCollider->SetRelativePosition(35.f, 20.f);
			}
			break;
		case EObjectDir::RightDown:
			if (m_AttackCount == 3)
			{
				m_AttackCollider->SetBoxSize(90.f, 120.f);
				m_AttackCollider->SetRelativePosition(50.f, -20.f);
			}
			else
			{
				m_AttackCollider->SetBoxSize(90.f, 100.f);
				m_AttackCollider->SetRelativePosition(45.f, -30.f);
			}
			break;
		}
	}
	else if (m_UseSkill == EPlayerSkills::DoubleEdge)
	{
		m_Scene->GetResource()->SoundPlay("DoubleEdgeSwing");

		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(0.f, 20.f);
			break;
		case EObjectDir::RightUp:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(30.f, 20.f);
			break;
		case EObjectDir::LeftUp:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(-30.f, 20.f);
			break;
		case EObjectDir::Left:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(-40.f, 0.f);
			break;
		case EObjectDir::Down:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(0.f, -60.f);
			break;
		case EObjectDir::RightDown:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(30.f, -60.f);
			break;
		case EObjectDir::LeftDown:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(-30.f, -60.f);
			break;
		case EObjectDir::Right:
			m_AttackCollider->SetBoxSize(160.f, 120.f);
			m_AttackCollider->SetRelativePosition(30.f, -30.f);
			break;
		}
	}
	else if (m_UseSkill == EPlayerSkills::DashAttack)
	{
		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_AttackCollider->SetBoxSize(90.f, 150.f);
			m_AttackCollider->SetRelativePosition(0.f, 40.f);
			break;
		case EObjectDir::LeftUp:
			m_AttackCollider->SetBoxSize(110.f, 130.f);
			m_AttackCollider->SetRelativePosition(-50.f, 40.f);
			break;
		case EObjectDir::RightUp:
			m_AttackCollider->SetBoxSize(110.f, 130.f);
			m_AttackCollider->SetRelativePosition(50.f, 40.f);
			break;
		case EObjectDir::Left:
			m_AttackCollider->SetBoxSize(170.f, 90.f);
			m_AttackCollider->SetRelativePosition(-60.f, -10.f);
			break;
		case EObjectDir::Down:
			m_AttackCollider->SetBoxSize(90.f, 140.f);
			m_AttackCollider->SetRelativePosition(0.f, -80.f);
			break;
		case EObjectDir::LeftDown:
			m_AttackCollider->SetBoxSize(120.f, 120.f);
			m_AttackCollider->SetRelativePosition(-45.f, -60.f);
			break;
		case EObjectDir::RightDown:
			m_AttackCollider->SetBoxSize(120.f, 120.f);
			m_AttackCollider->SetRelativePosition(75.f, -50.f);
			break;
		case EObjectDir::Right:
			m_AttackCollider->SetBoxSize(170.f, 90.f);
			m_AttackCollider->SetRelativePosition(60.f, -10.f);
			break;
		}
	}
	else if (m_UseSkill == EPlayerSkills::GhostSlash)
	{
		//// ��Ȱ�� ������ ���� Body�� �浹���������� �Ͻ������� �����Ѵ�. 
		m_Body->SetCollisionProfile("Default");

		int random = rand() % 2 + 1;

		if (random == 1)
		{
			m_Scene->GetResource()->SoundPlay("GhostSlash01");
		}
		else 
			m_Scene->GetResource()->SoundPlay("GhostSlash02");

		m_AttackCollider->SetBoxSize(150.f, 150.f);
	}
}

void CPlayer2D::Afterimage()
{
	// �ܻ� ����
	CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("AfterImage");

	CEffect* Effect = Afterimage->GetEffect();

	Afterimage->SetRootComponent(Effect);

	Effect->SetWorldPosition(m_Sprite->GetWorldPos());
	//Effect->AddWorldPosition(Vector3(0.f, 0.f, 0.f));

	CMaterial* Material = Effect->GetMaterial(0);
	//Material->SetOpacity(0.8f);

	// �ϴܳ־�� 
    Afterimage->SetLifeTime(1.f);

	//if (m_BlockTime == 0.f && m_HitTime == 0.f)
	{
        //Effect->SetTexture(m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetTexture());
        
        Effect->SetTexture(m_Sprite->GetTexture());
        Effect->SetTextureFrameIndex(m_Sprite->GetAnimation()->GetCurrentFrame(""));

        //Effect->SetWorldScale(Effect->GetTexture()->GetWidth() * 2.5f, Effect->GetTexture()->GetHeight() * 2.5f);
        Effect->SetWorldScale(m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetFrameData(m_Sprite->GetAnimation()->GetCurrentFrame("")).End.x * 2.5f,
            m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetFrameData(m_Sprite->GetAnimation()->GetCurrentFrame("")).End.y * 2.5f);

        //Effect->SetPivot(m_Sprite->GetPivot());
        Effect->SetPivot(m_Sprite->GetAnimation()->GetCurrentAnimationSequence("")->GetFramePivot(m_Sprite->GetAnimation()->GetCurrentFrame("")));

        //Effect->SetPivot(m_Sprite->)

		// �ܻ� ���ӽð��� �ٸ��� �Ͽ� �� �ܻ��� �ִϸ��̼� ������ �̾����� �ʰ� �Ѵ�. 
		//Effect->SetEffectType(EEffectType::Duration);

        Effect->SetDuration(3.f);

		Effect->SetRenderLayerName("Afterimage");

       

		// ������ Ȧ��¦���� ���� �ٸ� ���� 
		if (m_Sprite->GetAnimation()->GetCurrentFrame("") % 2 == 0)
			Material->SetBaseColorUnsignedChar(20, 232, 251, 255);
		//Material->SetBaseColorUnsignedChar(68, 83, 181, 255);
		else
			Material->SetBaseColorUnsignedChar(68, 83, 181, 255);
		//Material->SetBaseColorUnsignedChar(20, 232, 251, 255);


		/*if (m_Dash)
			Effect->SetDuration(m_Sprite->GetAnimation()->GetCurrentFrame("") / 15.f);
		else if (m_DoubleEdge)
			Effect->SetDuration(m_Sprite->GetAnimation()->GetCurrentFrame("") / 18.f);
		else
			Effect->SetDuration(m_Sprite->GetAnimation()->GetCurrentFrame("") / 13.f);*/
	}


    Material->SetRenderState("DepthDisable");

	// Ȧ�������ӿ� ���� ���� (�ܻ� ����)

    CGameObject* EffectObject = m_Scene->CreateObject<CGameObject>("EffectObject");
    CEffect* Effect1 = CreateComponent<CEffect>("MoveDust");

    EffectObject->SetRootComponent(Effect1);
    EffectObject->SetLifeTime(1.f);

	Effect1->SetAnimation<CAnimation2D>("asas");

	//Effect->AddChild(Effect1);

	Effect1->SetRelativePosition(0.f, -15.f);

	Effect1->GetAnimation()->AddAnimation("MoveDust", "PlayerMoveDust", 0.6f);
	Effect1->SetEffectType(EEffectType::Once);
	Effect1->GetAnimation()->SetLoop("MoveDust", false);

	Effect1->SetRenderLayerName("Effect");

	CMaterial* Material1 = Effect1->GetMaterial(0);
	Material1->SetOpacity(1.f);
}

void CPlayer2D::DashAttack()
{
	if (m_PressAttackKey)
	{
		m_UseSkill = EPlayerSkills::DashAttack;

		switch (m_Dir)
		{
		case EObjectDir::Up:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackUp");
			break;
		case EObjectDir::LeftUp:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackUpLeft");
			break;
		case EObjectDir::RightUp:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackUpRight");
			break;
		case EObjectDir::Left:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackLeft");
			break;
		case EObjectDir::Down:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackDown");
			break;
		case EObjectDir::LeftDown:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackDownLeft");
			break;
		case EObjectDir::RightDown:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackDownRight");
			break;
		case EObjectDir::Right:
			m_Sprite->GetAnimation()->ChangeAnimation("DashAttackRight");
			break;
		}

		m_Scene->GetResource()->SoundPlay("DashAttack");

		// �뽬Ÿ���� �ٿ� �뽬�� �������鼭 �뽬������ �����µ�, �ε巴�� �̾����� �Ѵ�.  
		m_DashTime = 0.2f;
		m_MoveSpeed = 1200.f;
	}
}

void CPlayer2D::AttackEnd()
{
	/*
		�뽬-������ ü���� ��� �뽬���尡 ȣ����� �ʱ� ������
		�̷��� ���ش�.
	*/
	m_DashTime = 0.f;
	m_Dash = false;

	SetMoveSpeed(250.f);
	
	m_Attack = false;
	m_DoubleEdge = false;

	m_Chain = false;
	 
	// �￬�� �ִϸ��̼��� ������ �Դٸ� �޺��� ó������ �̾���� �� 
	m_AttackCount = 0;


	
	m_UseSkill = EPlayerSkills::None;
}

void CPlayer2D::DashEnd()
{
	if(m_Body->GetCollisionProfile()->Name == "Default")
		m_Body->SetCollisionProfile("Object");
	/*
		����-�뽬�� ü���� ��� ���ÿ��尡 ȣ����� �ʱ� ������ 
		�̷��� ���ش�. 
	*/
	m_Attack = false;
	m_Chain = false;

	// �￬�� �ִϸ��̼��� ������ �Դٸ� �޺��� ó������ �̾���� �� 
	m_AttackCount = 0;

	m_DashTime = 0.f;
	m_Dash = false;


	SetMoveSpeed(250.f);
}

float CPlayer2D::GetHP()
{
    return m_HP;
}

float CPlayer2D::GetST()
{
    return m_Stamina;
}

void CPlayer2D::CollisionBeginAttack(const CollisionResult& result)
{
	result.Dest;

	int Damage = 0;

	switch (m_UseSkill)
	{
	case EPlayerSkills::ThreeSequenceSlash:
		if (m_AttackCount == 3)
			Damage = 50;
		else
			Damage = 30;
		break;
	case EPlayerSkills::DoubleEdge:
		Damage = 60;
		m_AttackCount = 0;
		break;
	case EPlayerSkills::DashAttack:
		Damage = 75;
		break;
	case EPlayerSkills::CounterAttack:
	{
		CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("PlayerCounterSlash");

		CEffect* Effect = Afterimage->GetEffect();

		Effect->SetAnimation<CAnimation2D>("Effect");

		Effect->SetWorldPosition(GetWorldPos());

		// �÷��̾� ���⿡ ���� �� ����Ʈ�� ȸ���� �ʿ� 
		if (m_Dir == EObjectDir::Right)
		{
			Effect->AddWorldRotationZ(180.f);
		}
		else if (m_Dir == EObjectDir::RightDown)
		{
			Effect->AddWorldRotationZ(135.f);
		}
		else if (m_Dir == EObjectDir::Down)
		{
			Effect->AddWorldRotationZ(90.f);
			Effect->AddWorldPositionY(-100.f);
		}
		else if (m_Dir == EObjectDir::LeftDown)
		{
			Effect->AddWorldRotationZ(45.f);
		}
		else if (m_Dir == EObjectDir::Left)
		{
			Effect->AddWorldRotationZ(0.f);
		}
		else if (m_Dir == EObjectDir::LeftUp)
		{
			Effect->AddWorldRotationZ(-45.f);
		}
		else if (m_Dir == EObjectDir::Up)
		{
			Effect->AddWorldRotationZ(-90.f);
		}
		else if (m_Dir == EObjectDir::RightUp)
		{
			Effect->AddWorldRotationZ(-135.f);

		}

		Effect->GetAnimation()->AddAnimation("CounterSlash", "CounterSlash", 0.5f);

		Effect->SetEffectType(EEffectType::Once);

        CMaterial* Material = Effect->GetMaterial(0);
        Material->SetRenderState("DepthDisable");

		Damage = 500;

		break;


	}
	case EPlayerSkills::GhostSlash:
	{
		
		Damage = 260;
		break;
	}
	}
	// ���濡 �������� ������. 
	EHitState HitState = result.Dest->GetOwner()->InflictDamage(Damage);


	// ����� �ǰ� �� ���¿� ���� ����Ʈ�� ����Ѵ�.
	CAfterimage* Afterimage = GetScene()->CreateObject<CAfterimage>("AfterImage1");

	//Effect->SetAnimation<CAnimation2D>("Afterimage1");

	// �ϴܳ־�� 
	if (HitState != EHitState::None)
	{
		Afterimage->SetLifeTime(1.f);

		CEffect* Effect1 = CreateComponent<CEffect>("PlayerHitEffect1");

		Afterimage->SetRootComponent(Effect1);

		Effect1->SetAnimation<CAnimation2D>("Effect1");

		int Random1 = (rand() % 2) + 1;

		if (HitState == EHitState::Normal)
		{
			if (Random1 == 1)
				Effect1->GetAnimation()->AddAnimation("SwordSpark1", "PlayerSwordSpark1", 0.25f);
			else if (Random1 == 2)
				Effect1->GetAnimation()->AddAnimation("SwordSpark1", "PlayerSwordSpark2", 0.25f);

			Effect1->SetEffectType(EEffectType::Once);

			Effect1->SetRenderLayerName("Effect");
            
            Effect1->SetWorldPositionZ(1.f);

			Effect1->SetPivot(0.5f, 0.5f);

			CMaterial* Material1 = Effect1->GetMaterial(0);
			Material1->SetOpacity(1.f);

			Material1->SetRenderState("DepthDisable");

			// ����Ʈ�� ����� ��ġ�� ���Ѵ�. 
			Effect1->SetWorldPosition(result.HitPoint);

			// �������� ����Ʈ�� ȸ����Ų��. 
			int Random = (rand() % 6) + 1;

			if (Random == 1)
				Effect1->AddWorldRotationZ(0.f);
			else if (Random == 2)
				Effect1->AddWorldRotationZ(60.f);
			else if (Random == 3)
				Effect1->AddWorldRotationZ(120.f);
			else if (Random == 4)
				Effect1->AddWorldRotationZ(180.f);
			else if (Random == 5)
				Effect1->AddWorldRotationZ(240.f);
			else if (Random == 6)
				Effect1->AddWorldRotationZ(360.f);
		}
		else if (HitState == EHitState::Block)
		{
			Effect1->GetAnimation()->AddAnimation("BlockCircle", "PlayerBlockCircle", 0.2f);

			Effect1->SetEffectType(EEffectType::Once);

			Effect1->SetRenderLayerName("Effect");

			Effect1->SetPivot(0.5f, 0.5f);

			CMaterial* Material1 = Effect1->GetMaterial(0);
			Material1->SetOpacity(1.f);

			//Material1->SetRenderState("DepthDisable");

			// ����Ʈ�� ����� ��ġ�� ���Ѵ�. 
			Effect1->SetWorldPosition(result.HitPoint);

			CEffect* Effect2 = CreateComponent<CEffect>("PlayerHitEffect2");
			Effect1->AddChild(Effect2);
			Effect2->SetAnimation<CAnimation2D>("Effect2");

			Effect2->SetEffectType(EEffectType::Once);

			Effect2->GetAnimation()->AddAnimation("BlockLight", "PlayerBlockLight", 0.2f);

			Effect2->SetRenderLayerName("Effect");

			Effect2->SetRelativePosition(0.f, 0.f);


			CEffect* Effect3 = CreateComponent<CEffect>("PlayerHitEffect3");
			Effect1->AddChild(Effect3);
			Effect3->SetAnimation<CAnimation2D>("Effect2");

			Effect3->GetAnimation()->AddAnimation("BlockSpark", "PlayerSwordSpark3", 0.2f);

			Effect3->SetEffectType(EEffectType::Loop);

			Effect3->SetRenderLayerName("Effect");

			Effect3->SetRelativePosition(0.f, 0.f);

			CMaterial* Material3 = Effect3->GetMaterial(0);
			Material3->SetBaseColorUnsignedChar(127, 235, 253, 0);

            Material3->SetRenderState("DepthDisable");

			// �������� ����Ʈ�� ȸ����Ų��. 
			int Random = (rand() % 6) + 1;

			if (Random == 1)
				Effect3->AddWorldRotationZ(50.f);
			else if (Random == 2)
				Effect3->AddWorldRotationZ(100.f);
			else if (Random == 3)
				Effect3->AddWorldRotationZ(150.f);
			else if (Random == 4)
				Effect3->AddWorldRotationZ(200.f);
			else if (Random == 5)
				Effect3->AddWorldRotationZ(250.f);
			else if (Random == 6)
				Effect3->AddWorldRotationZ(350.f);
		}
		else if (HitState == EHitState::Bigkill)
		{
			// ��ũ�� ����Ʈ 
			CMainHUD* mainHUD = m_Scene->GetViewport()->FindUIWindow<CMainHUD>("MainHUD");
			mainHUD->OnScreenEffect(EScreenEffect::WhiteFlash);

			// ī���;��� ����Ʈ1
			Effect1->SetWorldPosition(result.Dest->GetWorldPos());

			Effect1->GetAnimation()->AddAnimation("JustGuardCircle", "PlayerJustGuardCircle", 0.25f);

			Effect1->SetEffectType(EEffectType::Once);

			// ī���;��� ����Ʈ2 (���) 
			CEffect* Effect2 = CreateComponent<CEffect>("PlayerHitEffect");

			Effect1->AddChild(Effect2);

			Effect2->SetAnimation<CAnimation2D>("PlayerChain2");

			Effect2->GetAnimation()->AddAnimation("JustGuardCircle2", "PlayerChain", 0.25f);

			Effect2->SetRelativePosition(0.f, 0.f);

			Effect2->SetEffectType(EEffectType::Once);

			CMaterial* Material1 = Effect2->GetMaterial(0);
			Material1->SetFullColorUnsignedChar(255, 255, 255, 0);
			Material1->SetOnlyColor(true);

            Material1->SetRenderState("DepthDisable");
		}
        else if (HitState == EHitState::SuperArmor)
        {
            if (Random1 == 1)
				Effect1->GetAnimation()->AddAnimation("SwordSpark1", "PlayerSwordSpark1", 0.25f);
			else if (Random1 == 2)
				Effect1->GetAnimation()->AddAnimation("SwordSpark1", "PlayerSwordSpark2", 0.25f);

			Effect1->SetEffectType(EEffectType::Once);

			Effect1->SetRenderLayerName("Effect");

			Effect1->SetPivot(0.5f, 0.5f);

			CMaterial* Material1 = Effect1->GetMaterial(0);
			Material1->SetOpacity(1.f);
            Material1->SetBaseColorUnsignedChar(255, 0, 221, 0);

			//Material1->SetRenderState("DepthDisable");

			// ����Ʈ�� ����� ��ġ�� ���Ѵ�. 
			Effect1->SetWorldPosition(result.HitPoint);

            Material1->SetRenderState("DepthDisable");

			// �������� ����Ʈ�� ȸ����Ų��. 
			int Random = (rand() % 6) + 1;

			if (Random == 1)
				Effect1->AddWorldRotationZ(0.f);
			else if (Random == 2)
				Effect1->AddWorldRotationZ(60.f);
			else if (Random == 3)
				Effect1->AddWorldRotationZ(120.f);
			else if (Random == 4)
				Effect1->AddWorldRotationZ(180.f);
			else if (Random == 5)
				Effect1->AddWorldRotationZ(240.f);
			else if (Random == 6)
				Effect1->AddWorldRotationZ(360.f);
        }
	}

	

	// ���� �浹ü�� �����Ѵ�. 
	// ��, �ͽź����� ��� ���� Ÿ������ �����ؾ� �ϹǷ�, ������Ʈ���� �����Ѵ� 
	if(m_UseSkill != EPlayerSkills::GhostSlash)
		result.Src->Destroy();
}

void CPlayer2D::CollisionBeginObject(const CollisionResult& result)
{
	m_ObjectCollision = true;

	// ���ݹ����� ���Ϳ� �ٴ°�찡 ���� �� �ִµ� �̋� �����Ÿ��°� �����Ϸ��� 
	// ��ƮŸ�ӿ� �̰� �ϸ� �ȵ� 
	if (m_HitTime == 0.f && m_BlockTime == 0.f)
	{
		m_PrevSpeed = m_MoveSpeed;
		m_MoveSpeed = 0.f;
	}

	Vector3 SrcPos = result.Src->GetWorldPos();
	Vector3 DestPos = result.Dest->GetWorldPos();
	
	// ����� �ڽ��� �����̶��
	if (SrcPos.x - DestPos.x >= 0)
	{
		// ����� �ڽ��� ���� ���� �ִٸ� 
		if (SrcPos.y < DestPos.y)
		{
			// ������ �Ʒ��� �з�����
			m_HitCollider->AddWorldPosition(Vector3(500.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -500.f * g_DeltaTime, 0.f));
		}
		// ����� �ڽ��� ���� �Ʒ��� �ִٸ� 
		else if (SrcPos.y > DestPos.y)
		{
			// ������ ���� �з����� 
			m_HitCollider->AddWorldPosition(Vector3(500.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, 500.f * g_DeltaTime, 0.f));
		}
		// ����� �ڽ��� ���� �߾ӿ� �ִٸ�
		else
		{
			// ���������� �з�����. 
			m_HitCollider->AddWorldPosition(Vector3(500.f * g_DeltaTime, 0.f, 0.f));
		}
	}
	// ����� �ڽ��� �������̶�� 
	else if (DestPos.x - SrcPos.x >= 0)
	{
		// ����� �ڽ��� ������ ���� �ִٸ� 
		if (SrcPos.y  < DestPos.y)
		{
			// ���� �Ʒ��� �з�����
			m_HitCollider->AddWorldPosition(Vector3(-500.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, -500.f * g_DeltaTime, 0.f));
		}
		// ����� �ڽ��� ������ �Ʒ��� �ִٸ� 
		else if (SrcPos.y > DestPos.y)
		{
			// ���� ���� �з�����. 
			m_HitCollider->AddWorldPosition(Vector3(-500.f * g_DeltaTime, 0.f, 0.f));
			m_HitCollider->AddWorldPosition(Vector3(0.f, 500.f * g_DeltaTime, 0.f));
		}
		// ����� �ڽ��� ������ �߾ӿ� �ִٸ�
		else
		{
			// �������� �з�����. 
			m_HitCollider->AddWorldPosition(Vector3(-500.f * g_DeltaTime, 0.f, 0.f));
		}
	}
	// ����� �ڽ��� ������ 
	else
	{
		// ����� �ڽ��� ���� �ִٸ�
		if (SrcPos.y < DestPos.y )
		{
			// �Ʒ��� �з�����. 
			m_HitCollider->AddWorldPosition(Vector3(0.f, -500.f * g_DeltaTime, 0.f));
		}
		// ����� �ڽ��� �Ʒ��� �ִٸ� 
		else if (SrcPos.y > DestPos.y)
		{
			// ���� �з�����. 
			m_HitCollider->AddWorldPosition(Vector3(0.f, 500.f * g_DeltaTime, 0.f));
		}
	}

	
}

void CPlayer2D::CollisionEndObject(const CollisionResult& result)
{
	m_ObjectCollision = false;

	if (m_HitTime == 0.f)
	{
		// ���������� �񲸰��� �ȵǹǷ� 
		if (m_UseSkill == EPlayerSkills::DashAttack)
		{
			m_MoveSpeed = 0.f;
		}
		else
			m_MoveSpeed = m_PrevSpeed;
	}

	// ���� ���϶��� ����
	if (!m_Attack && !m_Dash && m_HitTime == 0.f)
		m_MoveSpeed = 250.f;
}
