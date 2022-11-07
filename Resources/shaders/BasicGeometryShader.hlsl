#include "BasicShaderHeader.hlsli"

//四角形の頂点数
static const uint vnum = 4;

//センターからのオフセット
static const float4 offset_array[vnum] = {
	float4(-0.5f,-0.5f,0,0),//左下
	float4(-0.5f,+0.5f,0,0),//左上
	float4(+0.5f,-0.5f,0,0),//右下
	float4(+0.5f,+0.5f,0,0),//右上
};

//点の入力から、四角形を出力
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout TriangleStream< GSOutput > output
){
	GSOutput element;

	//4点分回す
	for (uint i = 0; i < vnum; i++) {
		//ワールド座標ベースで、ずらす
		element.svpos = input[0].pos + offset_array[i];
		//ビュー、射影変換
		element.svpos = mul(mat,element.svpos);
		element.uv = float2(0.5f,0.5f);

		output.Append(element);
	}
}

//[maxvertexcount(3)]
//void main(
//	point VSOutput input[1] : SV_POSITION,
//	inout TriangleStream< GSOutput > output
//)
//{
//	GSOutput element;
//	//共通
//	element.normal = input[0].normal;
//	element.uv = input[0].uv;
//	//1点目
//	element.svpos = input[0].svpos;
//	output.Append(element);
//	//2点目
//	element.svpos = input[0].svpos + float4(10.0f,10.0f,0,0);
//	output.Append(element);
//	//3点目
//	element.svpos = input[0].svpos + float4(10.0f,0,0,0);;
//	output.Append(element);
//}