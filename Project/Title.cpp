#include "Title.h"
#include "MIDIOut.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理
	m_StartBtn = CButton(CRectangle(SceneWidth * 0.5f - 100, 100, SceneWidth * 0.5f + 100, 200), "曲選択へ");
}

CTitle::~CTitle(void)
{
	// 解放処理
}

void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		m_StartBtn.IsPull())
	{
		ChangeScene(SceneName::Select);
	}
}

void CTitle::Render(void) const
{
	CGraphicsUtilities::RenderString(0,  0, "Title");
	CGraphicsUtilities::RenderString(0, 30, "Enterキーでセレクト画面へ");
	m_StartBtn.Render();
}
