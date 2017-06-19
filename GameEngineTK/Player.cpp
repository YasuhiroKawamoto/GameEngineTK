#include "Player.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �t�@�C���̓ǂݍ���
/// </summary>
void Player::Load()
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
void Player::Init()
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

	
	// �����X�e�[�g�̐ݒ�
	m_currentState = Standby::GetInstance();

	// �e�����蔻��m�[�h�̐ݒ�
	{

		m_collisionNodeBullet.Initialize();
		m_collisionNodeBullet.SetParent(&m_parts[PARTS_ARM]);
		m_collisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		m_collisionNodeBullet.SetRadius(0.5f);
	}
}

/// <summary>
/// ����
/// </summary>
void Player::FireBullet()
{
	// ���˂���p�[�c�̃��[���h�s����擾
	Matrix worldm = m_parts[Player::PARTS_ARM].GetWorldMatrix();

	// ���o�������(���[���h�)
	Vector3 scale;
	Quaternion rotation;
	Vector3 translation;

	// ���[���h���W����e�v�f�𒊏o
	worldm.Decompose(scale, rotation, translation);

	// �e�p�[�c����Ɨ�������
	m_parts[Player::PARTS_ARM].SetParent(nullptr);
	m_parts[Player::PARTS_ARM].SetScale(scale);
	m_parts[Player::PARTS_ARM].SetRotationQ(rotation);
	m_parts[Player::PARTS_ARM].SetTranslation(translation);

	m_bulletVel = Vector3(0.0f, 0.0f, -0.3f);
	// �p�[�c�̌����ɍ��킹�đ��x�x�N�g������]
	m_bulletVel = Vector3::Transform(m_bulletVel, rotation);

	m_isShoot = true;
	 

}

/// <summary>
/// ���Z�b�g
/// </summary>
void Player::ResetBullet()
{
	m_parts[Player::PARTS_ARM].SetParent(&m_parts[PARTS_BODY]);
	m_parts[PARTS_ARM].SetRotationQ(Quaternion::Identity);
	m_parts[PARTS_ARM].SetTranslation(Vector3(0.4f, 0.2f, 0.0f));


}


/// <summary>
/// �ړ�����
/// </summary>
void Player::Move()
{
	// �L�[�X�V
	auto key = m_keyboard->GetState();


	// �p�x�ύX
	if (key.A)
	{
		float angle = m_parts[PARTS_TANK].GetRotation().y;
		m_parts[PARTS_TANK].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	if (key.D)
	{
		float angle = m_parts[PARTS_TANK].GetRotation().y;
		m_parts[PARTS_TANK].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	// �O�i
	if (key.W)
	{
		Vector3 moveV(0.0f, 0.0f, -0.1f);

		// �ړ��x�N�g������]
		Matrix rotmat = Matrix::CreateRotationY(m_parts[0].GetRotation().y);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		m_parts[0].SetTranslation(m_parts[0].GetTranslation() + moveV);
	}

	//�@���
	if (key.S)
	{
		Vector3 moveV(0.0f, 0.0f, 0.1f);

		// �ړ��x�N�g������]
		Matrix rotmat = Matrix::CreateRotationY(m_parts[0].GetRotation().y);
		moveV = Vector3::TransformNormal(moveV, rotmat);

		m_parts[0].SetTranslation(m_parts[0].GetTranslation() + moveV);
	}
}

Player::Player()
{
	
}

Player::Player(DirectX::Keyboard * keybord, DirectX::Keyboard::KeyboardStateTracker * keyTracker)
	:m_keyboard(keybord),
	m_keyboardTracker(keyTracker)
{
	m_isShoot = false;
	m_cnt = 0;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	// �������̉��
	delete m_currentState;
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update()
{
	// ���݂̃A�N�V���������s
	m_currentState->Action(this);

	// �p�[�c�̍X�V
	std::vector<Obj3d>::iterator itr;
	for (itr = this->GetParts().begin(); itr != this->GetParts().end(); itr++)
	{
		itr->Update();
	}

	// �e�����蔻��m�[�h�̍X�V
	m_collisionNodeBullet.Update();

	// �ړ�����
	Move();

	auto key = m_keyboard->GetState();
	m_keyboardTracker->Update(key);
	if (m_keyboardTracker->pressed.Space)
	{
		m_isShoot = false;
		ResetBullet();
		
		FireBullet();
	}


	if (m_isShoot)
	{
		m_parts[PARTS_ARM].SetTranslation(m_parts[PARTS_ARM].GetTranslation() + m_bulletVel);
		m_cnt++;
	}

	if (m_cnt > 120)
	{
		m_cnt = 0;
		m_isShoot = false;
		ResetBullet();
	}

}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	// �p�[�c�̕`��
	std::vector<Obj3d>::iterator itr;
	for (itr = m_parts.begin(); itr != m_parts.end(); itr++)
	{
		itr->Draw();
	}

	// �e�����蔻��m�[�h�̕`��
	m_collisionNodeBullet.Drwa();
}
