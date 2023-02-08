//#include "DirectionalLight.h"
//#include <cassert>
//#include "DirectXCommon.h"
////省略
//template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//
//ComPtr<ID3D12Device> DirectionalLight::device_ = nullptr;
//
//void DirectionalLight::StaticInitialize(ID3D12Device* device) {
//	//再初期化チェック
//	assert(!DirectionalLight::device_);
//	//nullptrチェック
//	assert(device);
//
//	//静的メンバ変数セット
//	DirectionalLight::device_ = device;
//}
//
//DirectionalLight* DirectionalLight::Create() {
//	DirectionalLight* light = new DirectionalLight();
//
//	light->Initialize();
//
//	return light;
//}
//
//void DirectionalLight::Initialize() {
//	CreateConstBuffer();
//	TransferConstBuffer();
//}
//
//void DirectionalLight::Update() {
//	if (dirty_) {
//		TransferConstBuffer();
//		dirty_ = false;
//	}
//}
//
//void DirectionalLight::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex) {
//	cmdList->SetGraphicsRootConstantBufferView(
//		rootParameterIndex, constBuff_->GetGPUVirtualAddress());
//}
//
//
//void DirectionalLight::CreateConstBuffer() {
//	HRESULT result;
//
//	// ヒーププロパティ
//	D3D12_HEAP_PROPERTIES heapProps{};
//	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
//
//	// リソース設定
//	D3D12_RESOURCE_DESC resourceDesc{};
//	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//	resourceDesc.Width = (sizeof(ConstBufferDataLight) + 0xff) & ~0xff;
//	resourceDesc.Height = 1;
//	resourceDesc.DepthOrArraySize = 1;
//	resourceDesc.MipLevels = 1;
//	resourceDesc.SampleDesc.Count = 1;
//	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//
//	// 定数バッファの生成
//	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
//		&heapProps, // アップロード可能
//		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
//		IID_PPV_ARGS(&constBuff_));
//	assert(SUCCEEDED(result));
//}
//
//void DirectionalLight::TransferConstBuffer() {
//	HRESULT result;
//
//	ConstBufferDataLight* constMap = nullptr;
//	result = constBuff_->Map(0, nullptr, (void**)&constMap);
//	if (SUCCEEDED(result)) {
//		constMap->lightv_ = -lightdir_;
//		constMap->lightcolor_ = lightcolor_;
//		constBuff_->Unmap(0, nullptr);
//	}
//}
