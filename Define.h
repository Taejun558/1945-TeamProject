#pragma once

#define		WINCX 800
#define		WINCY 600

#define		PURE  = 0

#define		NOEVENT 0
#define		DEAD    1

#define		PI		3.141592f

#define		RANDOM_800	rand()%800

enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_SUBBULLET, OBJ_ULTIMATE, OBJ_MONSTER, OBJ_MONBULLET,OBJ_ITEM,OBJ_BOSSMONSTER, OBJ_END };

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