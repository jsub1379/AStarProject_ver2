#pragma once
#include <vector>
#include "Math/Vector2.h"


/*
* 1. 레벨로부터 그리드 정보(시작, 종료, 장애물 정보 포함) 받아오는 메소드 필요함(FindPath할 때 전달 받아도 됨).
* 2. FindPath에서 경로를 찾았을 때 반환되는 경로 정보를 레벨 등에서 다시 받아서 시작화 준비
*   2.1. 이 때 ClosedList/Path 정보가 있어야 함.
* 3. ClosedList를 시간 차(타이머 이용)를 두고 방문하면서 해당 지점에 액터 생성 등을 통해 시각화 처리
* 4. ClosedList를 모두 방문했으면, 최종 경로 배열(Path)를 시간차를 두고 방문하면서 액터 생성 등을 통해 시각화.
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

	// === 탐색 과정 시각화 설정 ===
	void SetVisualization(bool enabled, int visitDelayMs = 60, int pathDelayMs = 35)
	{
		visualizationEnabled = enabled;
		visualizationVisitDelayMs = visitDelayMs;
		visualizationPathDelayMs = pathDelayMs;
	}

	// === 내부 격자를 콘솔로 그리기 ===
	void ShowGrid();

	// === 최종 경로를 애니메이션으로 그리기 ===
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