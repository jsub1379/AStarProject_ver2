#include "System.h"
#include "Level/MenuLevel.h"
#include "Level/AStarShow.h"

System* System::instance = nullptr;

System::System()
{
	instance = this;

	// ���� ���� �߰�.
	AddLevel(new AStarShow());

	// �޴� ���� ����.
	menuLevel = new MenuLevel();
}

System::~System()
{
	CleanUp();
}

void System::ToggleMenu()
{
	// ȭ�� ����.
	// clear screen ��ɾ� ����.
	system("cls");

	// ��� ó��.
	showMenu = !showMenu;

	if (showMenu)
	{
		// ���� ������ �ڷ� �б�.
		backLevel = mainLevel;

		// �޴� ������ ���� ������ ����.
		mainLevel = menuLevel;
	}
	else
	{
		// ���� ������ ���� ������ ����.
		mainLevel = backLevel;
	}
}

void System::CleanUp()
{
	// �̶��� Engine�� mainLevel�� menuLevel.
	if (showMenu)
	{
		// ���� ���� ����.
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	//// mainLevel�� ���� ���� -> �̶��� Engine���� �ϴ����� �����ϸ� ��.
	//else
	//{
	//
	//}

	SafeDelete(menuLevel);
	Engine::CleanUp();
}

System& System::Get()
{
	return *instance;
}