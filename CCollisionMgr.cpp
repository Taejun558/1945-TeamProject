#include "pch.h"
#include "CCollisionMgr.h"
#include "CPlayer.h"

void CCollisionMgr::Collision_Ultimate(list<CObj*>& Dst, list<CObj*>& Src)
{
    RECT rc{};

    for (auto& pDst : Dst)
    {
        for (auto& pSrc : Src)
        {
            if (IntersectRect(&rc, pDst->Get_Rect(), pSrc->Get_Rect()))
            {
                pDst->Take_Dmg(pSrc->Get_Dmg());
                pSrc->Take_Dmg(pDst->Get_Dmg());
            }
        }
    }
}

void CCollisionMgr::Collision_Item(list<CObj*>& Player, list<CObj*>&Item )
{
    RECT rc{};

    for (auto& pPlayer : Player)
    {
        for (auto& pItem : Item)
        {
            if (IntersectRect(&rc, pPlayer->Get_Rect(), pItem->Get_Rect()))
            {
                
                pItem->Set_Dead();
                dynamic_cast<CPlayer*>(pPlayer)->FireMultiShot();
            }
        }
    }
}

void CCollisionMgr::Collision_Rect(list<CObj*> Dst, list<CObj*> Src)
{
    RECT rc{};

    for (auto& pDst : Dst)
    {
        for (auto& pSrc : Src)
        {
            if (IntersectRect(&rc, pDst->Get_Rect(), pSrc->Get_Rect()))
            {
                pDst->Take_Dmg(pSrc->Get_Dmg());
                pSrc->Take_Dmg(pDst->Get_Dmg());
            }
        }
    }
}

void CCollisionMgr::Collision_Circle(list<CObj*> Dst, list<CObj*> Src)
{
    for (auto& pDst : Dst)
    {
        for (auto& pSrc : Src)
        {
            if (Check_Circle(pDst, pSrc))
            {
                pDst->Take_Dmg(pSrc->Get_Dmg());
                pSrc->Take_Dmg(pDst->Get_Dmg());

            }
        }
    }
}

bool CCollisionMgr::Check_Circle(CObj* pDst, CObj* pSrc)
{
    float fWidth = abs(pDst->Get_Info().fX - pSrc->Get_Info().fX);

    float fHeight = abs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

    float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

    float fRadius = (pDst->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

    return fRadius >= fDistance;
}
