#include "pch.h"
#include "CBossMonster.h"
#include "CObj.h"
#include "Define.h"

CBossMonster::CBossMonster()
{
	m_fAngle = 90;
}

CBossMonster::~CBossMonster()
{
    Release();
}

void CBossMonster::Initialize()
{
    m_tInfo.fCX = 150.f;
    m_tInfo.fCY = 150.f;

    m_fSpeed = 1.f;

	m_fHP = 1000.f;
	m_fMaxHP = 1000.f;
	m_iDmg = 1.f;
}

int CBossMonster::Update()
{
	if (m_bDead)
	    return DEAD;

	static DWORD dwLastMove = 0;
	DWORD dwNow = GetTickCount();


		if (dwNow - dwLastMove > 3000)
		{
			m_fAngle = rand() % 361;
			dwLastMove = dwNow;
		}

	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY += m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	ResolveCollision();
	


	__super::Update_Rect();

    return NOEVENT;
}

void CBossMonster::Late_Update()
{
}

void CBossMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);



		TCHAR szText[32];
		swprintf_s(szText, TEXT("Boss HP : %0.f"), m_fHP);
		TextOut(hDC, 440, 10, szText, lstrlen(szText));

		Rectangle(hDC, 380, 30, 380 + m_fMaxHP /5, 38); // 체력바

		MoveToEx(hDC, 380, 35, nullptr);
		for (int i = 0; i < m_fHP / 5; i++)
		{											//현재 체력
			MoveToEx(hDC, 380 + i, 30, nullptr);
			LineTo(hDC, 380 + i, 38);
		}

		FaceRender(hDC);
	
	
}

void CBossMonster::Release()
{
}


void CBossMonster::ResolveCollision()
{
	float fRandAngle;
	if (m_tRect.right >= WINCX)
	{
		m_tInfo.fX -= 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
	if (m_tRect.left <= 0)
	{
		m_tInfo.fX += 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
	if (m_tRect.top <= 0)
	{
		m_tInfo.fY += 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
	if (m_tRect.bottom >= WINCY)
	{
		m_tInfo.fY -= 10.f;
		fRandAngle = rand() % 360;
		m_fAngle = fRandAngle;
	}
}


void CBossMonster::FaceRender(HDC hDC)
{
	MoveToEx(hDC, m_tRect.left + 35, m_tRect.top + 50, nullptr);
	LineTo(hDC, m_tRect.left + 65, m_tRect.top + 45);					//왼쪽 눈
	LineTo(hDC, m_tRect.left + 50, m_tRect.top + 65);
	LineTo(hDC, m_tRect.left + 35, m_tRect.top + 50);


	MoveToEx(hDC, m_tRect.right - 35, m_tRect.top + 50, nullptr);
	LineTo(hDC, m_tRect.right - 65, m_tRect.top + 45);
	LineTo(hDC, m_tRect.right - 50, m_tRect.top + 65);					// 오른쪽 눈
	LineTo(hDC, m_tRect.right - 35, m_tRect.top + 50);


	MoveToEx(hDC, m_tRect.left + 73, m_tRect.top + 75, nullptr);
	LineTo(hDC, m_tRect.left + 77, m_tRect.top + 75);
	LineTo(hDC, m_tRect.left + 75, m_tRect.top + 80);
	LineTo(hDC, m_tRect.left + 73, m_tRect.top + 75);					//코


	MoveToEx(hDC, m_tRect.left + 45, m_tRect.top + 110, nullptr);
	LineTo(hDC, m_tRect.right - 45, m_tRect.top + 110);					//입


	MoveToEx(hDC, m_tRect.left + 60, m_tRect.top + 110, nullptr);
	LineTo(hDC, m_tRect.left + 65, m_tRect.top + 130);					//왼니
	LineTo(hDC, m_tRect.left + 70, m_tRect.top + 110);

	MoveToEx(hDC, m_tRect.right - 60, m_tRect.top + 110, nullptr);
	LineTo(hDC, m_tRect.right - 65, m_tRect.top + 130);					//오른니
	LineTo(hDC, m_tRect.right - 70, m_tRect.top + 110);
}