#include "Start.h"

Start::Start(const Vector2& position)
	: Actor('S', Color::White, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(2);
}

