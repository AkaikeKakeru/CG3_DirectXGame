cbuffer cbuff0 : register(b0) {
	matrix mat; //3D変換行列
};

cbuffer cbuff1 : register(b1) {
	float3 m_ambient : packoffset(c0); //アンビエント
	float3 m_diffuse : packoffset(c1); //ディヒューズ
	float3 m_specular : packoffset(c2); //スペキュラー
	float m_alpha : packoffset(c2.w); //アルファ
}

//頂点シェーダからピクセルシェーダへの出力
struct VSOutput {
	float4 svpos : SV_POSITION; //システム用頂点座標
	//float3 normal : NORMAL; //法線ベクトル
	float4 color : COLOR;//色
	float2 uv : TEXCOORD; //uv値
};