#include "SelectScene.h"
#include "Load.h"


int      g_MusicSelect = 0;


CSelectScene::CSelectScene(const CSelectScene::InitData & init) :
	MyApp::CScene::IScene(init)
{
	g_MusicSelect   = 0;
	m_SelectBtnUp   = CButton(CRectangle(500, 90,530,120), "▲");
	m_SelectBtnDown = CButton(CRectangle(500,120,530,150), "▼");
	m_SetBtn        = CButton(CRectangle(100,180,200,210), "決定");
}

CSelectScene::~CSelectScene(void)
{
}

void CSelectScene::Update(void)
{
	// 選択した曲へGO!
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		m_SetBtn.IsPull())
	{
		ChangeScene(SceneName::Setting);
	}

	// マウスホイールでのカーソル移動。
	int wheelMove = g_pInput->GetMouseWheelMove() * 0.01f;
	if (wheelMove)
	{
		g_MusicSelect += wheelMove;
	}

	// 上下矢印キーでのカーソル移動。
	if (g_pInput->IsKeyPush(MOFKEY_UP) ||
		m_SelectBtnUp.IsPull())
	{
		g_MusicSelect--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN) ||
		m_SelectBtnDown.IsPull())
	{
		g_MusicSelect++;
	}

	// セレクト数が曲数を超えないようにする。
	g_MusicSelect = MOF_CLIPING(g_MusicSelect, 0, g_MusicData.GetArrayCount() - 1);

}

void CSelectScene::Render(void) const
{
	CGraphicsUtilities::RenderString(0,   0, "Select");

	CGraphicsUtilities::RenderString(0,  30, "select : %d", g_MusicSelect);

	CGraphicsUtilities::RenderString(0,  60, "title : %s", g_MusicData[g_MusicSelect].title.c_str());

	CGraphicsUtilities::RenderString(0,  90, "上下キーで曲選択、Enterキーで演奏準備へ");
	
	m_SelectBtnDown.Render();
	m_SelectBtnUp.Render();
	m_SetBtn.Render();
}
