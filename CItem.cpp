#include "pch.h"
#include "CItem.h"

CItem::CItem()
{
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
    m_tInfo.fCX = 30.f;
    m_tInfo.fCY = 30.f;

    m_fSpeed = 3.f;

}

int CItem::Update()
{
    if (m_bDead)
        return DEAD;

    __super::Update_Rect();

    m_tInfo.fY += m_fSpeed;

	return NOEVENT;
}

void CItem::Late_Update()
{
}

void CItem::Render(HDC hDC)
{
    Rectangle(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);


#pragma region ¹°À½Ç¥
    MoveToEx(hDC, m_tInfo.fX - 5, m_tInfo.fY - 10, nullptr);
    LineTo(hDC, m_tInfo.fX + 5, m_tInfo.fY - 10);

    LineTo(hDC, m_tInfo.fX + 5, m_tInfo.fY - 4);

    LineTo(hDC, m_tInfo.fX, m_tInfo.fY);

    MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, nullptr);
    LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 7);

    MoveToEx(hDC, (m_tInfo.fX), m_tInfo.fY + 9, nullptr);
    LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 11);

#pragma endregion
}

void CItem::Release()
{
}