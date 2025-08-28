#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"

class AStarShow : public Level
{
	RTTI_DECLARATIONS(AStarShow, Level)
public:
	AStarShow();

	// Inherited via ICanPlayerMove.
	bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition);

	// ������ ��.
private:
	virtual void Render() override;

private:

	// �� ������ �о ���� ��ü �����ϴ� �Լ�.
	void ReadMapFile(const char* filename);

	// ���� Ŭ���� Ȯ���ϴ� �Լ�.
	bool CheckGameClear();

private:
	// ���� Ŭ��� ���� ����.
	int targetScore = 0;

	// ���� Ŭ���� ���� Ȯ�� ����.
	bool isGameClear = false;
};