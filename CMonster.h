#pragma once
#include "CObj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();
public:

	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	CObj* Create_Bullet();

private:
	float fLimitY = rand() % 100 + 100.f;

	float m_fTargetX;
	float m_fTargetY;


	DWORD m_dwLastFire = 0;
};

