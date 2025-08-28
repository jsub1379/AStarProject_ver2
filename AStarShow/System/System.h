#pragma once

#include "Engine.h"

class Level;
class System : public Engine
{
public:
	System();
	~System();

	// �޴� ��ȯ �Լ�.
	void ToggleMenu();

	virtual void CleanUp() override;

	static System& Get();

private:

	// �޴� ����.
	Level* menuLevel = nullptr;

	// ȭ�鿡 �Ⱥ��̴� ����.
	Level* backLevel = nullptr;

	// ���� �޴� ������ �����ְ� �ִ����� ��Ÿ��.
	bool showMenu = false;

	static System* instance;
};