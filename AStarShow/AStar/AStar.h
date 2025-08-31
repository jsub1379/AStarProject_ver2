#pragma once
#include <vector>
#include "Math/Vector2.h"


/*
* 1. �����κ��� �׸��� ����(����, ����, ��ֹ� ���� ����) �޾ƿ��� �޼ҵ� �ʿ���(FindPath�� �� ���� �޾Ƶ� ��).
* 2. FindPath���� ��θ� ã���� �� ��ȯ�Ǵ� ��� ������ ���� ��� �ٽ� �޾Ƽ� ����ȭ �غ�
*   2.1. �� �� ClosedList/Path ������ �־�� ��.
* 3. ClosedList�� �ð� ��(Ÿ�̸� �̿�)�� �ΰ� �湮�ϸ鼭 �ش� ������ ���� ���� ���� ���� �ð�ȭ ó��
* 4. ClosedList�� ��� �湮������, ���� ��� �迭(Path)�� �ð����� �ΰ� �湮�ϸ鼭 ���� ���� ���� ���� �ð�ȭ.
*/

class Node;
class AStar
{
	class Direction
	{
	public:
		int x = 0;
		int y = 0;
		float cost = 0.0f;

	};

public:
	AStar();
	~AStar();
	void MakeGrid(const std::vector<std::vector<char>>& data); 
	void FindPath();
	bool IsInRange(int x, int y, const std::vector<std::vector<char>>& grid);
	bool HasVisited(int x, int y, float gCost);
	float CalculateHeuristic(Node currentNode, Node goalNode);
	void ConstructPath(Node goalNode, Node startNode);
	void Path();

	// === Ž�� ���� �ð�ȭ ���� ===
	void SetVisualization(bool enabled, int visitDelayMs = 60, int pathDelayMs = 35)
	{
		visualizationEnabled = enabled;
		visualizationVisitDelayMs = visitDelayMs;
		visualizationPathDelayMs = pathDelayMs;
	}

	// === ���� ���ڸ� �ַܼ� �׸��� ===
	void ShowGrid();

	// === ���� ��θ� �ִϸ��̼����� �׸��� ===
	void ShowPath();


private:

	std::vector<std::vector<char>> grid = { };
	std::vector<Node> openList;
	std::vector<Node>closedList;
	std::vector<Node> path;
	bool visualizationEnabled = false;
	int  visualizationVisitDelayMs = 60;
	int  visualizationPathDelayMs = 35;

};


class Node : public Vector2
{
public:
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Vector2 parent;

	bool operator!=(const Node& other) const
	{
		return !(*this == other);
	}
};