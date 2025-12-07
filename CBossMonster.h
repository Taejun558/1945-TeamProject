#pragma once
#include "CObj.h"


class CBossMonster : public CObj
{
public:
	CBossMonster();
	virtual ~CBossMonster();

public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;

	void FaceRender(HDC hDC);
	void Release() override;

	void ResolveCollision();



};

