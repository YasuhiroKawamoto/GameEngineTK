#include "CollisionNode.h"


//=======================================================
// *******CollisionNodeクラスのメンバ関数******************
//=======================================================
void CollisionNode::SetParent(Obj3d* parent)
{
	m_obj.SetParent(parent);
}

//=======================================================
// **********SphereNodeクラスのメンバ関数*****************
//=======================================================

// コンストラクタ
SphereNode::SphereNode()
	:m_radius(1.0f)
{
}

void SphereNode::Initialize()
{
	// デバッグ表示用モデルのの読み込み
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


