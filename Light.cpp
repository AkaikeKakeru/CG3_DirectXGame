#include "Light.h"
#include <cassert>
//省略
template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

ComPtr<ID3D12Device> Light::device_ = nullptr;

void Light::StaticInitialize(ID3D12Device* device){
	//再初期化チェック
	assert(!Light::device_);
	//nullptrチェック
	assert(device);

	//静的メンバ変数セット
	Light::device_ = device;
}
