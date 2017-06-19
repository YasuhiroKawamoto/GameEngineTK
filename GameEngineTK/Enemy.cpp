#include "Enemy.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;


const int Enemy::MOVE_TIME = 60;
/// <summary>
/// �t�@�C���̓ǂݍ���
/// </summary>
void Enemy::Load()
{
	// �v���C���[�p�[�c�̃��[�h

	m_parts.resize(PARTS_NUM);

	m_parts[PARTS_TANK].LoadModel(L"Resources\\Tank.cmo");
	m_parts[PARTS_BODY].LoadModel(L"Resources\\Body.cmo");
	m_parts[PARTS_ARM].LoadModel(L"Resources\\Arm.cmo");
	m_parts[PARTS_HEAD].LoadModel(L"Resources\\Head.cmo");
	m_parts[PARTS_ENGINE].LoadModel(L"Resources\\Engine.cmo");

	for (int i = PARTS_WEAPON_SWORD1; i <= PARTS_WEAPON_SWORD8; i++)
	{
		m_parts[i].LoadModel(L"Resources\\Sword.cmo");
	}
	m_parts[PARTS_BEAM].LoadModel(L"Resources\\Sphere.cmo");

}


/// <summary>
/// ������
/// </summary>
void Enemy::Init()
{
	// �e�q�֌W�̍\�z
	m_parts[PARTS_BODY].SetParent(&m_parts[PARTS_TANK]);
	m_parts[PARTS_HEAD].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_ARM].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_ENGINE].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_WEAPON_PARENT].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_BEAM].SetParent(&m_parts[PARTS_WEAPON_PARENT]);

	for (int i = PARTS_WEAPON_SWORD1; i <= PARTS_WEAPON_SWORD8; i++)
	{
		m_parts[i].SetParent(&m_parts[PARTS_WEAPON_PARENT]);
	}



	// �q�p�[�c�̃I�t�Z�b�g
	m_parts[PARTS_BODY].SetTranslation(Vector3(0.0f, 0.5f, 0.0f));
	m_parts[PARTS_HEAD].SetTranslation(Vector3(-0.15f, 0.5f, 0.0f));
	m_parts[PARTS_ARM].SetTranslation(Vector3(0.4f, 0.2f, 0.0f));
	m_parts[PARTS_ENGINE].SetTranslation(Vector3(0.0f, 0.0f, 1.0f));

	for (int i = PARTS_WEAPON_SWORD1; i <= PARTS_WEAPON_SWORD8; i++)
	{
		int id = i - PARTS_WEAPON_SWORD1;
		float angle = XMConvertToRadians((360 / 8.0f)*id);
		m_parts[i].SetTranslation(Vector3(cosf(-angle), 0.5f, sinf(-angle)));
		m_parts[i].SetRotation(Vector3(0.0f, angle, 0.0f));
	}


	m_parts[PARTS_ARM].SetScale(Vector3(0.7f, 0.7f, 0.7f));


	m_parts[PARTS_BEAM].SetScale(Vector3::Zero);

	m_parts[PARTS_TANK].SetScale(Vector3(0.5f, 0.5f,0.5f));



	// �����X�e�[�g�̐ݒ�
	m_currentState = Standby::GetInstance();

	// �����ʒu�������_���ɐݒ�
	float x = rand() % 20-10;
	float z = rand() % 20-10;

	m_parts[PARTS_TANK].SetTranslation(Vector3(x, 0, z));

	m_currentState = Standby::GetInstance();
}


/// <summary>
/// �ړ�����
/// </summary>
void Enemy::Move()
{
	Vector3 moveV(0.0f, 0.0f, -0.05f);

	// �ړ��x�N�g������]
	Matrix rotmat = Matrix::CreateRotationY(m_parts[0].GetRotation().y);
	moveV = Vector3::TransformNormal(moveV, rotmat);

	m_parts[0].SetTranslation(m_parts[0].GetTranslation() + moveV);
}

float Enemy::ShorAngle(float ditangle, float currentAngle)
{
	float angle = ditangle - currentAngle;

	if (angle > XM_PI)
	{
		angle -= XM_2PI;
	}
	if (angle < -XM_PI)
	{
		angle += XM_2PI;
	}

	return angle;
}

Enemy::Enemy()
	:m_timer(0),
	m_DistAngle(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{

}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update()
{
	// ���݂̃X�e�[�g
	//if (this != nullptr)
	//	m_currentState->Action(this);

	// �p�[�c�̍X�V
	std::vector<Obj3d>::iterator itr;
	for (itr = this->GetParts().begin(); itr != this->GetParts().end(); itr++)
	{
		itr->Update();
	}

	// �ړ�����
	Move();

	// �p�x�̕ύX
	m_timer--;
	if (m_timer < 0)
	{
		m_timer = MOVE_TIME;

		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;

		m_DistAngle = XMConvertToRadians(rnd);
	}

	Vector3 rot = m_parts[0].GetRotation();

	float angle = ShorAngle(m_DistAngle, rot.y);
	rot.y += angle*0.01f;

	m_parts[0].SetRotation(rot);
}


/// <summary>
///  �X�e�[�g�̕ύX
/// </summary>
void Enemy::ChangeState(State* state)
{
	m_currentState = state;
}


/// <summary>
/// �`��
/// </summary>
void Enemy::Draw()
{
	// �p�[�c�̕`��
	std::vector<Obj3d>::iterator itr;
	for (itr = m_parts.begin(); itr != m_parts.end(); itr++)
	{
		itr->Draw();
	}
}
