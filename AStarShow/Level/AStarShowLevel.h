#pragma once

#include "Level/Level.h"


class AStarShowLevel : public Level
{
	RTTI_DECLARATIONS(AStarShowLevel, Level)
public:
	AStarShowLevel();

	// ������ ��.
private:
	virtual void Render() override;

private:

	// �� ������ �о ���� ��ü �����ϴ� �Լ�.
	void ReadMapFile(const char* filename);


private:

	// ���� Ŭ���� ���� Ȯ�� ����.
	bool isGameClear = false;
};