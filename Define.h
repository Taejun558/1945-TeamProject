#pragma once

#define		WINCX 800
#define		WINCY 600

#define		PURE  = 0

#define		NOEVENT 0
#define		DEAD    1

#define		PI		3.141592f

#define		ULTIMATE_COUNT	3;

enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_SUBBULLET, OBJ_END };

extern HWND g_hWnd;

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;

}INFO;

template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}