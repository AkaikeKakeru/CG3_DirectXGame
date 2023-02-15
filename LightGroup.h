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


public://メンバ関数
	
private://静的メンバ変数

private://メンバ変数
};