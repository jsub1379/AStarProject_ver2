#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
#include "AStar/Astar.h"
#include <vector>

class AStarShowLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(AStarShowLevel, Level)

public:
	AStarShowLevel();

	// Inherited via ICanPlayerMove.
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;

	std::vector<std::vector<char>> SnapshotGrid();

	// ������ ��.
private:
	virtual void Render() override;

private:

	// �� ������ �о ���� ��ü �����ϴ� �Լ�.
	void ReadMapFile(const char* filename);


	// ���� Ŭ���� Ȯ���ϴ� �Լ�.
	bool CheckGameClear();



private:
	// ���� Ŭ��� ���� ����.
	int targetScore = 0;

	// ���� Ŭ���� ���� Ȯ�� ����.
	bool isGameClear = false;

	int mapWidth = 0;
	int mapHeight = 0;


};