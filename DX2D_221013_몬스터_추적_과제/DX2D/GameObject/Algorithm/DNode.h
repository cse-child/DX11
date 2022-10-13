#pragma once

class DNode
{
public:
	friend class Dijkstra;

	struct Edge // ��� ����
	{
		DNode* node;
		float cost;
		LineCollider* line;

		Edge(Vector2 start, Vector2 end)
		{
			line = new LineCollider(start, end);
		}
		~Edge()
		{
			delete line;
		}
	};

public:
	DNode(Vector2 pos);
	~DNode();

	void Render();

	void AddEdge(DNode* node);

private:
	Vector2 pos;

	bool isClosed = false;

	int index = 0; // �迭�� ��ġ
	int via = -1; // ����ģ ���(� ���κ��� �Դ���)

	float cost = FLT_MAX; // float �ڷ����� �ִ�
	
	vector<Edge*> edges;
	
	Collider* collider;
};