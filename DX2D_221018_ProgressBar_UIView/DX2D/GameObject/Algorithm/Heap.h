#pragma once

class Heap
{
public:
	Heap();
	~Heap();

	void Insert(Node* node);
	void UpdateUpper(int index); // 상향식

	Node* DeleteRoot();
	void UpdateLower(int index); // 하향식

	void Swap(int n1, int n2);

	void Clear() { heap.clear(); }

	bool Empty() { return heap.empty(); }

private:
	vector<Node*> heap;
};