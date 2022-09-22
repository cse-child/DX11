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
		// �ʱ�ȭ�Ҷ��� ������ķ� �ʱ�ȭ�Ͽ� world, view, projection �� 
		// �ϳ��� 0�̴��� ���� ������ �� �������� �ʵ��� �Ѵ�.
		data.matrix = XMMatrixIdentity(); // �������
	}

	void Set(Matrix value)
	{
		// GPU������ ��->�� ������ �ƴ� ��->�� ������ ������
		// �� ������ ������ ��->�� ������ ������ �����Ѵ�.
		// ���� ���� ���ϴ� ����� ���� ����� ������ �Ϸ��� ��ġ��ķ� �����´�.
		data.matrix = XMMatrixTranspose(value); // ��ġ���
	}
	
private:
	Data data;
};