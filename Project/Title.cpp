#include "Title.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init) 
{
	// 初期化処理

	// ボタンフォントの登録。
	m_pBtnFont = FontAsset("Button");

	// スタートボタンの初期化。
	m_BtnGameStart.Initialize(Vector2(350, 300), Vector2(100, 30), "始める", m_pBtnFont);
}

CTitle::~CTitle(void)
{
	// 解放処理
}

void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) || m_BtnGameStart.IsClickL())
	{
		ChangeScene(SceneName::Game);
	}
}

void CTitle::Render(void) const
{
	CGraphicsUtilities::RenderString(0,  0, "TitleScene");
	CGraphicsUtilities::RenderString(0, 30, "return : go GameScene");

	m_BtnGameStart.Render();
}
