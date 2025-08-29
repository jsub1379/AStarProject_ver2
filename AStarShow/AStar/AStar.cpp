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
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
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
		
		//��� ã�� ���
		if (currentNode == goalNode)
		{
			//todo: ��� ��ȯ
		}

		//openlist ���� ����
		for (int ix = 0; ix < (int)openList.size(); ++ix)
		{
			// ��ġ ��.
			if (openList[ix] == currentNode)
			{
				// iterator�� Ȱ���� ���� �迭���� ��� ����.
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

		//�̿� ��� �湮
		for (Direction direction : directions)
		{
			int newX = currentNode.x + direction.x;
			int newY = currentNode.y + direction.y;

			if (IsInRange(newX, newY, grid))
			{
				continue;
			}
			//��ֹ���,����� Ȯ�� x
			if (grid[newX][newY] == '#' || grid[newX][newY] == '@')
			{
				continue;
			}
			float gCost = currentNode.gCost + direction.cost;

			// �̹� �湮������ ����
			if (HasVisited(newX, newY, gCost))
			{
				continue;
			}

			// �湮�� ���� ��� ����.
			// ��뵵 ���.
			Node neighborNode;
			neighborNode.gCost = currentNode.gCost + direction.cost;
			// �޸���ƽ ��� ��� �Լ� ȣ��.
			neighborNode.hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode.fCost = neighborNode.gCost + neighborNode.hCost;

			// �̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
			Node openListNode;
			for (Node node : openList)
			{
				if (node == neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// ��尡 ��Ͽ� ���ų� ����� �θ�, �� ��� �߰�.
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
	// x, y ������ ����� false.
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	// ����� �ʾ����� true.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// ���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��尡 ������ �湮�� ������ �Ǵ�.
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node node = openList[ix];
		if (node.x == x && node.y == y)
		{
			// ��ġ�� ����, ��뵵 �� ũ�� �湮�� ���� ����.
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
			// ��ġ�� ����, ��뵵 ������ �湮�� ���� ����.
			if (node.gCost < gCost)
			{
				return true;
			}
			// ��ġ�� ������ ����� �۴ٸ�, ���� ��� ����.
			else if (node.gCost > gCost)
			{
				closedList.erase(closedList.begin() + ix);
			}
		}
	}

	// ��Ͽ� ���ٰ� Ȯ�εǸ� �湮���� ���� ������ �Ǵ�.
	return false;
}

float AStar::CalculateHeuristic(Node currentNode, Node goalNode)
{
	// �ܼ� �Ÿ� ������� �޸���ƽ ������� Ȱ��.
	Vector2 diff = currentNode - goalNode;

	// �밢�� ���� ���ϱ�. 
	return (float)std::sqrt(diff.x * diff.x + diff.y * diff.y);
}