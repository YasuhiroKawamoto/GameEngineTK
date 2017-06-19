#pragma once

#include "Character.h"

#include <vector>
#include "Obj3d.h"



/// <summary>
/// エネミークラス
/// </summary>
class Enemy : public Character
{

public:
	// パーツの列挙型
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
	// 非公開メンバ変数
	static const int MOVE_TIME;
	int m_timer;
	float m_DistAngle;

	// パーツベクター
	std::vector<Obj3d> m_parts;


public:
	// 公開メンバ関数
	// デフォルトコンストラクタ
	Enemy();

	// デストラクタ
	~Enemy();

	// 更新
	void Update();

	// ステートの変更
	void ChangeState(State* state);

	// 描画
	void Draw();

	// パーツの取得
	std::vector<Obj3d>& GetParts()
	{
		return m_parts;
	}

	// データの読み込み
	void Load();


	// データの初期化
	void Init();

private:
	// 非公開メンバ変関数
	void Move();

	float ShorAngle(float ditangle, float currentAngle);
};