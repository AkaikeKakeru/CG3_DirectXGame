#include "BasicShaderHeader.hlsli"

[maxvertexcount(6)]
void main(
	triangle VSOutput input[3] : SV_POSITION,
	inout LineStream< GSOutput > output
)
{
	GSOutput element;

	for (uint i = 0; i < 3; i++)
	{
		// 線分の始点
		element.svpos = input[i].svpos;
		element.normal = input[i].normal;
		element.uv = input[i].uv;
		output.Append(element);

		// 線分の終点
		if (i == 2) {
			//+1すると溢れるので、最初に戻る
			element.svpos = input[0].svpos;
			element.normal = input[0].normal;
			element.uv = input[0].uv;
		}
		else {
			element.svpos = input[i + 1].svpos;
			element.normal = input[i + 1].normal;
			element.uv = input[i + 1].uv;
		}
		output.Append(element);

		//現在のストリップを終了し、次のストリップを開始
		output.RestartStrip();
	}
}