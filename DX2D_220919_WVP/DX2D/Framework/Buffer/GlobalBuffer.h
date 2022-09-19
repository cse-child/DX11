#pragma once
// GlobalBuffer

class MatrixBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	};

public:
	MatrixBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.matrix = XMMatrixIdentity(); // 단위행렬
	}

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value); // 전치행렬
	}
	
private:
	Data data;
};