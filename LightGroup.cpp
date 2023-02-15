#include "LightGroup.h"
template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

ComPtr<ID3D12Device> LightGroup::device_ = nullptr;