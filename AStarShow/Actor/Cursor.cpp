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
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(1);
}

void Cursor::BeginPlay()
{
	super::BeginPlay();

	// �������̽� ������.
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

	//esc ������ �޴�
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		System::Get().ToggleMenu();
		return;
	}

	// �̵� ���� - �̵��ϱ� ���� �̵��� ��ġ�� �� �� �ִ��� �Ǵ� �� �̵�.
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
		// �̵� ���� �̵� �������� Ȯ��.
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

