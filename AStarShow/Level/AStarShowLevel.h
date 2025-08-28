#pragma once

#include "Level/Level.h"


class AStarShowLevel : public Level
{
	RTTI_DECLARATIONS(AStarShowLevel, Level)
public:
	AStarShowLevel();

	// 가능은 함.
private:
	virtual void Render() override;

private:

	// 맵 파일을 읽어서 게임 객체 생성하는 함수.
	void ReadMapFile(const char* filename);


private:

	// 게임 클리어 여부 확인 변수.
	bool isGameClear = false;
};