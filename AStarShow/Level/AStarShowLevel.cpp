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
	// A*���� grid[x][y]�� �����ϹǷ�, �ٱ�=width(x), ����=height(y)
	std::vector<std::vector<char>> grid(mapWidth, std::vector<char>(mapHeight, ' '));

	// 1) �ٴ�(:) ���� ä���
	for (Actor* const a : actors)
	{
		const int x = static_cast<int>(a->Position().x);
		const int y = static_cast<int>(a->Position().y);
		if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) continue;

		if (a->As<Ground>()) {
			grid[x][y] = ':';      // �̵� ������ �⺻ Ÿ��
		}
	}

	// 2) ��/��ֹ�/����/��ǥ�� ����� (�켱������ �� ����)
	for (Actor* const a : actors)
	{
		const int x = static_cast<int>(a->Position().x);
		const int y = static_cast<int>(a->Position().y);
		if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) continue;

		if (a->As<Wall>()) { grid[x][y] = '@'; continue; } // ����
		if (a->As<Obstacle>()) { grid[x][y] = '#'; continue; } // ����
		if (a->As<Start>()) { grid[x][y] = 'S'; continue; } // ����
		if (a->As<Goal>()) { grid[x][y] = 'G'; continue; } // ��ǥ
	}

	return grid;
}



bool AStarShowLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
	bool blocked = false;
	// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ���� ���.
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			// ���̰ų� ��ֹ��̸� �̵� �Ұ�.
			if (actor->As<Wall>()||actor->As<Obstacle>())
			{
				blocked = true;
			}
		}

	}
	if (blocked) return false;
	return true;
}

