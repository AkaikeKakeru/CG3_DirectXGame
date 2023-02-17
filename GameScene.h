#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DebugText.h"
#include "LightGroup.h"
#include "Camera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;
	static const int lightCountNumber = 3;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugText debugText;
	Camera* camera_ = nullptr;
	LightGroup* lightGroup_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;
	Object3d* obj_1 = nullptr;
	Model* model_1 = nullptr;

	/// <summary>
	/// ライト用
	/// </summary>

	float ambientColor_0[lightCountNumber] = { 1,1,1 };

	//光線方向初期値
	float lightDir_0[lightCountNumber] = { 0,0,1 };
	float lightDir_1[lightCountNumber] = { 0,1,0 };
	float lightDir_2[lightCountNumber] = { 1,0,0 };

	//光色初期値
	float lightColor_0[lightCountNumber] = { 1,0,0 };
	float lightColor_1[lightCountNumber] = { 0,1,0 };
	float lightColor_2[lightCountNumber] = { 0,0,1 };

	//点光源初期値
	float pointLightPos_[lightCountNumber] = { 0,0,0 };
	float pointLightColor_[lightCountNumber] = { 1,1,1 };
	float pointLightAtten_[lightCountNumber] = { 0.3f,0.1f,0.1f };

private: // メンバ変数
	//Sprite* sprite1 = nullptr;
	//Sprite* sprite2 = nullptr;
};