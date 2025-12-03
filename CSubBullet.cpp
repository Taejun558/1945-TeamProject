#include "pch.h"
#include "CSubBullet.h"

CSubBullet::CSubBullet()
{
}

CSubBullet::~CSubBullet()
{
	Release();
}

void CSubBullet::Initialize()
{
	m_tInfo.fCX = 7.f;
	m_tInfo.fCY = 7.f;

	m_fSpeed = 2.f;
}

int CSubBullet::Update()
{
	__super::Update_Rect();

	m_tInfo.fY -= m_fSpeed;

	return NOEVENT;
}

void CSubBullet::Late_Update()
{
}

void CSubBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CSubBullet::Release()
{
}
