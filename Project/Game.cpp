#include "Game.h"

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理

	// ボタン用フォントの登録。
	m_pBtnFont = FontAsset("Button");
	m_pBtnFont->SetSize(16);

	// ウィンドウサイズ変更のボタンの初期化。
	m_BtnWindowSize[WindowSize::LARGE ].Initialize(Vector2( 10, 8), Vector2(50, 18), "大", m_pBtnFont);
	m_BtnWindowSize[WindowSize::MEDIUM].Initialize(Vector2( 70, 8), Vector2(50, 18), "中", m_pBtnFont);
	m_BtnWindowSize[WindowSize::SMALL ].Initialize(Vector2(130, 8), Vector2(50, 18), "小", m_pBtnFont);
}

CGame::~CGame(void)
{
	// 解放処理
}

void CGame::Update(void)
{
	// DEBUG
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		ChangeScene(SceneName::Title);
	}

	for (int i = 0; i < WindowSize::WINDOWSIZE_CONT; i++)
	{
		// 押されたボタンによってウィンドウのサイズを変更する。
		if (m_BtnWindowSize[i].IsClickL())
		{
			g_pGraphics->SetScreenSize(WindowSize[i].first, WindowSize[i].second);

			// 変更されたサイズを記憶,更新する。
			GetData().windowWidth  = WindowSize[i].first;
			GetData().windowHeight = WindowSize[i].second;
			break;
		}
	}
}

void CGame::Render(void) const
{
	// ウィンドウサイズ変更ボタンの描画。
	for (int i = 0; i < WindowSize::WINDOWSIZE_CONT; i++)
	{
		m_BtnWindowSize[i].Render();
	}
}
