#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <wrl.h>
#include "Vector3.h"

class Material {
private: // エイリアス
	//省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //サブクラス
		//マテリアル
	struct ConstBufferDataMaterial {
		Vector3 ambient; //アンビエント影響度
		Vector3 diffuse; //ディフューズ影響度
		Vector3 specular; //スペキュラー影響度
		float alpha; //アルファ
		};

public: //静的メンバ関数
	//静的初期化
	static void StaticInitialize(ID3D12Device* device);
	//生成
	static Material* Create();

private:
	// コンストラクタ
	Material() {
		ambient_ = {0.3f, 0.3f, 0.3f};
		diffuse_ = {0.0f, 0.0f, 0.0f};
		specular_ = {0.0f, 0.0f, 0.0f};
		alpha_ = 1.0f;
	}

	void Initialize();
	// 定数バッファの生成
	void CreateConstBuffer();

public:
	void Update();
	//テクスチャ読み込み
	void LoadTexture(const std::string& directoryPath,
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle,
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle);

	// 定数バッファの取得
	ComPtr<ID3D12Resource> GetConstantBuffer() { return constBuff_.Get(); }
	
	const CD3DX12_CPU_DESCRIPTOR_HANDLE& GetCpuHandle() { return cpuDescHandleSRV_; }
	const CD3DX12_GPU_DESCRIPTOR_HANDLE& GetGpuHandle() { return gpuDescHandleSRV_; }

private: // 静的メンバ変数
	// デバイス
	static ComPtr<ID3D12Device> device_;

public:
	std::string name_;            // マテリアル名
	Vector3 ambient_;            // アンビエント影響度
	Vector3 diffuse_;            // ディフューズ影響度
	Vector3 specular_;           // スペキュラー影響度
	float alpha_;                 // アルファ
	std::string filename_; // テクスチャファイル名

private:
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV_;
	// シェーダリソースビューのハンドル(GPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV_;

	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff_;
	// 定数バッファマテリアル
	ComPtr<ID3D12Resource> constBuff_;

	//定数バッファマップ
	ConstBufferDataMaterial* constMap_ = nullptr;
};