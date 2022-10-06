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
		// 초기화할때는 단위행렬로 초기화하여 world, view, projection 중 
		// 하나가 0이더라도 셋을 곱했을 때 에러나지 않도록 한다.
		data.matrix = XMMatrixIdentity(); // 단위행렬
	}

	void Set(Matrix value)
	{
		// GPU에서는 행->열 순서가 아닌 열->행 순서의 연산이
		// 더 빠르기 때문에 열->행 순서로 연산을 수행한다.
		// 따라서 내가 원하는 행렬의 연산 결과를 나오게 하려면 전치행렬로 뒤집는다.
		data.matrix = XMMatrixTranspose(value); // 전치행렬
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
	// 상수버퍼는 넘기는 요소가 16의 배수여야한다.
	//int index; // 얘는 4바이트여서 16의 배수가 안되므로 못씀
	int values[4] = {}; // 16바이트
};

class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
	{
	}
	float values[4] = {};
};