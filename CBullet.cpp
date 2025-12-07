#include "pch.h"
#include "CBullet.h"
#include "Define.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
    Release();
}

void CBullet::Initialize()
{
    m_tInfo.fCX = 10.f;
    m_tInfo.fCY = 10.f;
    m_fSpeed = 5.f;
    m_iDmg = 2;
    m_fHP = 1;
}

int CBullet::Update()
{
    if (m_fHP <= 0)
        m_bDead = true;

    if (m_bDead)
        return DEAD;
    __super::Update_Rect();


    m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
    m_tInfo.fY -=  m_fSpeed * sinf(m_fAngle * (PI / 180.f));

    return NOEVENT;
}

void CBullet::Late_Update()
{

}

void CBullet::Render(HDC hDC)
{
    Ellipse(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);
}

void CBullet::Release()
{
}
