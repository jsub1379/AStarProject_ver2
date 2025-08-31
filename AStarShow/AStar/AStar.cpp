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

	grid = data; // 깊은 복사

	// ===== 테스트 출력 =====
	//std::cout << "=== SnapshotGrid Result ===" << std::endl;
	for (int y = 0; y < (int)grid[0].size(); ++y)  // y: 세로(height)
	{
		for (int x = 0; x < (int)grid.size(); ++x) // x: 가로(width)
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

			ConstructPath(currentNode,startNode);

			return;
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

			if (!IsInRange(newX, newY, grid))
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


			// 방문을 위한 노드 생성.
			// 비용도 계산.
			Node neighborNode;
			neighborNode.x = newX;
			neighborNode.y = newY;
			neighborNode.parent = Vector2(currentNode.x, currentNode.y);  // 부모 좌표 저장

			neighborNode.gCost = currentNode.gCost + direction.cost;
			neighborNode.hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode.fCost = neighborNode.gCost + neighborNode.hCost;


			// 이웃 노드가 열린 리스트에 있는지 확인.
			Node openListNode;
			bool inOpen = false;	
			for (Node& node : openList)
			{
				if (node == neighborNode)  // Vector2::operator==로 x,y 좌표 비교
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
	if (x >= static_cast<int>(grid.size()))     return false;   // x: width(바깥 벡터)
	if (y >= static_cast<int>(grid[0].size()))  return false;   // y: height(안쪽 벡터)
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

void AStar::ConstructPath(Node goalNode, Node startNode)
{
	path.clear();

	Node currentNode = goalNode;

	// start 포함 여부는 필요에 따라
	while (!(currentNode.x == startNode.x && currentNode.y == startNode.y))
	{
		path.emplace_back(currentNode);

		// 부모 좌표로 '점프'할 때, 좌표만 바꾸지 말고
		// closedList에서 그 좌표를 가진 '노드'를 찾아서 교체해야
		// 다음 루프에서 parent 사슬을 계속 탈 수 있음.
		bool foundParent = false;
		for (const Node& n : closedList)
		{
			if (n.x == currentNode.parent.x && n.y == currentNode.parent.y)
			{
				currentNode = n;     // 전체 노드 교체(부모 정보까지 함께 이동)
				foundParent = true;
				break;
			}
		}
		if (!foundParent)
		{
			// 안전장치: 부모를 못 찾으면 중단
			break;
		}
	}

	// 시작 노드를 경로에 포함하고 싶다면 추가
	path.emplace_back(startNode);

	std::reverse(path.begin(), path.end());
}



void AStar::Path()
{
	if (!path.empty())
	{
		std::cout << "경로를 찾았습니다. 최단 경로:\n";
		for (Node node : path)
		{
			std::cout
				<< "(" << node.x
				<< ", " << node.y << ") -> ";
		}
		std::cout << "목표 도착\n";
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

