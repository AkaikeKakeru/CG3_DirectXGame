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
		// ���_��1�ǉ�
		output.Append(element);
	}

	// �ŏ��̓_��������x�ǉ�
	element.svpos = input[0].svpos;
	element.normal = input[0].normal;
	element.uv = input[0].uv;
	output.Append(element);
}