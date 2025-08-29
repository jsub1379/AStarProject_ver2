#include "AStar.h"
#include <iostream>


AStar::AStar()
{
}

AStar::~AStar()
{

}

void AStar::MakeGrid(char data)
{
	grid.emplace_back(data);
}
void AStar::FindPath()
{
	Node startNode;
	Node goalNode;
	
	for (int x = 0; x < grid.size(); ++x)
	{
		for (int y = 0; y < grid[0].size(); ++y)
		{
			if (grid[x][y] == 'S')
			{
				startNode.x = x; startNode.y = y;

			}
			if (grid[x][y] == 'G')
			{
				goalNode.x = x; goalNode.y = y;
			}
		}
	}

	openList.emplace_back(startNode);

	std::vector<Direction> directions =
	{
		// 하상우좌 이동.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// 대각선 이동.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f },
	};

	while (!openList.empty())
	{
		Node lowestNode = openList[0];

		for (Node node : openList)
		{
			if (node.fCost < lowestNode.fCost)
			{
				lowestNode = node;
			}
		}

		Node currentNode = lowestNode;
		
		//경로 찾은 경우
		if (currentNode == goalNode)
		{
			//todo: 경로 반환
		}

		//openlist 에서 삭제
		for (int ix = 0; ix < (int)openList.size(); ++ix)
		{
			// 위치 비교.
			if (openList[ix] == currentNode)
			{
				// iterator를 활용해 동적 배열에서 노드 제거.
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		bool isNodeInList = false;
		for (Node node : closedList)
		{
			if (node == currentNode)
			{
				isNodeInList = true;
				break;
			}
		}
		if (isNodeInList)
		{
			continue;
		}

		closedList.emplace_back(currentNode);

		//이웃 노드 방문
		for (Direction direction : directions)
		{
			int newX = currentNode.x + direction.x;
			int newY = currentNode.y + direction.y;

			if (IsInRange(newX, newY, grid))
			{
				continue;
			}
			//장애물인,벽경우 확인 x
			if (grid[newX][newY] == '#' || grid[newX][newY] == '@')
			{
				continue;
			}
			float gCost = currentNode.gCost + direction.cost;

			// 이미 방문했으면 무시
			if (HasVisited(newX, newY, gCost))
			{
				continue;
			}

			// 방문을 위한 노드 생성.
			// 비용도 계산.
			Node neighborNode;
			neighborNode.gCost = currentNode.gCost + direction.cost;
			// 휴리스틱 비용 계산 함수 호출.
			neighborNode.hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode.fCost = neighborNode.gCost + neighborNode.hCost;

			// 이웃 노드가 열린 리스트에 있는지 확인.
			Node openListNode;
			for (Node node : openList)
			{
				if (node == neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// 노드가 목록에 없거나 비용이 싸면, 새 노드 추가.
			if (openListNode.gCost > neighborNode.gCost
				|| openListNode.fCost > neighborNode.fCost)
			{
				openList.emplace_back(neighborNode);
			}

		}

	}

}


bool AStar::IsInRange(int x, int y, const std::vector<std::vector<char>>& grid)
{
	// x, y 범위가 벗어나면 false.
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	// 벗어나지 않았으면 true.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// 열린 리스트나 닫힌 리스트에 이미 해당 노드가 있으면 방문한 것으로 판단.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node node = openList[ix];
		if (node.x == x && node.y == y)
		{
			// 위치가 같고, 비용도 더 크면 방문할 이유 없음.
			if (node.gCost < gCost)
			{
				return true;
			}
			else if (node.gCost > gCost)
			{
				openList.erase(openList.begin() + ix);
			}
		}
	}

	for (int ix = 0; ix < (int)closedList.size(); ++ix)
	{
		Node node = closedList[ix];
		if (node.x == x && node.y == y)
		{
			// 위치가 같고, 비용도 높으면 방문할 이유 없음.
			if (node.gCost < gCost)
			{
				return true;
			}
			// 위치는 같으나 비용이 작다면, 기존 노드 제거.
			else if (node.gCost > gCost)
			{
				closedList.erase(closedList.begin() + ix);
			}
		}
	}

	// 목록에 없다고 확인되면 방문하지 않은 것으로 판단.
	return false;
}

float AStar::CalculateHeuristic(Node currentNode, Node goalNode)
{
	// 단순 거리 계산으로 휴리스틱 비용으로 활용.
	Vector2 diff = currentNode - goalNode;

	// 대각선 길이 구하기. 
	return (float)std::sqrt(diff.x * diff.x + diff.y * diff.y);
}