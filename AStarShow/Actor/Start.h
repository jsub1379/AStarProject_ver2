#pragma once

#include "Actor/Actor.h"

class Start : public Actor
{
    RTTI_DECLARATIONS(Start, Actor)

public:
    Start(const Vector2& position);
};