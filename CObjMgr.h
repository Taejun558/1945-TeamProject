#pragma once
#include "CObj.h"




class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(const CObjMgr& rhs)			= delete;
	CObjMgr& operator=(CObjMgr& rObj)	 = delete;
	~CObjMgr();

public:
	void	Add_Object(OBJID eID, CObj* pObj);
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	CObj* Get_Target(OBJID eID, CObj* pObj);

public:
	static CObjMgr* Get_Instance()
	{
		if(nullptr == m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	void Delete_All(OBJID eID);



	CObj* Create_Item(float x, float y);

private:
	static CObjMgr* m_pInstance;

	static int iScore;

	


	list<CObj*> m_ObjList[OBJ_END];
};	

