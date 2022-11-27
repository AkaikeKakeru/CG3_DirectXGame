#include "GameScene.h"
#include <cassert>
#include<random>

using namespace DirectX;

template <class T>
inline void safe_delete(T*& p) {
	delete p;
	p = nullptr;
}

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete spriteBG;
	delete particleMan;

	//for (int i = 0; i < _countof(kusa); i++)
	//{
	//	delete kusa[i];
	//}

	//スプライトの解放
	safe_delete(sprite1);
	safe_delete(sprite2);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	////テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/texture.png");

	//草用テクスチャをテクスチャ2番に読み込み
	//Sprite::LoadTexture(2, L"Resources/kusa.png");


	//座標{0,0}に、テクスチャ2番のスプライトを生成
	//sprite1 = Sprite::Create(2, { 0,0 });
	//座標{500,500}に、テクスチャ2番のスプライトを生成
	//sprite2 = Sprite::Create(2, { 500,500 }, { 1,0,0,1 }, { 0,0 }, false, true);

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	particleMan = ParticleManager::Create();

	//for (int i = 0; i < 100; i++){
	//	//X,Y,Z全て[-5.0f,+5,0f]でランダムに分布
	//	const float rnd_pos = 10.0f;
	//	XMFLOAT3 pos{};
	//	pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//	pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
	//	pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

	//	//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
	//	const float rnd_vel = 0.1f;
	//	XMFLOAT3 vel{};
	//	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

	//	//重力に見立ててYのみ[-0.001f,0]でランダムに分布
	//	XMFLOAT3 acc{};
	//	const float rnd_acc = 0.001f;
	//	acc.y = -(float)rand() / RAND_MAX * rnd_acc;

	//	//追加
	//	particleMan->Add(60, pos, vel, acc);
	//}

	particleMan->Update();

	/////乱数
	////シード生成器
	//std::random_device seed_gen;
	////乱数エンジン
	//std::mt19937_64 engine(seed_gen());
	////範囲の指定
	//std::uniform_real_distribution<float> dist(-20,+20);

	//for (int i = 0; i < _countof(kusa); i++){
	//	float valueX = dist(engine);
	//	float valueZ = dist(engine);

	//	kusa[i] = ParticleManager::Create();
	//	kusa[i]->SetPosition(
	//		XMFLOAT3(valueX,0,valueZ)
	//	);
	//	kusa[i]->Update();
	//}
}

void GameScene::Update() {
	if (particleNum >= 100) {
		particleNum = 0;
	}

	particleNum++;

	for (int i = 0; i < 100; i++){

		if (i == particleNum) {

			//X,Y,Z全て[-5.0f,+5,0f]でランダムに分布
			const float rnd_pos = 10.0f;
			XMFLOAT3 pos{};
			pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

			//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			//重力に見立ててYのみ[-0.001f,0]でランダムに分布
			const float rnd_acc = 0.001f;
			XMFLOAT3 acc{};
			acc.y = -(float)rand() / RAND_MAX * rnd_acc;

			//[1.0f,2.0f]で分布
			const float rnd_scale = 1.0f;
			float s_scale = 0.0f;
			s_scale = (float)rand() / RAND_MAX  * rnd_scale + rnd_scale;

			//全て、[64.0f,192.0f]で分布
			const float rnd_color = 256.0f;
			XMFLOAT4 s_color, e_color = {};
			s_color.x = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			s_color.y = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			s_color.z = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			//s_color.w = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			s_color.w = 1.0f;
			e_color.x = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			e_color.y = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			e_color.z = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			//e_color.w = (float)rand() / RAND_MAX  * rnd_color ;//+( rnd_color/2);
			e_color.w = 1.0f;

			//追加
			particleMan->Add(60,
				pos, vel, acc,
				s_scale,0.0f,
				s_color,e_color);
		}
	}

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		//XMFLOAT3 position = object3d->GetPosition();

		// 移動後の座標を計算
		//if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		//else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		//if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		//else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		//// 座標の変更を反映
		//object3d->SetPosition(position);
	}

	//for (int i = 0; i < _countof(kusa); i++){
	//	// オブジェクト移動
	//	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)){
	//		// 現在の座標を取得
	//		XMFLOAT3 position = kusa[i]->GetPosition();

	//		// 移動後の座標を計算
	//		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
	//		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
	//		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
	//		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

	//		// 座標の変更を反映
	//		kusa[i]->SetPosition(position);
	//	}
	//}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	// オブジェクト移動
	if (input->PushKey(DIK_SPACE)) {
		// 現在の座標を取得
		XMFLOAT2 position = sprite1->GetPosition();

		// 移動後の座標を計算
		position.x += 1.0f;

		// 座標の変更を反映
		sprite1->SetPosition(position);
	}

	particleMan->Update();

	//for (int i = 0; i < _countof(kusa); i++){
	//	kusa[i]->Update();
	//}
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	particleMan->Draw();

	//for (int i = 0; i < _countof(kusa); i++){
	//	kusa[i]->Draw();
	//}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//sprite1->Draw();
	//sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}