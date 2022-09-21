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
		data.matrix = XMMatrixIdentity(); // �������
	}

	void Set(Matrix value)
	{
		data.matrix = XMMatrixTranspose(value); // ��ġ���
	}
	
private:
	Data data;
};