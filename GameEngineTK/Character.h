#pragma once

#include "State.h"
#include "Obj3d.h"

class State;

class Character
{
protected:
	// 現在のステート
	State* m_currentState;

	// パーツベクター
	std::vector<Obj3d> m_parts;

public:
	// プレイヤーの更新
	virtual void Update() = 0;

	// ステートの変更
	virtual void ChangeState(State* state);

	// プレイヤの描画
	virtual void Draw() = 0;

	// データの読み込み
	virtual void Load() = 0;

	// データの初期化
	virtual void Init() = 0;

	// パーツの取得
	std::vector<Obj3d>& GetParts()
	{
		return m_parts;
	}
};