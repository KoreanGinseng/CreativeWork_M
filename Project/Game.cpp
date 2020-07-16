#include "Game.h"
#include "Load.h"


CMIDIOut          g_MidiOutput;

MofU8             CGame::m_sPlayChannel = 0x00;

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理
	m_sPlayChannel = GetData().channel;
	CNote::SetAutoParam(GetData().autoParam);
	CNote::SetKeyLength(GetData().keyLength);
	CNote::SetKeyOffset(GetData().offsetKey);

	g_NoteArray[g_MusicSelect].Initialize(GetData().trackNo);
	g_PlayResult.Clear();

	//g_NoteArray[g_MusicSelect].SetFallSpeed(GetData().fallSpeed);
	g_NoteArray[g_MusicSelect].SetFallSpeed(g_MusicData[g_MusicSelect].fallSpd);

	int   size     = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[GetData().trackNo].GetArrayCount();
	float fallTime = CheckLineY / g_NoteArray[g_MusicSelect].GetFallSpeed();
	m_EndTime      = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[GetData().trackNo].GetData(size - 1).eventTime / 1000.0f + fallTime + 3.0f;
	
	// DEBUG : ノーツが落ちてくる秒数をデバッグプリントする。(確認用)
	for (int i = 0; i < g_NoteArray[g_MusicSelect].GetNoteArray().GetArrayCount(); i++)
	{
		MOF_PRINTLOG("%d\n", g_NoteArray[g_MusicSelect].GetNoteArray()[i].GetStartTime());
	}

	m_StartTime.Start();
}

CGame::~CGame(void)
{
	// 解放処理

	// 全部の音を一回止める。
	for (int i = 0; i < 128; i++)
	{
		g_MidiOutput.Stop((MofU8)i, m_sPlayChannel);
	}
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
	g_NoteArray[g_MusicSelect].Update();
}

void CGame::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Game");

	// 譜面の縦の線のやつ。
	RenderKeyLine();
	
	// ノーツの描画。
	g_NoteArray[g_MusicSelect].Render();

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
	// 鍵盤の外側
	CGraphicsUtilities::RenderFillRect(0, PianoRollOffsetY, PianoRollOffsetX, SceneHeight, MOF_COLOR_BLACK);
	CGraphicsUtilities::RenderFillRect(SceneWidth - PianoRollOffsetX, PianoRollOffsetY, SceneWidth, SceneHeight, MOF_COLOR_BLACK);
	CGraphicsUtilities::RenderFillRect(0, CheckLineY, SceneWidth, PianoRollOffsetY, MOF_COLOR_BLACK);

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
			g_MidiOutput.IsPlay(pianoKey, m_sPlayChannel)
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
		g_MidiOutput.IsPlay(PianoKey::A0_S, m_sPlayChannel)
		? MOF_COLOR_HRED
		: MOF_COLOR_BLACK
	);

	// C1_S～の描画。
	for (int i = 0; i < 7; i++)
	{
		MofU8 pianoKey = PianoKey::C1_S + (i * PianoBlackKeyWidth);

		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 3 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MidiOutput.IsPlay(pianoKey, m_sPlayChannel)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 4 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MidiOutput.IsPlay(pianoKey + 2, m_sPlayChannel)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);

		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 6 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MidiOutput.IsPlay(pianoKey + 5, m_sPlayChannel)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 7 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MidiOutput.IsPlay(pianoKey + 7, m_sPlayChannel)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
		blackX = PianoRollOffsetX + (PianoWhiteKeyWidth * 8 - PianoBlackKeyWidth * 0.5f) + i * (PianoWhiteKeyWidth * 7);
		CGraphicsUtilities::RenderFillRect(
			blackX, PianoRollOffsetY,
			blackX + PianoBlackKeyWidth, PianoRollOffsetY + PianoBlackKeyHeight,
			g_MidiOutput.IsPlay(pianoKey + 9, m_sPlayChannel)
			? MOF_COLOR_HRED
			: MOF_COLOR_BLACK
		);
	}
}
