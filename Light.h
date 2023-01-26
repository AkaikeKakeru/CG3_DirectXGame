#pragma once
#include "Vector3.h"
#include <wrl.h>
#include <d3d12.h>

class Light {
private: // エイリアス
	//省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://サブクラス
	struct ConstBufferData {
		Vector3 lightv_; //ライトへの方向ベクトル
		Vector3 lightcolor_;//ライトの色
	};

private://静的メンバ関数
	static void StaticInitialize(ID3D12Device* device);

private://静的メンバ変数
	//デバイス
	static ComPtr<ID3D12Device> device_;

public://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	//ライト光線方向(単位ベクトル)
	Vector3 lightdir_ = { 1,0,0 };
	//ライト色
	Vector3 lightcolor_ = { 1,1,1 };
	//ダーティフラグ
	bool dirty_ = false;
};