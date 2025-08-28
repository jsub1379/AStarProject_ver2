#include "Obstacle.h"

Obstacle::Obstacle(const Vector2& position)
	: Actor('#', Color::White, position)
{
	// 그릴 때 사용할 정렬 순서 설정.
	SetSortingOrder(0);
}