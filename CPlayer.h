#pragma once
#include "CObj.h"
class CPlayer :
    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Activate_Ult();
    void        FireMultiShot();
private:
    void        Key_Input();
    CObj*       Create_Bullet();
    CObj*       Create_SubBullet();
    CObj*       Create_Ultimate();
    CObj*       Create_MultiBullet();


private:

    bool m_bUltimate = false;
    DWORD m_dwUltStartTime = 0;



    POINT   m_tSubWeapon;
};

