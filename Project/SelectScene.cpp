#include "SelectScene.h"
#include "Load.h"

// 演奏曲のリスト番号
int      g_MusicSelect = 0;


CSelectScene::CSelectScene(const CSelectScene::InitData & init) :
	MyApp::CScene::IScene(init)
{
	g_MusicSelect   = 0;

	float x = SceneWidth  - 180;
	float y = SceneHeight - 110;
	m_PlayBtn       = CButton(CRectangle(              x,               y,         x + 150,           y + 80));
	m_PlayAutoBtn   = CButton(CRectangle(        x - 250,               y,         x -  30,           y + 80));
	m_SelectBtnUp   = CButton(CRectangle(            530,              30,             580,               80));
	m_SelectBtnDown = CButton(CRectangle(            530,SceneHeight - 80,             580, SceneHeight - 30));
	m_SetBtn        = CButton(CRectangle(SceneWidth - 80,              30, SceneWidth - 30,               80));
	
	m_SelectBtnUp  .SetTexture(TextureAsset("ArrowUp"));
	m_SelectBtnDown.SetTexture(TextureAsset("ArrowDown"));
	m_SetBtn       .SetTexture(TextureAsset("Gear"));
	m_PlayBtn      .SetTexture(TextureAsset("Play"));
	m_PlayAutoBtn  .SetTexture(TextureAsset("PlayAuto"));

	m_TruckIndex    = 0;

	m_pSelect1Texture = TextureAsset("Select_1");
	m_pSelect2Texture = TextureAsset("Select_2");

	m_pNameFont = FontAsset("MusicName");
	m_pInfoFont = FontAsset("Info");
	m_pNameFont->SetSize(50);
	m_pInfoFont->SetSize(36);

	m_ArrowMotion << CEaseMotion<float>(0.0f, 5.0f, Ease::InOut, EaseType::Sine, 0.5f);
	m_ArrowMotion << CEaseMotion<float>(5.0f, 0.0f, Ease::InOut, EaseType::Sine, 0.5f);

	m_ArrowMotion.Start();

	m_Scale    = 1.0f;
	m_Rotate   = 0.0f;
	m_pTitleTexture = TextureAsset("Title");

	m_ScaleMotion << CEaseMotion<float>(1.0f, 1.2f, Ease::InOut, EaseType::Sine, 0.5f);
	m_ScaleMotion << CEaseMotion<float>(1.2f, 1.0f, Ease::InOut, EaseType::Sine, 0.5f);

	m_ScaleMotion.Start();
}

CSelectScene::~CSelectScene(void)
{
}

void CSelectScene::Update(void)
{
	int truckNo  = g_MusicData[g_MusicSelect].trucks[m_TruckIndex];
	int truckCnt = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray().GetArrayCount();
	// 選択した曲へGO!
	if (
		// ボタン系押されたかの判定。
		(
		    g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		    m_PlayAutoBtn.IsPull()             ||
		    m_PlayBtn.IsPull()
		)   
		&&
		// データがあるかどうかの判定。
		(
			truckNo < truckCnt                 &&
			g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[truckNo].GetArrayCount() > 0
		) 
	   )
	{
		GetData().trackNo = g_MusicData[g_MusicSelect].trucks[m_TruckIndex];
		GetData().channel = GetData().trackNo;
		GetData().autoParam = m_PlayAutoBtn.IsPull() ? Auto::All : Auto::Semi;
		ChangeScene(SceneName::Game);
	}

	// 設定画面へ。
	if (m_SetBtn.IsPull())
	{
		ChangeScene(SceneName::Setting);
	}

	// 背景の更新。
	m_ScaleMotion.Update();

	m_Scale = m_ScaleMotion.GetValue();

	// ループさせる。
	if (m_ScaleMotion.IsEnd())
	{
		m_ScaleMotion.Reset();
		m_ScaleMotion.Start();
	}

	m_Rotate += 0.01f;

	m_Rotate = MOF_NORMALIZE_RADIANANGLE(m_Rotate);

	// 矢印のふわふわするモーションの更新。
	m_ArrowMotion.Update();

	m_SelectBtnUp  .GetRect().SetPosition(Vector2(530,               30) + Vector2(0, -m_ArrowMotion.GetValue()));
	m_SelectBtnDown.GetRect().SetPosition(Vector2(530, SceneHeight - 80) + Vector2(0,  m_ArrowMotion.GetValue()));

	// アニメーションをループさせる。
	if (m_ArrowMotion.IsEnd())
	{
		m_ArrowMotion.Reset();
		m_ArrowMotion.Start();
	}

	// マウスホイールでのカーソル移動。
	int wheelMove = g_pInput->GetMouseWheelMove() * 0.01f;
	if (wheelMove)
	{
		int max  = g_MusicData.GetArrayCount();

		g_MusicSelect += wheelMove;

		// ロールする処理。
		if (g_MusicSelect < 0)
		{
			g_MusicSelect += max;
		}
		else if (g_MusicSelect >= max)
		{
			g_MusicSelect -= max;
		}
	}

	// 上下矢印キーでのカーソル移動。
	if (g_pInput->IsKeyPush(MOFKEY_UP) ||
		m_SelectBtnUp.IsPull())
	{
		g_MusicSelect--;
		if (g_MusicSelect < 0)
		{
			g_MusicSelect = g_MusicData.GetArrayCount() - 1;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN) ||
		m_SelectBtnDown.IsPull())
	{
		g_MusicSelect++;
		if (g_MusicSelect > g_MusicData.GetArrayCount() - 1)
		{
			g_MusicSelect = 0;
		}
	}

	// 左右矢印キーでトラックの選択。
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		m_TruckIndex--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		m_TruckIndex++;
	}

	// セレクト数が曲数を超えないようにする。
	g_MusicSelect = MOF_CLIPING(g_MusicSelect, 0, g_MusicData.GetArrayCount() - 1);
	m_TruckIndex  = MOF_CLIPING(m_TruckIndex , 0, g_MusicData[g_MusicSelect].trucks.size() - 1);
}

