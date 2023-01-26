#include "Light.h"
//省略
template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

ComPtr<ID3D12Device> Light::device_ = nullptr;