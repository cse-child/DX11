#include "Framework.h"

Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
	for (DNode* node : nodes)
		delete node;
	nodes.clear();
}

void Dijkstra::Update()
{
	if (KEY_DOWN(VK_F1))
	{
		CreateNode(mousePos);
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		for (DNode* node : nodes)
		{
			if (node->collider->IsPointCollision(mousePos))
			{
				selectNode = node;
				break;
			}
		}
	}

	if (KEY_UP(VK_RBUTTON))
	{
		if (selectNode == nullptr) return;

		for (DNode* node : nodes)
		{
			if (node == selectNode) continue; // �ڱ��ڽŰ� ������
			
			if (node->collider->IsPointCollision(mousePos))
			{
				node->AddEdge(selectNode);
				selectNode->AddEdge(node);
				break;
			}
		}
	}
}

void Dijkstra::Render()
{
	for (DNode* node : nodes)
		node->Render();
}

/* Ư�� ��ġ�� ��忡�� ���� ����� ��� ã�� */
int Dijkstra::FindCloseNode(Vector2 pos)
{
	float minCost = FLT_MAX;

	int index = -1;

	for (UINT i = 0; i < nodes.size(); i++)
	{
		float distance = Vector2::Distance(pos, nodes[i]->pos);

		if (minCost > distance)
		{
			minCost = distance;
			index = i;
		}
	}
	return index;
}

/* ������ �ִ� ���� �� ���� ���� ����� ��� ã�� */
int Dijkstra::FindMinCostNode()
{
	float minCost = FLT_MAX;

	int index = -1;

	for (UINT i = 0; i < nodes.size(); i++)
	{
		if (nodes[i]->isClosed) continue;

		if (minCost > nodes[i]->cost)
		{
			minCost = nodes[i]->cost;
			index = i;
		}
	}
	return index;
}

void Dijkstra::SetEdgeInfo(int curIndex)
{
	if (curIndex == -1) return;

	nodes[curIndex]->isClosed = true;

	float cost = nodes[curIndex]->cost;

	for (DNode::Edge* edge : nodes[curIndex]->edges)
	{
		if (edge->node->cost > cost + edge->cost)
		{
			edge->node->cost = cost + edge->cost;
			edge->node->via = curIndex;
		}
	}
}

void Dijkstra::ResetNodes()
{
	for (DNode* node : nodes)
	{
		node->isClosed = false;
		node->via = -1;
		node->cost = FLT_MAX;
	}
}

/* ��Ʈ��ŷ �̿��Ͽ� �ִ� ��� ã�� */
vector<Vector2> Dijkstra::GetPath(int start, int end)
{
	ResetNodes();

	// 1. ���۳�� �ʱ�ȭ
	int curIndex = start;
	nodes[curIndex]->cost = 0;
	nodes[curIndex]->via = start;

	for (DNode* node : nodes)
	{
		// 2. ���õ� ����� ������� �ʱ�ȭ, ���õ� ���� Close
		SetEdgeInfo(curIndex);

		// 3. Close�� �ȵ� ��� �� ���� ȿ���� ���� ��� ã��(����� ����)
		curIndex = FindMinCostNode();
	}
	
	// 4. ��Ʈ��ŷ �̿��Ͽ� �ִܰ�� ���ϱ�
	curIndex = end;

	vector<Vector2> path;
	while (curIndex != start)
	{
		path.push_back(nodes[curIndex]->pos);
		curIndex = nodes[curIndex]->via;

		if (curIndex == -1) // ��ΰ� ���� ���
			break;
	}
	
	path.push_back(nodes[start]->pos);

	return path;
}

void Dijkstra::CreateNode(Vector2 pos)
{
	DNode* node = new DNode(pos);
	node->index = nodes.size();

	nodes.push_back(node);
}
