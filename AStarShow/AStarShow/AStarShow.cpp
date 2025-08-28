#include "AStarShow.h"
#include "Level/AStarShowLevel.h"

AStarShow* AStarShow::instance = nullptr;

AStarShow::AStarShow()
{
	instance = this;

	// ���� ���� �߰�.
	AddLevel(new AStarShowLevel());

}

AStarShow::~AStarShow()
{
	CleanUp();
}

//void AStarShow::ToggleMenu()
//{
//	// ȭ�� ����.
//	// clear screen ��ɾ� ����.
//	system("cls");
//
//	// ��� ó��.
//	showMenu = !showMenu;
//
//	if (showMenu)
//	{
//		// ���� ������ �ڷ� �б�.
//		backLevel = mainLevel;
//
//		// �޴� ������ ���� ������ ����.
//		mainLevel = menuLevel;
//	}
//	else
//	{
//		// ���� ������ ���� ������ ����.
//		mainLevel = backLevel;
//	}
//}

void AStarShow::CleanUp()
{
	// �̶��� Engine�� mainLevel�� menuLevel.
	//if (showMenu)
	//{
	//	// ���� ���� ����.
	//	SafeDelete(backLevel);
	//	mainLevel = nullptr;
	//}
	//// mainLevel�� ���� ���� -> �̶��� Engine���� �ϴ����� �����ϸ� ��.
	//else
	//{
	//
	//}

	//SafeDelete(menuLevel);
	Engine::CleanUp();
}

AStarShow& AStarShow::Get()
{
	return *instance;
}