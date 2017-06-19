#pragma once

#include "Character.h"

#include <vector>
#include "Obj3d.h"
#include "CollisionNode.h"


/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public Character
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

	// キーボード
	DirectX::Keyboard* m_keyboard;
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardTracker;

	// 弾速度
	DirectX::SimpleMath::Vector3 m_bulletVel;
	bool m_isShoot;
	int m_cnt;

	// 弾丸用の当たり判定オブジェクト
	SphereNode m_collisionNodeBullet;


public:
	// 公開メンバ関数
	// デフォルトコンストラクタ
	Player();

	// コンストラクタ
	Player(DirectX::Keyboard* keybord, DirectX::Keyboard::KeyboardStateTracker* keyTracker);

	// デストラクタ
	~Player();

	// プレイヤーの更新
	void Update() override;

	// プレイヤの描画
	void Draw() override;

	// データの読み込み
	void Load() override;

	// データの初期化
	void Init() override;

	// 弾丸発射
	void FireBullet();

	// 弾丸装填
	void ResetBullet();

	// キーの取得
	DirectX::Keyboard* GetKey()
	{
		return m_keyboard;
	}

	// 弾の当たり判定取得
	const SphereNode& GetCollisionNodeBullet()
	{
		return m_collisionNodeBullet;
	}
private:
	// 非公開メンバ変関数
	void Move();


};