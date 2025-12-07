#include "pch.h"
#include "CSubBullet.h"
#include "CObjMgr.h"

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

	m_fSpeed = 3.f;
	m_iDmg = 1;
	m_fHP = 1;
}

int CSubBullet::Update()
{
	if (m_fHP <= 0)
		m_bDead = true;

	if (m_bDead)
		return DEAD;

	__super::Update_Rect();

	return NOEVENT;
}

void CSubBullet::Late_Update()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJ_MONSTER, this);

	if (m_pTarget)
	{
		float fWidth(0.f), fHeight(0.f), fDiagonal(0.f), fRadian(0.f);

		fWidth = m_pTarget->Get_Info().fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info().fY - m_tInfo.fY;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		fRadian = acosf(fWidth / fDiagonal);

		m_fAngle = fRadian * (180.f / PI);

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
		{
			m_fAngle *= -1.f;
		}
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * (PI / 180.f));

	}
	else
	{
		m_tInfo.fY -= m_fSpeed;
	}


	
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