void CSelectScene::Render(void) const
{
	m_pTitleTexture->RenderScaleRotate(SceneWidth * 0.5f, SceneHeight * 0.5f, m_Scale, m_Rotate, MOF_ALPHA_WHITE(128), TEXALIGN_CENTERCENTER);

	for (int i = -2; i <= 2; i++)
	{
		int w = 400;
		int h = 100;
		int x = 100 + MOF_ABS(i) * -30;
		int y = (SceneHeight - h) * 0.5f + (i * (h + 50));
		CRectangle rect(x, y, x + w, y + h);

		// 背景テクスチャの描画。
		if (i == 0)
		{
			m_pSelect1Texture->Render(rect);
		}
		else
		{
			m_pSelect2Texture->Render(rect);
		}

		// テキスト描画。
		CRectangle outStrRect;
		int musicNo = LoopMusicNo(g_MusicSelect + i);
		m_pNameFont->CalculateStringRect(0, 0, g_MusicData[musicNo].title.c_str(), outStrRect);
		m_pNameFont->RenderString(
			x + (rect.GetWidth()  - outStrRect.GetWidth() ) * 0.5f,
			y + (rect.GetHeight() - outStrRect.GetHeight()) * 0.5f,
			g_MusicData[musicNo].title.c_str()
		);
	}
	
	// 各ボタンの描画。
	m_SelectBtnDown.Render();
	m_SelectBtnUp.Render();
	m_PlayBtn.Render();
	m_PlayAutoBtn.Render();
	m_SetBtn.Render();

	// 情報の描画。
	Vector2    infoPos(SceneWidth * 0.5f + 30, 110);
	CRectangle infoRect(infoPos, Vector2(SceneWidth - 30, SceneHeight - 140));
	CGraphicsUtilities::RenderFillRect(infoRect, MOF_ALPHA_BLUE(64));

	int offsetX = infoRect.Left + 30;

	CRectangle titleNameRect;
	m_pInfoFont->CalculateStringRect(0, 0, g_MusicData[g_MusicSelect].title.c_str(), titleNameRect);
	m_pInfoFont->RenderString(infoPos.x + (infoRect.GetWidth() - titleNameRect.GetWidth()) * 0.5f, infoPos.y + 30, g_MusicData[g_MusicSelect].title.c_str());
	CGraphicsUtilities::RenderLine(infoRect.Left + 30, infoPos.y + 32 + titleNameRect.GetHeight(), infoRect.Right - 30, infoPos.y + 32 + titleNameRect.GetHeight(), MOF_COLOR_WHITE);

	int truckNo  = g_MusicData[g_MusicSelect].trucks[m_TruckIndex];
	int truckCnt = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray().GetArrayCount();
	m_pInfoFont->RenderFormatString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 3, "TrackNo   : %02u", truckNo);
	
	// トラックが存在するか確認する。
	if (truckNo >= truckCnt)
	{
		m_pInfoFont->RenderString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 2, "このトラックは存在しません。");
	}
	else
	{
		int combCnt  = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[truckNo].GetArrayCount();
		m_pInfoFont->RenderFormatString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 2, "TrackName : %s"  , g_NoteArray[g_MusicSelect].GetSMFData().GetTrackNameArray()[truckNo].GetString());
		m_pInfoFont->RenderFormatString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 1, "MaxCombo  : %d"  , combCnt / 2);
	}
}

int CSelectScene::LoopMusicNo(const int& offset) const
{
	int no = offset;

	int size = g_MusicData.GetArrayCount();
	
	if (size == 1)
	{
		return 0;
	}
	else if (no > size - 1)
	{
		return LoopMusicNo(no - size);
	}
	else if (no < 0)
	{
		return LoopMusicNo(size + no);
	}

	return no;
}
