#pragma once

// dll �ܺη� ���ø� ������ �� �߻��ϴ� ��� ��Ȱ��ȭ.
#pragma warning(disable: 4251)
// ���� ������ �ּҸ� ��ȯ�� �� �߻��ϴ� ��� ��Ȱ��ȭ.
#pragma warning(disable: 4172)

#include <stdlib.h>

#if BuildEngineDLL
#define Engine_API __declspec(dllexport)
#else
#define Engine_API __declspec(dllimport)
#endif


// �޸� ���� �Լ�.
template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T*& target)
{
	if (target)
	{
		delete[] target;
		target = nullptr;
	}
}