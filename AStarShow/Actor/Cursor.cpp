#include "Cursor.h"
#include "Input.h"
#include "System/System.h"
#include "Actor/Wall.h"
#include "INterface/ICanPlayerMove.h"
#include "Level/level.h"

#include <vector>
#include <Windows.h>
#include <iostream>

Cursor::Cursor(const Vector2& position)
	: Actor('+', Color::White, position)
{
	// 그릴 때 사용할 정렬 순서 설정.
	SetSortingOrder(1);
}

void Cursor::BeginPlay()
{
	super::BeginPlay();

	// 인터페이스 얻어오기.
	if (GetOwner())
	{
		canPlayerMoveInterface
			= dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owner level to ICanPlayerMove.\n";
		}
	}
}


void Cursor::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//esc 누르면 메뉴
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		System::Get().ToggleMenu();
		return;
	}

	// 이동 로직 - 이동하기 전에 이동할 위치로 갈 수 있는지 판단 후 이동.
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		bool result = canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x - 1, Position().y)
		);

		if (result)
		{
			Vector2 position = Position();
			position.x -= 1;
			SetPosition(position);
		}
	}
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		// 이동 전에 이동 가능한지 확인.
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x + 1, Position().y)))
		{
			Vector2 position = Position();
			position.x += 1;
			SetPosition(position);
		}
	}


	if (Input::Get().GetKeyDown(VK_UP))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, Position().y - 1)))
		{
			Vector2 position = Position();
			position.y -= 1;
			SetPosition(position);
		}
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, Position().y + 1)))
		{
			Vector2 position = Position();
			position.y += 1;
			SetPosition(position);
		}
	}

}

