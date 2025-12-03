#include "pch.h"
#include "CBullet.h"

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
}

int CBullet::Update()
{
    __super::Update_Rect();

    m_tInfo.fY -= m_fSpeed;

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
