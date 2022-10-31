#include "BasicShaderHeader.hlsli"

[maxvertexcount(4)]
void main(
	triangle VSOutput input[3] : SV_POSITION,
	inout LineStream< GSOutput > output
)
{
	GSOutput element;

	for (uint i = 0; i < 3; i++)
	{
		element.svpos = input[i].svpos;
		element.normal = input[i].normal;
		element.uv = input[i].uv;
		// 頂点を1つ追加
		output.Append(element);
	}

	// 最初の点をもう一度追加
	element.svpos = input[0].svpos;
	element.normal = input[0].normal;
	element.uv = input[0].uv;
	output.Append(element);
}