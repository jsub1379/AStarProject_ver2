#include "Goal.h"

Goal::Goal(const Vector2& position)
	: Actor('G', Color::White, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(2);
}

