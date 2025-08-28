#include "AStarShow.h"

#include "Actor/Wall.h"
#include "Actor/Obstacle.h"
#include "Actor/Ground.h"
#include "Actor/Cursor.h"

#include <iostream>

AStarShow::AStarShow()
{
	ReadMapFile("../Assets/map_test.txt");
}

void AStarShow::Render()
{
	super::Render();

}
void AStarShow::ReadMapFile(const char* filename)
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
	while (!feof(file))
	{
		fgets(buffer, 256, file);
		int lineLength = (int)strlen(buffer);

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
	position.x = 3;
	position.y = 3;
	AddActor(new Cursor(position));
	   

	fclose(file);

}

bool AStarShow::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
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