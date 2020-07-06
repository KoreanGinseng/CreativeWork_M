#include "Setting.h"
#include "Game.h"

CSetting::CSetting(const InitData & init) :
	MyApp::CScene::IScene(init)
{
	m_Select      = 1;

	m_SelectUp    = CButton(CRectangle(850, 210,  880, 240), "▲");
	m_SelectDown  = CButton(CRectangle(850, 270,  880, 300), "▼");
	m_SelectLeft  = CButton(CRectangle(820, 240,  850, 270), "＜");
	m_SelectRight = CButton(CRectangle(880, 240,  910, 270), "＞");
	m_Start       = CButton(CRectangle(800, 350,  900, 380), "開始");
	m_Back        = CButton(CRectangle(910, 350, 1010, 380), "戻る");
}

CSetting::~CSetting(void)
{
}

void CSetting::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		m_Back.IsPull())
	{
		ChangeScene(SceneName::Select);
	}
	if (g_pInput->IsKeyPush(MOFKEY_4) ||
		m_Start.IsPull())
	{
		if (g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[GetData().trackNo].GetArrayCount() == 0)
		{
			return;
		}
		ChangeScene(SceneName::Game);

		GetData().channel = GetData().trackNo;

		// 全チャンネルの音色変更。
		for (int i = 0; i < g_NoteArray[g_MusicSelect].GetSMFData().GetInstrumentArray().GetArrayCount(); i++)
		{
			g_Midiout.ChangeInstrument((GMInstrument)g_NoteArray[g_MusicSelect].GetSMFData().GetInstrumentArray()[i], i);
		}
	}

	// マウスホイールでのカーソル移動。
	int wheelMove = g_pInput->GetMouseWheelMove() * 0.01f;
	if (wheelMove)
	{
		m_Select -= wheelMove;
	}

	// 上下矢印キーでのカーソル移動。
	if (g_pInput->IsKeyPush(MOFKEY_UP) ||
		m_SelectUp.IsPull())
	{
		m_Select--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN) ||
		m_SelectDown.IsPull())
	{
		m_Select++;
	}

	// セレクト数が超えないようにする。
	m_Select = MOF_CLIPING(m_Select, 1, 6);

	if (g_pInput->IsKeyPush(MOFKEY_LEFT) ||
		m_SelectLeft.IsPull())
	{
		switch (m_Select)
		{
		case 1:
			GetData().fallSpeed -= 0.1f;
			break;
		case 2:
			GetData().keyLength =
				(GetData().keyLength == KeyLength::_25) || (GetData().keyLength == KeyLength::_37)
				? KeyLength::_25
				: GetData().keyLength == KeyLength::_49
				? KeyLength::_37
				: GetData().keyLength == KeyLength::_61
				? KeyLength::_49
				: KeyLength::_61;
			break;
		case 3:
			GetData().offsetKey = (PianoKey)(GetData().offsetKey - 1);
			break;
		case 4:
			GetData().autoParam = (Auto)((int)GetData().autoParam - 1);
			break;
		case 5:
			GetData().trackNo--;
			break;
		case 6:
			g_NoteArray[g_MusicSelect].GetSMFData().GetInstrumentArray()[GetData().trackNo];
			break;
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RIGHT) ||
		     m_SelectRight.IsPull())
	{
		switch (m_Select)
		{
		case 1:
			GetData().fallSpeed += 0.1f;
			break;
		case 2:
			GetData().keyLength =
				(GetData().keyLength == KeyLength::_88) || (GetData().keyLength == KeyLength::_61)
				? KeyLength::_88
				: GetData().keyLength == KeyLength::_49
				? KeyLength::_61
				: GetData().keyLength == KeyLength::_37
				? KeyLength::_49
				: KeyLength::_37;
			break;
		case 3:
			GetData().offsetKey = (PianoKey)(GetData().offsetKey + 1);
			break;
		case 4:
			GetData().autoParam = (Auto)((int)GetData().autoParam + 1);
			break;
		case 5:
			GetData().trackNo++;
			break;
		}
	}
	GetData().fallSpeed = MOF_CLIPING(GetData().fallSpeed, 1.0f, 10.0f);
	GetData().autoParam = (Auto)MOF_CLIPING((int)GetData().autoParam, 0, 2);
	GetData().trackNo   = MOF_CLIPING(GetData().trackNo, 0, g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray().GetArrayCount() - 1);
}

void CSetting::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Setting");

	CGraphicsUtilities::RenderString(0,  30, "FallSpeed : %.1f", GetData().fallSpeed);
	CGraphicsUtilities::RenderString(0,  60, "KeyLength : %2d" , GetData().keyLength);
	CGraphicsUtilities::RenderString(0,  90, "OffsetKey : %03u", GetData().offsetKey);
	CGraphicsUtilities::RenderString(0, 120, "AutoParam : %s"  , GetData().autoParam == Auto::All ? "All" : GetData().autoParam == Auto::Semi ? "Semi" : "None");
	CGraphicsUtilities::RenderString(0, 150, "trackNum  : %d"  , GetData().trackNo);
	CGraphicsUtilities::RenderString(0, 180, "Instrument: %u"  , g_NoteArray[g_MusicSelect].GetSMFData().GetInstrumentArray()[GetData().trackNo]);

	CGraphicsUtilities::RenderString(0, 210, "info");
	int combCnt = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[GetData().trackNo].GetArrayCount();
	CGraphicsUtilities::RenderString(0, 240, "MidiFormat: %d", g_NoteArray[g_MusicSelect].GetSMFData().GetMidiFormat());
	CGraphicsUtilities::RenderString(0, 270, "TrackName : %s", g_NoteArray[g_MusicSelect].GetSMFData().GetTrackNameArray()[GetData().trackNo].GetString());
	CGraphicsUtilities::RenderString(0, 300, "MaxComb   : %d", combCnt / 2);
	CGraphicsUtilities::RenderString(0, 330, "%s", g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[GetData().trackNo].GetArrayCount() ? "4キーでプレイ" : "プレイ不可");
	CGraphicsUtilities::RenderString(0, 360, "Enterキーでセレクト画面へ");

	CGraphicsUtilities::RenderString(350, m_Select * 30, "←");

	m_SelectDown.Render();
	m_SelectUp.Render();
	m_SelectLeft.Render();
	m_SelectRight.Render();
	m_Start.Render();
	m_Back.Render();

	// 白鍵の描画。
	CGame::RenderWhiteKey(GetData().offsetKey, GetData().keyLength);

	// 黒鍵の描画。
	CGame::RenderBlackKey();
}
