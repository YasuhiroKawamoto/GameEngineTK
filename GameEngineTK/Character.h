#pragma once

#include "State.h"
#include "Obj3d.h"

class State;

class Character
{
protected:
	// ���݂̃X�e�[�g
	State* m_currentState;

	// �p�[�c�x�N�^�[
	std::vector<Obj3d> m_parts;

public:
	// �v���C���[�̍X�V
	virtual void Update() = 0;

	// �X�e�[�g�̕ύX
	virtual void ChangeState(State* state);

	// �v���C���̕`��
	virtual void Draw() = 0;

	// �f�[�^�̓ǂݍ���
	virtual void Load() = 0;

	// �f�[�^�̏�����
	virtual void Init() = 0;

	// �p�[�c�̎擾
	std::vector<Obj3d>& GetParts()
	{
		return m_parts;
	}
};