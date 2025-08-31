#include "AStar.h"
#include <iostream>
#include <Windows.h>
#include <Utils/Utils.h>
AStar::AStar()
{
}

AStar::~AStar()
{

}

void AStar::MakeGrid(const std::vector<std::vector<char>>& data)
{
	system("cls");
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	Utils::SetConsolePosition(coord);

	grid = data; // ���� ����

	// ===== �׽�Ʈ ��� =====
	//std::cout << "=== SnapshotGrid Result ===" << std::endl;
	for (int y = 0; y < (int)grid[0].size(); ++y)  // y: ����(height)
	{
		for (int x = 0; x < (int)grid.size(); ++x) // x: ����(width)
		{
			std::cout << grid[x][y];
		}
		std::cout << std::endl;
	}
	std::cout << "===========================" << std::endl;
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

			ConstructPath(currentNode,startNode);

			return;
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

			if (!IsInRange(newX, newY, grid))
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

			if (visualizationEnabled)
			{
				if (grid[newX][newY] != '@' && grid[newX][newY] != '#' &&
					grid[newX][newY] != 'S' && grid[newX][newY] != 'G')
				{
					grid[newX][newY] = '+';
				}

				ShowGrid();
				Sleep(visualizationVisitDelayMs);
			}


			// �湮�� ���� ��� ����.
			// ��뵵 ���.
			Node neighborNode;
			neighborNode.x = newX;
			neighborNode.y = newY;
			neighborNode.parent = Vector2(currentNode.x, currentNode.y);  // �θ� ��ǥ ����

			neighborNode.gCost = currentNode.gCost + direction.cost;
			neighborNode.hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode.fCost = neighborNode.gCost + neighborNode.hCost;


			// �̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
			Node openListNode;
			bool inOpen = false;	
			for (Node& node : openList)
			{
				if (node == neighborNode)  // Vector2::operator==�� x,y ��ǥ ��
				{
					inOpen = true;
					if (neighborNode.gCost < node.gCost)
					{
						node.gCost = neighborNode.gCost;
						node.hCost = neighborNode.hCost;
						node.fCost = neighborNode.fCost;
						node.parent.x = neighborNode.parent.x;
						node.parent.y = neighborNode.parent.y;
					}
					break;
				}
			}
			if (!inOpen)
			{
				openList.emplace_back(neighborNode);
			}


		}

	}

}


bool AStar::IsInRange(int x, int y, const std::vector<std::vector<char>>& grid)
{
	if (x < 0 || y < 0) return false;
	if (x >= static_cast<int>(grid.size()))     return false;   // x: width(�ٱ� ����)
	if (y >= static_cast<int>(grid[0].size()))  return false;   // y: height(���� ����)
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

void AStar::ConstructPath(Node goalNode, Node startNode)
{
	path.clear();

	Node currentNode = goalNode;

	// start ���� ���δ� �ʿ信 ����
	while (!(currentNode.x == startNode.x && currentNode.y == startNode.y))
	{
		path.emplace_back(currentNode);

		// �θ� ��ǥ�� '����'�� ��, ��ǥ�� �ٲ��� ����
		// closedList���� �� ��ǥ�� ���� '���'�� ã�Ƽ� ��ü�ؾ�
		// ���� �������� parent �罽�� ��� Ż �� ����.
		bool foundParent = false;
		for (const Node& n : closedList)
		{
			if (n.x == currentNode.parent.x && n.y == currentNode.parent.y)
			{
				currentNode = n;     // ��ü ��� ��ü(�θ� �������� �Բ� �̵�)
				foundParent = true;
				break;
			}
		}
		if (!foundParent)
		{
			// ������ġ: �θ� �� ã���� �ߴ�
			break;
		}
	}

	// ���� ��带 ��ο� �����ϰ� �ʹٸ� �߰�
	path.emplace_back(startNode);

	std::reverse(path.begin(), path.end());
}



void AStar::Path()
{
	if (!path.empty())
	{
		std::cout << "��θ� ã�ҽ��ϴ�. �ִ� ���:\n";
		for (Node node : path)
		{
			std::cout
				<< "(" << node.x
				<< ", " << node.y << ") -> ";
		}
		std::cout << "��ǥ ����\n";
	}
}

void AStar::ShowGrid()
{
	if (!visualizationEnabled) return;

	COORD coord{ 0, 0 };
	Utils::SetConsolePosition(coord);

	const int width = static_cast<int>(grid.size());
	const int height = width > 0 ? static_cast<int>(grid[0].size()) : 0;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			std::cout << grid[x][y];
		}
		std::cout << "\n";
	}
}


void AStar::ShowPath()
{
	if (!visualizationEnabled) return;

	for (const auto& p : path)
	{
		const int x = static_cast<int>(p.x);
		const int y = static_cast<int>(p.y);
		if (x < 0 || y < 0) continue;
		if (x >= static_cast<int>(grid.size())) continue;
		if (y >= static_cast<int>(grid[0].size())) continue;

		if (grid[x][y] != 'S' && grid[x][y] != 'G')
			grid[x][y] = '*';

		ShowGrid();
		Sleep(visualizationPathDelayMs);
	}
}

