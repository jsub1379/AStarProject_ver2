#include "Obstacle.h"

Obstacle::Obstacle(const Vector2& position)
	: Actor('#', Color::White, position)
{
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(0);
}