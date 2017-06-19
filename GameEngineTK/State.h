#pragma once

#include "Character.h"


#include <vector>
#include "Obj3d.h"

class Character;


// �C���^�[�t�F�[�X
class State
{
public:
	virtual ~State(){}
	virtual void Action(Character* player) = 0;
};

// �ҋ@�X�e�[�g
class Standby :public State
{
private: 
	static State* pState;
public:
	static State* GetInstance();
	void Action(Character* player) override;
};


// �����U��
class ConvergenceAttack :public State
{
private:
	static State* pState;
public:
	static State* GetInstance();
	void Action(Character* player) override;
};

// �����U��
class ThrowingAttack :public State
{
private:
	static State* pState;
public:
	static State* GetInstance();
	void Action(Character* player) override;
};