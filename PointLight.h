#pragma once
#include "Vector3.h"

class PointLight {
public: //サブクラス
	//定数バッファ用データ構造体
	struct ConstbufferData {
		Vector3 lightpos_;
		float pa1;
		Vector3 lightcolor_;
		float pad2;
		Vector3 lightatten_;
		unsigned int active_;
	};

public: //メンバ関数
	inline const Vector3& GetLightPos() {
		return lightpos_;
	}
	inline const Vector3& GetLightColor() {
		return lightcolor_;
	}
	inline const Vector3& GetLightAtten() {
		return lightAtten_;
	}
	inline bool GetActive() {
		return active_;
	}

	inline void SetLightPos(const Vector3& lightpos) {
		lightpos_ = lightpos;
	}
	inline void SetLightColor(const Vector3& lightcolor) {
		lightcolor_ = lightcolor;
	}
	inline void SetLightAtten(const Vector3& lightAtten) {
		lightAtten_ = lightAtten;
	}
	inline void SetActive(const bool active) {
		active_ = active;
	}


private: //メンバ変数
	//ライト座標(ワールド座標系)
	Vector3 lightpos_{ 0,0,0 };
	//ライト色
	Vector3 lightcolor_ = { 1,1,1 };
	//ライト距離減衰係数
	Vector3 lightAtten_ = { 1.0f,1.0f,1.0f };
	//有効フラグ
	bool active_ = false;
};