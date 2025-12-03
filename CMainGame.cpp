#include "pch.h"
#include "CMainGame.h"
#include "CBullet.h"
#include "CAbstractFactory.h"
#include "CSubBullet.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr) , m_dwTime(GetTickCount())
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}


	dynamic_cast<CPlayer*>(m_pPlayer)->Set_Bullet(&m_BulletList);

	dynamic_cast<CPlayer*>(m_pPlayer)->Set_SubBullet(&m_SubBulletList);


}

void CMainGame::Update()
{
	m_pPlayer->Update();

	for (auto& pBullet : m_BulletList)
		pBullet->Update();

	for (auto& pBullet : m_SubBulletList)
		pBullet->Update();
}

void CMainGame::Late_Update()
{
	m_pPlayer->Late_Update();
}

void CMainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	m_pPlayer->Render(m_hDC);

	for (auto& pBullet : m_BulletList)
	{
		if (pBullet != nullptr)
			pBullet->Render(m_hDC);
	}

	for (auto& pBullet : m_SubBulletList)
	{
		if (pBullet != nullptr)
			pBullet->Render(m_hDC);
	}
}

void CMainGame::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);

	for_each(m_BulletList.begin(), m_BulletList.end(), Safe_Delete<CObj*>);
	m_BulletList.clear();

	for_each(m_SubBulletList.begin(), m_SubBulletList.end(), Safe_Delete<CObj*>);
	m_SubBulletList.clear();

	ReleaseDC(g_hWnd, m_hDC);
}
