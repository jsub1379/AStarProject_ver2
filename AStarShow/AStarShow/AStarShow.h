#pragma once

#include "Engine.h"

class Level;
class AStarShow : public Engine
{
public:
	AStarShow();
	~AStarShow();

	// �޴� ��ȯ �Լ�.
	//void ToggleMenu();

	virtual void CleanUp() override;

	static AStarShow& Get();

private:

	// �޴� ����.
	//Level* menuLevel = nullptr;

	// ȭ�鿡 �Ⱥ��̴� ����.
	//Level* backLevel = nullptr;

	// ���� �޴� ������ �����ְ� �ִ����� ��Ÿ��.
	//bool showMenu = false;

	static AStarShow* instance;
};