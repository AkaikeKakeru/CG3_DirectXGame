#include "GameScene.h"
#include <cassert>
#include<random>

#include "Vector3.h"
#include "Vector4.h"

#include <sstream>
#include <iomanip>

#include <imgui.h>

using namespace DirectX;

template <class T>
inline void safe_delete(T*& p) {
	delete p;
	p = nullptr;
}

GameScene::GameScene() {
}

GameScene::~GameScene() {
	safe_delete(spriteBG);
	safe_delete(obj_1);
	safe_delete(model_1);

	safe_delete(lightGroup_);
	safe_delete(camera_);

	//スプライトの解放
	//safe_delete(sprite1);
	//safe_delete(sprite2);
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
	//Sprite::LoadTexture(2, L"Resources/texture.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	//カメラ生成
	camera_ = new Camera();
	Object3d::SetCamera(camera_);

	// 3Dオブジェクト生成
	model_1 = Model::LoadFromOBJ("sphere", true);
	obj_1 = Object3d::Create();
	obj_1->SetModel(model_1);

	//ライト生成
	lightGroup_ = LightGroup::Create();
	Object3d::SetLightGroup(lightGroup_);
}

void GameScene::Update() {
	{//imguiからのライトパラメータを反映
		lightGroup_->SetAmbientColor({
			ambientColor_ [0],
			ambientColor_ [1],
			ambientColor_ [2]
			});
		
		lightGroup_->SetDirLightDir(0, {
			lightDir_[0][0],
			lightDir_[0][1],
			lightDir_[0][2]
			});
		lightGroup_->SetDirLightColor(0, {
			lightColor_[0][0],
			lightColor_[0][1],
			lightColor_[0][2]
			});

		lightGroup_->SetDirLightDir(1, {
			lightDir_[1][0],
			lightDir_[1][1],
			lightDir_[1][2]
			});
		lightGroup_->SetDirLightColor(1, {
			lightColor_[1][0],
			lightColor_[1][1],
			lightColor_[1][2]
			});

		lightGroup_->SetDirLightDir(2, {
			lightDir_[2][0],
			lightDir_[2][1],
			lightDir_[2][2]
			});
		lightGroup_->SetDirLightColor(2, {
			lightColor_[2][0],
			lightColor_[2][1],
			lightColor_[2][2]
			});
	}

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		Vector3 position = obj_1->GetPosition();

		//移動後の座標を計算
		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		// 座標の変更を反映
		obj_1->SetPosition(position);
	}

	// カメラ移動
	//if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A)) {
	//	if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
	//	else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
	//	if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
	//	else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	//}

	// オブジェクト回転
	{
		// 現在の座標を取得
		Vector3 rot = obj_1->GetRotation();

		// 移動後の座標を計算
		rot.y += ConvertToRadian(1.0f);

		// 座標の変更を反映
		obj_1->SetRotation(rot);
	}

	//{
	//	static Vector3 lightDir = { 0,1,5 };

	//	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A)) {
	//		if (input->PushKey(DIK_W)) { lightDir.y += 1.0f; }
	//		else if (input->PushKey(DIK_S)) {lightDir.y -= 1.0f; }
	//		if (input->PushKey(DIK_D)) { lightDir.x += 1.0f; }
	//		else if (input->PushKey(DIK_A)) { lightDir.x -= 1.0f; }
	//	}

	//	light_->SetLightDir(lightDir);

	//}

	lightGroup_->Update();
	obj_1->Update();
}

void GameScene::Draw() {
#pragma region imgui描画
	ImGui::Begin("Light");

	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));

	ImGui::ColorEdit3("ambientColor", ambientColor_, ImGuiColorEditFlags_Float);
	ImGui::InputFloat3("lightDir0", lightDir_[0]);
	ImGui::ColorEdit3("lightColor0", lightColor_[0], ImGuiColorEditFlags_Float);
	ImGui::InputFloat3("lightDir1", lightDir_[1]);
	ImGui::ColorEdit3("lightColor1", lightColor_[1], ImGuiColorEditFlags_Float);
	ImGui::InputFloat3("lightDir2", lightDir_[2]);
	ImGui::ColorEdit3("lightColor2", lightColor_[2], ImGuiColorEditFlags_Float);
	ImGui::End();
#pragma endregion

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
	Object3d::PreDraw(cmdList);

	obj_1->Draw();

	Object3d::PostDraw();

	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(cmdList);

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