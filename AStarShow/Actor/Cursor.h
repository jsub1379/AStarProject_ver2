#pragma once

#include "Actor/Actor.h"


class Cursor : public Actor
{
    RTTI_DECLARATIONS(Cursor, Actor)

public:
    Cursor(const Vector2& position);

    virtual void BeginPlay() override;
    virtual void Tick(float deltaTime) override;

private:
    // �������̽� ���� ����.
    class ICanPlayerMove* canPlayerMoveInterface = nullptr;

};