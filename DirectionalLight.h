#pragma once
#include "Vector3.h"
#include <wrl.h>
#include <d3d12.h>

class DirectionalLight {
private: // エイリアス
	//省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://サブクラス
	struct ConstBufferData {
		Vector3 lightv_; //ライトへの方向ベクトル
		Vector3 lightcolor_;//ライトの色
		unsigned int active_;//有効フラグ
	};

public://静的メンバ関数

public://メンバ関数
	//ライト方向を取得
	const Vector3& GetLightDir() const {
		return lightdir_;
	}

	//ライト色を取得
	const Vector3& GetLightColor() const {
		return lightcolor_;
	}

	//ライト方向をセット
	void SetLightDir(const Vector3& lightdir) {
		//正規化してセット
		lightdir_ = Vector3Normalize(lightdir);
		dirty_ = true;
	}

	//ライト色をセット
	void SetLightColor(const Vector3& lightcolor) {
		lightcolor_ = lightcolor;
		dirty_ = true;
	}

	//有効フラグをセット
	inline void SetActive(bool active) { active_ = active; }

	//有効チェック
	inline bool IsActive() { return active_; }

private://静的メンバ変数
	//デバイス
	static ComPtr<ID3D12Device> device_;

private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	//ライト光線方向(単位ベクトル)
	Vector3 lightdir_ = { 1,0,0 };
	//ライト色
	Vector3 lightcolor_ = { 1,1,1 };
	//ダーティフラグ
	bool dirty_ = false;

	//有効フラグ
	bool active_ = false;
};