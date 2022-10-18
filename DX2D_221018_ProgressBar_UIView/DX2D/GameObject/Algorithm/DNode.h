#pragma once

class DNode
{
public:
	friend class Dijkstra;

	struct Edge // 경로 정보
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

	int index = 0; // 배열의 위치
	int via = -1; // 지나친 경로(어떤 노드로부터 왔는지)

	float cost = FLT_MAX; // float 자료형의 최댓값
	
	vector<Edge*> edges;
	
	Collider* collider;
};