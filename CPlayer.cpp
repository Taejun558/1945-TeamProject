#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CSubBullet.h"
#include "CUltimate.h"
#include "Define.h"
#include "CObjMgr.h"



CPlayer::CPlayer() 
{
	
	ZeroMemory(&m_tSubWeapon, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX >> 1, WINCY >> 1, 40.f, 60.f };

	m_fSpeed = 5.f;
	m_fDistance = 50.f;
	m_fRotate = 0;
	m_fHP = 50;
	m_fMaxHP = 50;
	m_iDmg = 1;
	

}

int CPlayer::Update()
{
	CObj::Update_Rect();


	m_fRotate -= 2;

	Key_Input();

	






	return NOEVENT;
}

void CPlayer::Late_Update()
{
	m_tSubWeapon.x = long(m_tInfo.fX + m_fDistance * cosf(m_fRotate * (PI / 180.f)));
	m_tSubWeapon.y = long(m_tInfo.fY - m_fDistance * sinf(m_fRotate * (PI / 180.f)));
	


	static DWORD dwLastFire = 0;
	DWORD dwNow = GetTickCount();
		if (dwNow - dwLastFire > 500) // 보조무기 쿨타임 조절
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_SUBBULLET, Create_SubBullet());
			dwLastFire = dwNow;
		}


	


}


void CPlayer::FireMultiShot()
{
		for (int i = 0; i < 9; i++)
		{
			CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY - 25, 20 * i);

			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, pBullet);
		}
}

void CPlayer::Activate_Ult()
{
	if (GetTickCount() - m_dwUltStartTime > 20000) // 20초 쿨타임
	{
		m_bUltimate = true;
		m_dwUltStartTime = GetTickCount();

		for (int i = 0; i < 5; ++i)
		{
			int x(90), y(700);

			if (i % 2 == 0)
				y = 800;
			CObjMgr::Get_Instance()->Add_Object(OBJ_ULTIMATE, CAbstractFactory<CUltimate>::Create(x + i * 160, y));
		}

	

		DWORD dwNow = GetTickCount();
		if (dwNow - m_dwUltStartTime >= 3000)
			//궁 지속시간
			m_bUltimate = false;

		if (m_bUltimate)
		{
			CObjMgr::Get_Instance()->Delete_All(OBJ_MONBULLET);
		}
	}

		
	}

	//m_pSubBullet->push_back(Create_SubBullet());

void CPlayer::Render(HDC hDC)
{
#pragma region 본체
	// 앞부분
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY - 15, nullptr);
	LineTo(hDC, m_tInfo.fX + 10, m_tInfo.fY);
	LineTo(hDC, m_tInfo.fX - 10, m_tInfo.fY);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY - 15);

	// 몸체
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 22);

	// 좌 날개
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 7, nullptr);
	LineTo(hDC, m_tInfo.fX - 20, m_tInfo.fY + 15);

	// 우 날개
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 7, nullptr);
	LineTo(hDC, m_tInfo.fX + 20, m_tInfo.fY + 15);

	// 꼬리 
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 22, nullptr);
	LineTo(hDC, m_tInfo.fX - 10, m_tInfo.fY + 30);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY + 22, nullptr);
	LineTo(hDC, m_tInfo.fX + 10, m_tInfo.fY + 30);
	LineTo(hDC, m_tInfo.fX - 10, m_tInfo.fY + 30);

#pragma endregion

#pragma region 보조무기
	Ellipse(hDC, (int)m_tSubWeapon.x - 10, (int)m_tSubWeapon.y - 10,     //보조무기
				(int)m_tSubWeapon.x + 10, (int)m_tSubWeapon.y + 10);
#pragma endregion



#pragma region 체력

	TCHAR szText[32];
	swprintf_s(szText, TEXT("HP : %0.f"), m_fHP);
	TextOut(hDC, 10, 10, szText, lstrlen(szText));

	Rectangle(hDC, 10, 30, 10 + m_fMaxHP * 4, 40); // 체력바




	MoveToEx(hDC, 10, 30, nullptr);
	for (int i = 0; i < m_fHP*4; i++)
	{											//현재 체력
		MoveToEx(hDC, 10 + i, 30, nullptr);
		LineTo(hDC, 10 + i, 40);
	}

#pragma endregion


}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{

#pragma region 플레이어 이동

	if (GetAsyncKeyState(VK_RIGHT))	
{
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX += m_fSpeed / sqrtf(2.f);
		m_tInfo.fY += m_fSpeed / sqrtf(2.f);
	}

	else
	{
		m_tInfo.fX += m_fSpeed;
	}		
}

else if (GetAsyncKeyState(VK_LEFT))
{ 
	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fX -= m_fSpeed / sqrtf(2.f);
		m_tInfo.fY += m_fSpeed / sqrtf(2.f);
	}
	else
    	m_tInfo.fX -= m_fSpeed; 
}

else if (GetAsyncKeyState(VK_UP))
{ 
	m_tInfo.fY -= m_fSpeed; 
}

else if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

#pragma endregion

#pragma region 플레이어 평타발사

	static DWORD dwLastFire = 0;
	DWORD dwNow = GetTickCount();

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (dwNow - dwLastFire > 100) //  플레이어 평타 쿨타임 조절
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, Create_Bullet());
			dwLastFire = dwNow;
		}
	}

#pragma endregion


//궁극기	
	if (GetAsyncKeyState('R') & 0x8000)
		Activate_Ult();
}

CObj *CPlayer::Create_Bullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY-25, 90);
	return pBullet;
}

CObj* CPlayer::Create_SubBullet()
{
	CObj* pBullet = CAbstractFactory<CSubBullet>::Create(m_tSubWeapon.x, m_tSubWeapon.y - 10);
	return pBullet;
}

CObj* CPlayer::Create_MultiBullet()
{
	for (int i(0); i<9; i++)
	{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY - 25, 20*i );
	

	return pBullet;
	}
}

CObj*	CPlayer::Create_Ultimate()
{
	CObj* pUlt = CAbstractFactory<CUltimate>::Create();
	return pUlt;
}
