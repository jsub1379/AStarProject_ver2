#pragma once
#pragma once

#include "Actor/Actor.h"

class Obstacle : public Actor
{
    RTTI_DECLARATIONS(Obstacle, Actor)

public:
    Obstacle(const Vector2& position);
};