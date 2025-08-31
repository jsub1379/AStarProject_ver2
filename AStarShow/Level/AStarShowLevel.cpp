#include "AStarShowLevel.h"
#include "AStar/AStar.h"
#include "Input.h"

#include "Actor/Wall.h"
#include "Actor/Obstacle.h"
#include "Actor/Ground.h"
#include "Actor/Cursor.h"
#include "Actor/Start.h"
#include "Actor/Goal.h"

#include <iostream>
#include <Windows.h>

AStarShowLevel::AStarShowLevel()
{
	ReadMapFile("../Assets/map_test.txt");
}

void AStarShowLevel::Render()
{
	super::Render();


}
void AStarShowLevel::ReadMapFile(const char* filename)
{

	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");
	if (file == nullptr)
	{
		std::cout << "cannot find file\n";
		return;
	}

	Vector2 position;

	char buffer[256] = { };
	int lineLength = 0;
	while (!feof(file))
	{
		fgets(buffer, 256, file);
		lineLength = (int)strlen(buffer);


		for (int ix = 0; ix < lineLength; ++ix)
		{

			char mapCharacter = buffer[ix];

			switch (mapCharacter)
			{
			case '@':
				AddActor(new Wall(position));
				break;
			case ':':
				AddActor(new Ground(position));
				break;
			case '#':
				AddActor(new Obstacle(position));
				break;
			default:
				std::cout << ' ';
				break;
			}

			++position.x;
		}

		position.x = 0;
		++position.y;
	}
	mapWidth = lineLength;
	mapHeight = position.y;

	position.x = 3;
	position.y = 3;
	AddActor(new Cursor(position));

	fclose(file);

}

std::vector<std::vector<char>> AStarShowLevel::SnapshotGrid()
{
	// A*에서 grid[x][y]로 접근하므로, 바깥=width(x), 안쪽=height(y)
	std::vector<std::vector<char>> grid(mapWidth, std::vector<char>(mapHeight, ' '));

	// 1) 바닥(:) 먼저 채우기
	for (Actor* const a : actors)
	{
		const int x = static_cast<int>(a->Position().x);
		const int y = static_cast<int>(a->Position().y);
		if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) continue;

		if (a->As<Ground>()) {
			grid[x][y] = ':';      // 이동 가능한 기본 타일
		}
	}

	// 2) 벽/장애물/시작/목표로 덮어쓰기 (우선순위가 더 강함)
	for (Actor* const a : actors)
	{
		const int x = static_cast<int>(a->Position().x);
		const int y = static_cast<int>(a->Position().y);
		if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) continue;

		if (a->As<Wall>()) { grid[x][y] = '@'; continue; } // 막힘
		if (a->As<Obstacle>()) { grid[x][y] = '#'; continue; } // 막힘
		if (a->As<Start>()) { grid[x][y] = 'S'; continue; } // 시작
		if (a->As<Goal>()) { grid[x][y] = 'G'; continue; } // 목표
	}

	return grid;
}



bool AStarShowLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
	bool blocked = false;
	// 플레이어가 이동하려는 위치에 박스가 없는 경우.
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			// 벽이거나 장애물이면 이동 불가.
			if (actor->As<Wall>()||actor->As<Obstacle>())
			{
				blocked = true;
			}
		}

	}
	if (blocked) return false;
	return true;
}

