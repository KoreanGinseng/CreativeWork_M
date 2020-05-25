#include "Game.h"

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理

	// ボタン用フォントの登録。
	m_pBtnFont = FontAsset("Button");
	m_pBtnFont->SetSize(16);

	// ウィンドウサイズ変更のボタンの初期化。
	m_BtnWindowSize[WINDOWSIZE::LARGE ].Initialize(Vector2( 10, 8), Vector2(50, 18), "大", m_pBtnFont);
	m_BtnWindowSize[WINDOWSIZE::MEDIUM].Initialize(Vector2( 70, 8), Vector2(50, 18), "中", m_pBtnFont);
	m_BtnWindowSize[WINDOWSIZE::SMALL ].Initialize(Vector2(130, 8), Vector2(50, 18), "小", m_pBtnFont);

	// 最前面にするボタンの初期化。
	m_BtnAppForward.Initialize(Vector2(210, 8), Vector2(50, 18), "最前面", m_pBtnFont);
	m_bForward = false;

	// タイトルへ行くボタンの初期化。
	m_BtnGoTitle.Initialize(Vector2(290, 8), Vector2(70, 18), "タイトルへ", m_pBtnFont);

	// ゲームデータからウィンドウのサイズを変更する。
	g_pGraphics->SetScreenSize(
		WindowSize[GetData().windowSize].first,
		WindowSize[GetData().windowSize].second
	);
}

CGame::~CGame(void)
{
	// 解放処理
}

void CGame::Update(void)
{
	// タイトルへ行くボタンが押されたらタイトルへ行こうね。
	if (m_BtnGoTitle.IsClickL())
	{
		ChangeScene(SceneName::Title);

		// 画面サイズを戻しておく。
		g_pGraphics->SetScreenSize(
			WindowSize[WINDOWSIZE::LARGE].first,
			WindowSize[WINDOWSIZE::LARGE].second
		);
	}

	for (int i = 0; i < WINDOWSIZE::WINDOWSIZE_CONT; i++)
	{
		// 押されたボタンによってウィンドウのサイズを変更する。
		if (m_BtnWindowSize[i].IsClickL())
		{
			g_pGraphics->SetScreenSize(WindowSize[i].first, WindowSize[i].second);

			// 変更されたサイズを記憶,更新する。
			GetData().windowSize = static_cast<WINDOWSIZE>(i);
			break;
		}
	}

	// ウィンドウ最前面の処理。
	if (m_BtnAppForward.IsClickL())
	{
		m_bForward = !m_bForward;
		m_BtnAppForward.SetString(m_bForward ? "解除" : "最前面");
		CWindowUtillities::SetForeGround(m_bForward);
	}
}

void CGame::Render(void) const
{
	// ウィンドウサイズ変更ボタンの描画。
	for (int i = 0; i < WINDOWSIZE::WINDOWSIZE_CONT; i++)
	{
		m_BtnWindowSize[i].Render();
	}

	// 最前面設定ボタンの描画。
	m_BtnAppForward.Render();

	// タイトルへ行くボタンの描画。
	m_BtnGoTitle.Render();
}
