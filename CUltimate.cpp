#include "pch.h"
#include "CUltimate.h"
#include "CAbstractFactory.h"

CUltimate::CUltimate()
{
}

CUltimate::~CUltimate()
{
	Release();
}

void CUltimate::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_fSpeed = 5.f;
	m_iDmg = 100;
}

int CUltimate::Update()
{
	__super::Update_Rect();

	

	DWORD dwNow = GetTickCount();
	DWORD dwUltStart = 0;
	m_tInfo.fY -= m_fSpeed;

	return NOEVENT;
}

void CUltimate::Late_Update()
{
}

void CUltimate::Render(HDC hDC)
{
		Rectangle(hDC, m_tRect.left,
			m_tRect.top ,
			m_tRect.right,
			m_tRect.bottom );
}

void CUltimate::Release()
{
}


