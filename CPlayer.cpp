#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CSubBullet.h"

CPlayer::CPlayer() 
	:m_pBullet(nullptr), m_pSubBullet(nullptr)
{
	
	ZeroMemory(&m_tSubWeapon, sizeof(POINT));
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX >> 1, WINCY >> 1, 50.f, 50.f };

	m_fSpeed = 5.f;
	m_fDistance = 50.f;
	m_fRotate = 0;

}

int CPlayer::Update()
{
	CObj::Update_Rect();


	m_fRotate -= 2;

	Key_Input();

	static DWORD dwLastFire = 0;
	DWORD dwNow = GetTickCount();

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (dwNow - dwLastFire > 100) //  플레이어 평타 쿨타임 조절
		{
			m_pBullet->push_back(Create_Bullet());
			dwLastFire = dwNow;
		}
	}

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
			m_pSubBullet->push_back(Create_SubBullet());
			dwLastFire = dwNow;
		}
	}

	//m_pSubBullet->push_back(Create_SubBullet());

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);

	Ellipse(hDC, (int)m_tSubWeapon.x - 10, (int)m_tSubWeapon.y - 10,
				(int)m_tSubWeapon.x + 10, (int)m_tSubWeapon.y + 10);

}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{

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

	}

CObj *CPlayer::Create_Bullet()
{
	CObj* pBullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY-25);
	return pBullet;
}

CObj* CPlayer::Create_SubBullet()
{
	CObj* pBullet = CAbstractFactory<CSubBullet>::Create(m_tSubWeapon.x, m_tSubWeapon.y - 10);
	return pBullet;
}




