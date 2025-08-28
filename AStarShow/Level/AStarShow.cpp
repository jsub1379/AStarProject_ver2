#include "AStarShow.h"

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
				std::cout << '@';
				break;
			case ':':
				std::cout << ':';
				break;
			case '#':
				std::cout << '#';
				break;
			default:
				std::cout << ' ';
				break;
			}
		}
		std::cout << "\n";
	}


	fclose(file);

}