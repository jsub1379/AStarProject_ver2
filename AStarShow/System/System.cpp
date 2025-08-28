#include "System.h"
#include "Level/MenuLevel.h"
#include "Level/AStarShow.h"

System* System::instance = nullptr;

System::System()
{
	instance = this;

	// 메인 레벨 추가.
	AddLevel(new AStarShow());

	// 메뉴 레벨 생성.
	menuLevel = new MenuLevel();
}

System::~System()
{
	CleanUp();
}

void System::ToggleMenu()
{
	// 화면 정리.
	// clear screen 명령어 실행.
	system("cls");

	// 토글 처리.
	showMenu = !showMenu;

	if (showMenu)
	{
		// 게임 레벨을 뒤로 밀기.
		backLevel = mainLevel;

		// 메뉴 레벨을 메인 레벨로 설정.
		mainLevel = menuLevel;
	}
	else
	{
		// 게임 레벨을 메인 레벨로 설정.
		mainLevel = backLevel;
	}
}

void System::CleanUp()
{
	// 이때는 Engine의 mainLevel이 menuLevel.
	if (showMenu)
	{
		// 게임 레벨 제거.
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	//// mainLevel이 게임 레벨 -> 이때는 Engine에서 하던데로 정리하면 됨.
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