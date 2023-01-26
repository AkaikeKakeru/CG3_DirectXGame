#pragma once
#include "Vector3.h"

class Light {
private: // エイリアス
	//省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://サブクラス
	struct ConstBufferData {
		Vector3 lightv; //ライトへの方向ベクトル
		Vector3 lightcolor;//ライトの色
	};
};