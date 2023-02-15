#include "LightGroup.h"
#include <cassert>
#include "DirectXCommon.h"
template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

ComPtr<ID3D12Device> LightGroup::device_ = nullptr;

void LightGroup::StaticInitialize(ID3D12Device* device) {
	//再初期化チェック
	assert(!LightGroup::device_);
	//nullptrチェック
	assert(device);

	//静的メンバ変数セット
	LightGroup::device_ = device;
}

void LightGroup::Initialize() {
	CreateConstBuffer();
	TransferConstBuffer();
}

void LightGroup::CreateConstBuffer() {
	HRESULT result;

	// ヒーププロパティ
	D3D12_HEAP_PROPERTIES heapProps{};
	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;

	// リソース設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void LightGroup::TransferConstBuffer() {
}
