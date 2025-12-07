#include "pch.h"
#include "CMainGame.h"
#include "CAbstractFactory.h"
#include "CUltimate.h"
#include "CObjMgr.h"
#include "CMonster.h"
#include "CCollisionMgr.h"
#include "CObj.h"

CMainGame::CMainGame()
	:m_dwTime(GetTickCount())
	, m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}
CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand(unsigned int((time(NULL))));

	m_hDC = GetDC(g_hWnd);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());
	
}
void CMainGame::Update()
{
	static DWORD dwLastFire = 0;
	DWORD dwNow = GetTickCount();
	if (dwNow - dwLastFire > 5000)
	{
		for (int i = 0; i < 15; ++i)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster>::
				Create(rand() % WINCX, rand() % 200 - 100));
		}
		dwLastFire = dwNow;
		dwNow = GetTickCount();
	}
	
	CObjMgr::Get_Instance()->Update();

}

void CMainGame::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

#pragma region FPS Ç¥½Ã
	CObjMgr::Get_Instance()->Render(m_hDC);

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
#pragma endregion
}

void CMainGame::Release()
{
	CObjMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
