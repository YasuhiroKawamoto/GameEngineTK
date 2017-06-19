#pragma once

#include "Character.h"

#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"


/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public Character
{
public:

	// �p�[�c�̗񋓌^
	enum PARTS
	{
		PARTS_TANK,
		PARTS_BODY,
		PARTS_ENGINE,
		PARTS_HEAD,
		PARTS_ARM,

		PARTS_WEAPON_SWORD1,
		PARTS_WEAPON_SWORD2,
		PARTS_WEAPON_SWORD3,
		PARTS_WEAPON_SWORD4,
		PARTS_WEAPON_SWORD5,
		PARTS_WEAPON_SWORD6,
		PARTS_WEAPON_SWORD7,
		PARTS_WEAPON_SWORD8,

		PARTS_WEAPON_PARENT,
		PARTS_BEAM,

		PARTS_NUM
	};

private:
	// ����J�����o�ϐ�

	// �L�[�{�[�h
	DirectX::Keyboard* m_keyboard;
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardTracker;

	// �e���x
	DirectX::SimpleMath::Vector3 m_bulletVel;
	bool m_isShoot;
	int m_cnt;

	// �e�ۗp�̓����蔻��I�u�W�F�N�g
	SphereNode m_collisionNodeBullet;


public:
	// ���J�����o�֐�
	// �f�t�H���g�R���X�g���N�^
	Player();

	// �R���X�g���N�^
	Player(DirectX::Keyboard* keybord, DirectX::Keyboard::KeyboardStateTracker* keyTracker);

	// �f�X�g���N�^
	~Player();

	// �v���C���[�̍X�V
	void Update() override;

	// �v���C���̕`��
	void Draw() override;

	// �f�[�^�̓ǂݍ���
	void Load() override;

	// �f�[�^�̏�����
	void Init() override;

	// �e�۔���
	void FireBullet();

	// �e�ۑ��U
	void ResetBullet();

	// �L�[�̎擾
	DirectX::Keyboard* GetKey()
	{
		return m_keyboard;
	}

	// �e�̓����蔻��擾
	const SphereNode& GetCollisionNodeBullet()
	{
		return m_collisionNodeBullet;
	}
private:
	// ����J�����o�ϊ֐�
	void Move();


};