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

private://静的メンバ変数
	//デバイス
	static ComPtr<ID3D12Device> device_;
};