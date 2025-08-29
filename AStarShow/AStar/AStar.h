#pragma once
#include <vector>
#include "Math/Vector2.h"
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
	void MakeGrid(char data);
	void FindPath();
	bool IsInRange(int x, int y, const std::vector<std::vector<char>>& grid);
	bool HasVisited(int x, int y, float gCost);
	float CalculateHeuristic(Node currentNode, Node goalNode);
private:

	std::vector<std::vector<char>> grid = { };
	std::vector<Node> openList;
	std::vector<Node>closedList;
};


class Node : public Vector2
{
public:
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
};