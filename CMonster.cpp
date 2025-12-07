#include "pch.h"
#include "CMonster.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CMonsterBullet.h"
#include "Define.h"
#include "CItem.h"

CMonster::CMonster()
{
   m_fTargetX = m_tInfo.fX;
   m_fTargetY = m_tInfo.fY;

}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
    m_tInfo.fCX = 50.f;
    m_tInfo.fCY = 50.f;


    m_fHP = 3;
    m_iDmg = 1;


}

int CMonster:: Update()
{


    if (m_fHP <= 0)
    { 

        m_bDead = true;
    }

    if (m_bDead)
    {

        return DEAD;
    }

    __super::Update_Rect();


    if (m_tInfo.fY <= fLimitY)
    {
        m_fAngle = 90;
        m_fSpeed = 2.f;                                             //몬스터 등장, 일정 선 이전까지 내려옴
        m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
        m_tInfo.fY += m_fSpeed * sinf(m_fAngle * (PI / 180.f));
    }

    if (m_tInfo.fY > fLimitY)
    {
        m_fSpeed = 0.5f;
                                                    //일정 선 도달 시 느려짐
        DWORD dwNow = GetTickCount();


        if (dwNow - m_dwLastFire > 3000)
        {
            CObjMgr::Get_Instance()->Add_Object(OBJ_MONBULLET, Create_Bullet());        //3초마다 평타발사
            m_fAngle = rand() % 361;                                                   //랜덤 무빙
            m_dwLastFire = dwNow;

          /*  m_fTargetX = m_tInfo.fX + (rand() % 200 - 100);
            m_fTargetY = m_tInfo.fY + (rand() % 200 - 100);*/
        }

        m_tInfo.fX += m_fSpeed * cosf(m_fAngle * (PI / 180.f));
        m_tInfo.fY += m_fSpeed * sinf(m_fAngle * (PI / 180.f));

        ResolveCollision();


        //float dx = m_fTargetX - m_tInfo.fX;
        //float dy = m_fTargetY - m_tInfo.fY;
        //float dist = sqrtf(dx * dx + dy * dy);

        //if (dist > 1.f)
        //{
        //    m_tInfo.fX += dx / dist * m_fSpeed * (rand()%3-1);
        //    m_tInfo.fY += dy / dist * m_fSpeed;
        //}

       // if (dwNow - m_dwLastFire > 3000)
       // {
       //     CObjMgr::Get_Instance()->Add_Object(OBJ_MONBULLET, Create_Bullet());
       //     
       //     m_dwLastFire = dwNow;
       //
       //
       //
       // }
       // m_tInfo.fX += (rand() % 31 - 15) * m_fSpeed;
       // m_tInfo.fY -= (rand() % 31 - 15) * m_fSpeed;

    }
    return NOEVENT;
}


void CMonster::Late_Update()
{
    //srand(unsigned int(time(NULL)));
}

CObj* CMonster::Create_Bullet()
{
    CObj* pBullet = CAbstractFactory<CMonsterBullet>::Create(m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY/2);
    return pBullet;
 }



void CMonster::Render(HDC hDC)
{



    Rectangle(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);



}

void CMonster::Release()
{
}


void CMonster::ResolveCollision()
{
    float fRandAngle;
    if (m_tRect.right >= WINCX)
    {
        m_tInfo.fX -= 10.f;
        fRandAngle = rand() % 360;
        m_fAngle = fRandAngle;
    }
    if (m_tRect.left <= 0)
    {
        m_tInfo.fX += 10.f;
        fRandAngle = rand() % 360;
        m_fAngle = fRandAngle;
    }
    if (m_tRect.top <= 0)
    {
        m_tInfo.fY += 10.f;
        fRandAngle = rand() % 360;
        m_fAngle = fRandAngle;
    }
    if (m_tRect.bottom >= WINCY)
    {
        m_tInfo.fY -= 10.f;
        fRandAngle = rand() % 360;
        m_fAngle = fRandAngle;
    }
}