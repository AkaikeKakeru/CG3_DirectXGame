#include "GameScene.h"
#include <cassert>

#include<random>

using namespace DirectX;

template <class T>
inline void safe_delete(T*& p) {
	delete p;
	p = nullptr;
}

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;

	//for (int i = 0; i < _countof(kusa); i++)
	//{
	//	delete kusa[i];
	//}

	//スプライトの解放
	safe_delete(sprite1);
	safe_delete(sprite2);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
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
	object3d = Object3d::Create();
	object3d->Update();

	/////乱数
	////シード生成器
	//std::random_device seed_gen;
	////乱数エンジン
	//std::mt19937_64 engine(seed_gen());
	////範囲の指定
	//std::uniform_real_distribution<float> dist(-20,+20);

	//for (int i = 0; i < _countof(kusa); i++)
	//{
	//	float valueX = dist(engine);
	//	float valueZ = dist(engine);

	//	kusa[i] = Object3d::Create();
	//	kusa[i]->SetPosition(
	//		XMFLOAT3(valueX,0,valueZ)
	//	);
	//	kusa[i]->Update();
	//}
}

void GameScene::Update()
{
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		XMFLOAT3 position = object3d->GetPosition();

		// 移動後の座標を計算
		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		// 座標の変更を反映
		object3d->SetPosition(position);
	}

	//for (int i = 0; i < _countof(kusa); i++)
	//{
	//	// オブジェクト移動
	//	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	//	{
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
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { Object3d::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	// オブジェクト移動
	if (input->PushKey(DIK_SPACE))
	{
		// 現在の座標を取得
		XMFLOAT2 position = sprite1->GetPosition();

		// 移動後の座標を計算
		position.x += 1.0f;

		// 座標の変更を反映
		sprite1->SetPosition(position);
	}

	object3d->Update();
	
	//for (int i = 0; i < _countof(kusa); i++)
	//{
	//	kusa[i]->Update();
	//}
}

void GameScene::Draw()
{
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
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	object3d->Draw();

	//for (int i = 0; i < _countof(kusa); i++)
	//{
	//	kusa[i]->Draw();
	//}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
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

