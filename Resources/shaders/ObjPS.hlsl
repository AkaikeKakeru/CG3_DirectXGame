#include "Obj.hlsli"

Texture2D<float4>tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET{
	//テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	//シェーディングによる色
	float4 shadecolor = float4(ambientColor * ambient, m_alpha);

	//光沢度
	const float shininess = 4.0f;
	//頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	//環境反射光
	float3 ambient = m_ambient;

	for (int i = 0; i < DIRLIGHT_NUM; i++) {
		if (dirLight[i].active) {
			//ライトに向かうベクトルと法線の内積
			float3 dotlightnormal = dot(dirLight[i].lightv, input.normal);
			//反射光ベクトル
			float3 reflect = normalize(-dirLight[i].lightv + 2 * dotlightnormal * input.normal);

			//拡散反射光
			float3 diffuse = dotlightnormal * m_diffuse;
			//鏡面反射光
			float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

			//phong
			//全て加算
			shadecolor.rgb += (diffuse + specular) * dirLight[i].lightcolor;
			shadecolor.a += m_alpha;
		}
	}

	return shadecolor * texcolor;
}