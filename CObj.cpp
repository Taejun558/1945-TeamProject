#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f), m_bDead(false), m_fDistance(0.f),m_fAngle(0.f)
{
	memset(&m_tInfo, 0, sizeof(INFO));
	memset(&m_tRect, 0, sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= LONG(m_tInfo.fX - (m_tInfo.fCX / 2.f));
	m_tRect.top		= LONG(m_tInfo.fY - (m_tInfo.fCY / 2.f));
	m_tRect.right	= LONG(m_tInfo.fX + (m_tInfo.fCX / 2.f));
	m_tRect.bottom	= LONG(m_tInfo.fY + (m_tInfo.fCY / 2.f));
}

void CObj::Drop_Item()
{
	int iProb = rand() & 10;

	if (iProb == 7)
	{
//		Create_Item();
	}
}
