#pragma once
#include "Vector3.h"
#include <wrl.h>
#include <d3d12.h>
#include "DirectionalLight.h"

class LightGroup {
private: // エイリアス
	//省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://定数
	static const int DirLightNum_ = 3;

public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferDat {
		//環境光の色
		Vector3 ambientColor_;
		float pad1_;
		//平行光源用
		DirectionalLight::ConstBufferData dirLights_[DirLightNum_];
	};

public://静的メンバ関数
	void StaticInitialize(ID3D12Device* device);

public://メンバ関数
	void Initialize();

	//定数バッファ生成
	void CreateConstBuffer();
	//定数バッファへのデータ転送
	void TransferConstBuffer();

private://静的メンバ変数
	//デバイス
	static ComPtr<ID3D12Device> device_;

private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	//環境光色
	Vector3 ambientColor_ = { 1,1,1 };
	//平行光源の配列
	DirectionalLight dirLights_[DirLightNum_];
	//ダーティフラグ
	bool dirty_ = false;
};