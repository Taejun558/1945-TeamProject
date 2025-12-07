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
	const RECT* Get_Rect() const { return &m_tRect; }

	void	Set_Pos(float fX, float fY)
	{
		m_tInfo.fX = fX;
		m_tInfo.fY = fY;
	}

	void	Set_Angle(float fAngle)
	{
		m_fAngle = fAngle;
	}

	void	Set_Dead() { m_bDead = true; }
	bool	Get_Dead() { return m_bDead; }

	float	Get_Dmg() { return m_iDmg; }

	float	Get_HP() { return m_fHP; }

	void Take_Dmg (float dmg){m_fHP -= dmg;}

	void	Drop_Item();

//	void	Create_Item();


protected:
	INFO	m_tInfo;
	RECT	m_tRect;
	CObj* m_pTarget;

	float	m_fSpeed;
	float	m_fDistance;
	float	m_fRotate;
	bool	m_bDead;
	float	m_fAngle;
	int		m_iDmg;
	float	m_fHP;
	float	m_fMaxHP;
};

