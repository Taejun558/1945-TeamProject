#include "pch.h"
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "CItem.h"
#include "CBossMonster.h"
#include "CAbstractFactory.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;
int CObjMgr::iScore = 0;

CObjMgr::CObjMgr()
{
			
}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj* CObjMgr::Get_Target(OBJID eID, CObj* pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj* pTarget = nullptr;

	float fDistance(0.f), fWidth(0.f), fHeight(0.f), fDiagonal(0.f);

	for (auto& Dst : m_ObjList[eID])
	{
		if (Dst->Get_Dead())
			continue;

		fWidth = pObj->Get_Info().fX - Dst->Get_Info().fX;
		fHeight = pObj->Get_Info().fY - Dst->Get_Info().fY;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Dst;

			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Delete_All(OBJID eID)
{
		for (auto& pObj : m_ObjList[eID])
			Safe_Delete<CObj*>(pObj);

		m_ObjList[eID].clear();
	
}

CObj* CObjMgr::Create_Item(float x, float y)
{
			CObj* pItem = new CItem;
			pItem->Set_Pos(x, y);
			return pItem;
}



void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (OBJ_END <= eID || pObj == nullptr)
		return;

	m_ObjList[eID].push_back(pObj);

	pObj->Initialize();
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (iResult == DEAD)
			{
				if (i == OBJ_MONSTER)
				{
					int iProb = rand() % 10;
					if (iProb >= 5)
					{
						float x = (*iter)->Get_Info().fX;
						float y = (*iter)->Get_Info().fY;

						Add_Object(OBJ_ITEM, Create_Item(x, y));
					}
					iScore++;
				}
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	static bool bSpawned = false;

	if (iScore >= 30 && !bSpawned)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSSMONSTER, CAbstractFactory<CBossMonster>::
			Create(400, 100));
		bSpawned = true;
	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Late_Update();
		}
	}

	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_SUBBULLET]);
	CCollisionMgr::Collision_Ultimate(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_ULTIMATE]);
	CCollisionMgr::Collision_Ultimate(m_ObjList[OBJ_MONBULLET], m_ObjList[OBJ_ULTIMATE]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONBULLET]);
	CCollisionMgr::Collision_Item(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_BOSSMONSTER], m_ObjList[OBJ_BULLET]);
	CCollisionMgr::Collision_Rect(m_ObjList[OBJ_BOSSMONSTER], m_ObjList[OBJ_SUBBULLET]);
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_BOSSMONSTER], m_ObjList[OBJ_ULTIMATE]);
}

void CObjMgr::Render(HDC hDC)
{

#pragma region Á¡¼ö

	TCHAR szText[32];
	swprintf_s(szText, TEXT("Kill : % d"), CObjMgr::iScore);
	TextOut(hDC, 10, 50, szText, lstrlen(szText));
#pragma endregion


	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
		{
			pObj->Render(hDC);
		}
	}

}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}