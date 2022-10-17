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
			if (node == selectNode) continue; // 자기자신과 이을때
			
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

/* 특정 위치의 노드에서 가장 가까운 노드 찾기 */
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

/* 가지고 있는 노드들 중 가장 적은 비용의 노드 찾기 */
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

/* 백트래킹 이용하여 최단 경로 찾기 */
vector<Vector2> Dijkstra::GetPath(int start, int end)
{
	ResetNodes();

	// 1. 시작노드 초기화
	int curIndex = start;
	nodes[curIndex]->cost = 0;
	nodes[curIndex]->via = start;

	for (DNode* node : nodes)
	{
		// 2. 선택된 노드의 엣지노드 초기화, 선택된 노드는 Close
		SetEdgeInfo(curIndex);

		// 3. Close가 안된 노드 중 가장 효율이 좋은 노드 찾기(비용이 적은)
		curIndex = FindMinCostNode();
	}
	
	// 4. 백트래킹 이용하여 최단경로 구하기
	curIndex = end;

	vector<Vector2> path;
	while (curIndex != start)
	{
		path.push_back(nodes[curIndex]->pos);
		curIndex = nodes[curIndex]->via;

		if (curIndex == -1) // 경로가 없는 경우
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
