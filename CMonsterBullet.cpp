#include "pch.h"
#include "CMonsterBullet.h"
#include "CObjMgr.h"
#include "Define.h"

CMonsterBullet::CMonsterBullet()
{
}

CMonsterBullet::~CMonsterBullet()
{
	Release();
}

void CMonsterBullet::Initialize()
{
    m_tInfo.fCX = 8.f;
    m_tInfo.fCY = 8.f;

    m_fSpeed = 5.f;
    m_iDmg = 1;
    m_fHP = 1;
}

int CMonsterBullet::Update()
{
    if (m_fHP <= 0)
        m_bDead = true;

    if (m_bDead)
        return DEAD;
    __super::Update_Rect();

    m_tInfo.fY += m_fSpeed;

	return NOEVENT;
}

void CMonsterBullet::Late_Update()
{
}

void CMonsterBullet::Render(HDC hDC)
{
  //  Ellipse(hDC,
  //      m_tRect.left,
  //      m_tRect.top,
  //      m_tRect.right,
  //      m_tRect.bottom);

    for (int i(0); i < m_tInfo.fCX; i++)
    {
        MoveToEx(hDC, m_tRect.left +i, m_tRect.top, nullptr);
        LineTo(hDC, m_tRect.left + i, m_tRect.bottom);
    }
}

void CMonsterBullet::Release()
{
}
