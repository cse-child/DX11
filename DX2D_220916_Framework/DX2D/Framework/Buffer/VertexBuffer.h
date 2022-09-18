#pragma once

class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count);
	~VertexBuffer();

	void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

private:
	ID3D11Buffer* buffer;

	UINT stride;
	UINT offset;
};