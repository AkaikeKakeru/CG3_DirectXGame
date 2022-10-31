#include "BasicShaderHeader.hlsli"

[maxvertexcount(1)]
void main(
	point VSOutput input[1] : SV_POSITION,
	inout PointStream< GSOutput > output
)
{
	GSOutput element;
	element.svpos = input[0].svpos;
	element.normal = input[0].normal;
	element.uv = input[0].uv;
	output.Append(element);
}