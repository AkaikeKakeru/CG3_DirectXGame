﻿#include "GameScene.h"
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
	Object3d::SetLight(lightGroup_);

	{
		lightGroup_->SetPointLightActive(0, false);
		lightGroup_->SetPointLightActive(1, false);
		lightGroup_->SetPointLightActive(2, false);

		lightGroup_->SetPointLightActive(0, true);
		pointLightPos_[0] = 0.5f;
		pointLightPos_[1] = 1.0f;
		pointLightPos_[2] = 0.0f;
	}
}

void GameScene::Update() {
	{
		lightGroup_->SetPointLightPos(0, { 
			pointLightPos_[0],
			pointLightPos_[1],
			pointLightPos_[2]
			});

		lightGroup_->SetPointLightColor(0, { 
			pointLightColor_[0],
			pointLightColor_[1],
			pointLightColor_[2]
			});

		lightGroup_->SetPointLightAtten(0, { 
			pointLightAtten_[0],
			pointLightAtten_[1],
			pointLightAtten_[2]
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

	lightGroup_->Update();
	obj_1->Update();
}

void GameScene::Draw() {

#pragma region imGui描画
	ImGui::Begin("Light");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(500, 200));

	ImGui::ColorEdit3("pointLightColor", pointLightColor_, ImGuiColorEditFlags_Float);
	ImGui::InputFloat3("pointLightPos", pointLightPos_);
	ImGui::InputFloat3("pointLightAtten", pointLightAtten_);

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