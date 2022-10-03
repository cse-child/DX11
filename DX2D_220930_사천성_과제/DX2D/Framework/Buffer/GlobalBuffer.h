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

class ColorBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Float4 color;
	};

public:
	ColorBuffer() : ConstBuffer(&data, sizeof(Data))
	{
		data.color = { 1,1,1,1 };
	}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		data.color = { r,g,b,a };
	}

	void Set(Float4 color)
	{
		data.color = color;
	}

	Float4& Get() { return data.color; }

private:
	Data data;
};

class IntValueBuffer : public ConstBuffer
{
public:
	IntValueBuffer() : ConstBuffer(values, sizeof(int) * 4)
	{
	}
	// ������۴� �ѱ�� ��Ұ� 16�� ��������Ѵ�.
	//int index; // ��� 4����Ʈ���� 16�� ����� �ȵǹǷ� ����
	int values[4] = {}; // 16����Ʈ
};

class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
	{
	}
	float values[4] = {};
};