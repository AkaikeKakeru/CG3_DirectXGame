#pragma once

#include <Windows.h>
#include <wrl.h>

#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Model.h"

#include "WorldTransform.h"
#include "ViewProjection.h"

#include "Light.h"

/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d {
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // サブクラス
	// パイプラインセット
	struct PipelineSet {
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature_;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate_;
	};

	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0 {
		Matrix4 viewproj_;//ビュープロジェクション行列
		Matrix4 world_;//ワールド行列
		Vector3 cameraPos_;//カメラ座標(ワールド座標)
	};

private: // 定数

public: // 静的メンバ関数
	// 静的初期化
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	// 描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	// 描画後処理
	static void PostDraw();

	// 3Dオブジェクト生成
	static Object3d* Create();

	// 視点座標の取得
	static const Vector3& GetEye() { return viewProjection_.camera_.eye_; }

	// 視点座標の設定
	static void SetEye(Vector3 eye);

	// 注視点座標の取得
	static const Vector3& GetTarget() { return viewProjection_.camera_.target_; }

	// 注視点座標の設定
	static void SetTarget(Vector3 target);

	static void SetLight(Light* light) {
		Object3d::light_ = light;
	}

	// ベクトルによる移動
	static void CameraMoveVector(Vector3 move);

	// ベクトルによる視点移動
	static void CameraMoveEyeVector(Vector3 move);

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device_;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList_;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature_;
	// テクスチャあり用パイプライン
	static PipelineSet pipelineSet_;

	//ビュープロジェクション
	static ViewProjection viewProjection_;

	//ライト
	static Light* light_;

private:// 静的メンバ関数
	// カメラ初期化
	static void InitializeCamera(int window_width, int window_height);

	// グラフィックパイプライン生成
	static void InitializeGraphicsPipeline();

	// ビュー行列を更新
	static void UpdateViewMatrix();

public: // メンバ関数
	bool Initialize();
	// 毎フレーム処理
	void Update();
	// 描画
	void Draw();

	// 座標の取得
	const Vector3& GetPosition() const { return worldTransform_.position_; }

	//スケールの取得
	const Vector3& GetScale() const { return worldTransform_.scale_; }

	//回転の取得
	const Vector3& GetRotation() const { return worldTransform_.rotation_; }

	//ビュープロジェクションの取得
	const ViewProjection& GetViewProjection() const { return viewProjection_; }

	/// 座標の設定
	void SetPosition(const Vector3& position) { this->worldTransform_.position_ = position; }

	//スケールの設定
	void SetScale(const Vector3& scale) { this->worldTransform_.scale_ = scale; }

	//回転の設定
	void SetRotation(const Vector3& rotation) { this->worldTransform_.rotation_ = rotation; }

	//ワールド変換の設定
	void SetWorldTransform(const WorldTransform worldTransform) { worldTransform_ = worldTransform; }

	//ビュープロジェクションの設定
	void SetViewProjection(const ViewProjection& viewProjection) { viewProjection_ = viewProjection; }

	//モデルセッタ
	void SetModel(Model* model) { model_ = model; }

private: // メンバ変数
	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;
};