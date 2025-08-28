#include "AStarShowLevel.h"

#include "Actor/Ground.h"
#include "Actor/Obstacle.h"
#include "Actor/Wall.h"

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Utils/Utils.h"

#include <iostream>
AStarShowLevel::AStarShowLevel()
{
	ReadMapFile("map_test.txt");
}

void AStarShowLevel::Render()
{
	super::Render();

	if (isGameClear)
	{
		Utils::SetConsolePosition({ 0, 0 });
		Utils::SetConsoleTextColor(
			static_cast<WORD>(Color::White)
		);

		std::cout << "Game Clear!";
	}
}
void AStarShowLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�.
	char filepath[256] = { };
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// ����ó��.
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ����: " << filename << "\n";
		return;
	}

	// �Ľ�(Parcing, �ؼ�).
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);


	// �迭 ��ȸ�� ���� �ε��� ����.
	int index = 0;

	// ���ڿ� ���� ��.
	int size = (int)readSize;

	// x, y ��ǥ.
	Vector2 position;

	// ���� �迭 ��ȸ.
	while (index < size)
	{
		// �� ���� Ȯ��.
		char mapCharacter = buffer[index];
		++index;

		// ���� ���� ó��.
		if (mapCharacter == '\n')
		{
			// ���� �ٷ� �ѱ�鼭, x ��ǥ �ʱ�ȭ.
			++position.y;
			position.x = 0;
			continue;
		}

		// �� ���� ���� ó��.
		switch (mapCharacter)
		{
		case ':':
			AddActor(new Ground(position));
			break;
		case '#':
			AddActor(new Obstacle(position));
			break;
		case '@':
			AddActor(new Wall(position));
			break;
		default:
			break;
		}

		// x ��ǥ ���� ó��.
		++position.x;
	}

	// ���� ����.
	delete[] buffer;

	// ���� �ݱ�.
	fclose(file);
}