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

private:
    void        Key_Input();
    CObj*       Create_Bullet();
    CObj*       Create_SubBullet();
public:
    void    Set_Bullet(list<CObj*>* pBullet)
    {
        m_pBullet = pBullet;
    }

    void    Set_SubBullet(list<CObj*>* pSubBullet)
    {
        m_pSubBullet = pSubBullet;
    }

private:
    list<CObj*>* m_pBullet;
    list<CObj*>* m_pSubBullet;


    POINT   m_tSubWeapon;
};

