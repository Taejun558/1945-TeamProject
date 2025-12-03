#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void	Initialize()	PURE;
	virtual int		Update()		PURE;
	virtual	void	Late_Update()	PURE;
	virtual void	 Render(HDC hDC)PURE;
	virtual void	Release()		PURE;

public:
	INFO Get_Info() { return m_tInfo; }
	void	Update_Rect();

	void	Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}

protected:
	INFO	m_tInfo;
	RECT	m_tRect;

	float	m_fSpeed;
	float	m_fDistance;
	float	m_fRotate;

};

