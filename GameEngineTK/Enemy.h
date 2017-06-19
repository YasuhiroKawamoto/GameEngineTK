#pragma once

#include "Character.h"

#include <vector>
#include "Obj3d.h"



/// <summary>
/// �G�l�~�[�N���X
/// </summary>
class Enemy : public Character
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
	static const int MOVE_TIME;
	int m_timer;
	float m_DistAngle;

	// �p�[�c�x�N�^�[
	std::vector<Obj3d> m_parts;


public:
	// ���J�����o�֐�
	// �f�t�H���g�R���X�g���N�^
	Enemy();

	// �f�X�g���N�^
	~Enemy();

	// �X�V
	void Update();

	// �X�e�[�g�̕ύX
	void ChangeState(State* state);

	// �`��
	void Draw();

	// �p�[�c�̎擾
	std::vector<Obj3d>& GetParts()
	{
		return m_parts;
	}

	// �f�[�^�̓ǂݍ���
	void Load();


	// �f�[�^�̏�����
	void Init();

private:
	// ����J�����o�ϊ֐�
	void Move();

	float ShorAngle(float ditangle, float currentAngle);
};