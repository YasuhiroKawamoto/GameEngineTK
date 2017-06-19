#pragma once

#include "Character.h"


#include <vector>
#include "Obj3d.h"

class Character;


// インターフェース
class State
{
public:
	virtual ~State(){}
	virtual void Action(Character* player) = 0;
};

// 待機ステート
class Standby :public State
{
private: 
	static State* pState;
public:
	static State* GetInstance();
	void Action(Character* player) override;
};


// 収束攻撃
class ConvergenceAttack :public State
{
private:
	static State* pState;
public:
	static State* GetInstance();
	void Action(Character* player) override;
};

// 投擲攻撃
class ThrowingAttack :public State
{
private:
	static State* pState;
public:
	static State* GetInstance();
	void Action(Character* player) override;
};