#include "Game.h"
#include "Load.h"


CMIDIOut          g_Midiout;

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理
	CNote::SetAutoParam(GetData().autoParam);
	CNote::SetKeyLength(GetData().keyLength);
	CNote::SetKeyOffset(GetData().offsetKey);

	g_NoteArray.Initialize(GetData().trackNo);
	g_PlayResult.Clear();

	g_NoteArray.SetFallSpeed(GetData().fallSpeed);

	int   size     = g_NoteArray.GetSMFData().GetNoteArray().GetArrayCount();
	float fallTime = CheckLineY / g_NoteArray.GetFallSpeed();
	m_EndTime      = g_NoteArray.GetSMFData().GetNoteArray()[GetData().trackNo].GetData(size - 1).eventTime / 1000.0f + fallTime + 3.0f;
	
	m_StartTime.Start();
}

CGame::~CGame(void)
{
	// 解放処理
}

void CGame::Update(void)
{
	m_StartTime.Update();

	// 2キーでタイトルへ戻る。
	if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		ChangeScene(SceneName::Title);
	}
	// 終わったらリザルトへ。
	if (m_StartTime.GetTime() > m_EndTime)
	{
		ChangeScene(SceneName::Result);
	}

	// ノーツの更新。
	g_NoteArray.Update();
}

void CGame::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Game");

	// 譜面の縦の線のやつ。
	RenderKeyLine();
	
	// ノーツの描画。
	g_NoteArray.Render();

	// 判定ラインの描画。
	//RenderCheckLine();

	NoteHitResult hit = CNote::GetHitResult();

	CGraphicsUtilities::RenderString(
		0, 30, "%s",
		hit == NoteHitResult::NONE
		? "" 
		: hit == NoteHitResult::MISS
		? "MISS"
		: hit == NoteHitResult::BAD
		? "BAD"
		: hit == NoteHitResult::GOOD
		? "GOOD"
		: hit == NoteHitResult::GREAT
		? "GREAT"
		: "PERFECT"
		);

	CGraphicsUtilities::RenderString(0, 60, "Combo    : %d", g_PlayResult.combo);
	CGraphicsUtilities::RenderString(0, 90, "MaxCombo : %d", g_PlayResult.maxCombo);

	// 白鍵の描画。
	CGame::RenderWhiteKey(GetData().offsetKey, GetData().keyLength);

	// 黒鍵の描画。
	CGame::RenderBlackKey();
	
}

void CGame::RenderKeyLine(void) const
{
	// 譜面の縦の線のやつ。
	for (int x = 0; x <= 7; x++)
	{
		CGraphicsUtilities::RenderLine(
			PianoRollOffsetX + PianoWhiteKeyWidth * 2 + x * 7 * PianoWhiteKeyWidth,
			0,
			PianoRollOffsetX + PianoWhiteKeyWidth * 2 + x * 7 * PianoWhiteKeyWidth,
			SceneHeight,
			MOF_COLOR_HWHITE
		);

		CGraphicsUtilities::RenderLine(
			PianoRollOffsetX + PianoWhiteKeyWidth * 2 + x * 7 * PianoWhiteKeyWidth + PianoWhiteKeyWidth * 3,
			0,
			PianoRollOffsetX + PianoWhiteKeyWidth * 2 + x * 7 * PianoWhiteKeyWidth + PianoWhiteKeyWidth * 3,
			SceneHeight,
			MOF_COLOR_CBLACK
		);
	}
}

void CGame::RenderCheckLine(void) const
{
	// 判定ラインの描画。
	CGraphicsUtilities::RenderLine(10, CheckLineY, 1270, CheckLineY, MOF_COLOR_RED);

	// 白鍵の上の丸いやつ。
	for (int i = 0, x = 0; i < 88; i++)
	{
		MofU8 pianoKey = i + PianoKey::A0;

		if (CMIDIInput::IsBlackKey(pianoKey))
		{
			continue;
		}

		CGraphicsUtilities::RenderCircle(
			PianoRollOffsetX + x * PianoWhiteKeyWidth + PianoWhiteKeyWidth * 0.5f, CheckLineY, 5, MOF_COLOR_RED
		);

		x++;
	}
}

void CGame::RenderWhiteKey(const PianoKey& offset, const KeyLength& length)
{
	// 白鍵の描画。
	for (int i = 0, x = 0; i < 88; i++)
	{
		MofU8 pianoKey = i + PianoKey::A0;

		bool bKeyRange = true;
		if (pianoKey < offset || pianoKey >= length + offset)
		{
			bKeyRange = false;
		}

		if (CMIDIInput::IsBlackKey(pianoKey))
		{
			continue;
		}

		CGraphicsUtilities::RenderFillRect(
			PianoRollOffsetX + PianoWhiteKeyWidth * x,
			PianoRollOffsetY,
			PianoRollOffsetX + PianoWhiteKeyWidth * (x + 1),
			PianoRollOffsetY + PianoWhiteKeyHeight,
			g_MIDIInput.IsKeyHold(pianoKey)
			? MOF_COLOR_HBLUE
			: bKeyRange ? MOF_COLOR_WHITE : MOF_COLOR_HWHITE
		);

		x++;
	}

	// 白鍵の間に線入れる。
	for (int i = 0; i <= WhiteKeyCount; i++)
	{
		CGraphicsUtilities::RenderLine(
			PianoRollOffsetX + i * PianoWhiteKeyWidth, PianoRollOffsetY,
			PianoRollOffsetX + i * PianoWhiteKeyWidth, PianoRollOffsetY + PianoWhiteKeyHeight,
			MOF_COLOR_BLACK
		);
	}
}

void CGame::RenderBlackKey(void)
{
	// A0_Sの描画。
	int blackX = PianoRollOffsetX + (PianoWhiteKeyWidth - PianoBlackKeyWidth * 0.5f);
	CGraphicsUtilities::RenderFillRect(
		blackX, PianoRollOffsetY,
		blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
		g_MIDIInput.IsKeyHold(PianoKey::A0_S)
		? MOF_COLOR_HRED
		: MOF_COLOR_BLACK
	);

	// C1_S〜の描画。
	for (int i = 0; i < 7; i++)
	{
		MofU8 pianoKey = PianoKey::C1_S + (i * PianoBlackKeyWidth);

		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 3 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MIDIInput.IsKeyHold(pianoKey)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 4 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MIDIInput.IsKeyHold(pianoKey + 2)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);

		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 6 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MIDIInput.IsKeyHold(pianoKey + 5)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 7 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MIDIInput.IsKeyHold(pianoKey + 7)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 8 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MIDIInput.IsKeyHold(pianoKey + 9)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
	}
}
