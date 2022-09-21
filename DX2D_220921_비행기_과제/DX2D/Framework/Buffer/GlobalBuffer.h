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