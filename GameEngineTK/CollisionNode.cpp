#include "CollisionNode.h"


//=======================================================
// *******CollisionNode�N���X�̃����o�֐�******************
//=======================================================
void CollisionNode::SetParent(Obj3d* parent)
{
	m_obj.SetParent(parent);
}

//=======================================================
// **********SphereNode�N���X�̃����o�֐�*****************
//=======================================================

// �R���X�g���N�^
SphereNode::SphereNode()
	:m_radius(1.0f)
{
}

void SphereNode::Initialize()
{
	// �f�o�b�O�\���p���f���̂̓ǂݍ���
	m_obj.LoadModel(L"Resources\\SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTranslation(m_trans);
	m_obj.SetScale(DirectX::SimpleMath::Vector3(m_radius));
	m_obj.Update();
}

void SphereNode::Drwa()
{
	m_obj.Draw();
}


