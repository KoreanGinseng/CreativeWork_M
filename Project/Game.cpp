#include "Game.h"
#include "Load.h"


CMIDIOut          g_MidiOutput;

MofU8             CGame::m_sPlayChannel = 0x00;

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理

	// フォントの設定。
	m_pFont = FontAsset("Info");
	m_pFont->SetSize(40);

	// 演奏するチャンネルの設定。
	m_sPlayChannel = GetData().channel;

	// 演奏するパラメータの設定。
	CNote::SetAutoParam(GetData().autoParam);
	CNote::SetKeyLength(GetData().keyLength);
	CNote::SetKeyOffset(GetData().offsetKey);

	// アクセスの簡略化。
	CNoteArray*    pNoteArray           = &(g_NoteArray[g_MusicSelect]);
	MusicData*     pMusicData           = &(g_MusicData[g_MusicSelect]);
	CDynamicArray<NoteDataArray>* pNDAA = &(pNoteArray->GetSMFData().GetNoteArray());
	NoteDataArray* pNoteDataArray       = &((*pNDAA)[GetData().trackNo]);

	// 演奏するノーツを初期化する。
	pNoteArray->Initialize(GetData().trackNo, &m_Score);
	// 演奏結果のリセット。
	g_PlayResult.Clear();

	// 落下速度の設定。
	pNoteArray->SetFallSpeed(pMusicData->fallSpd);

	// 演奏終了時間の算出。
	int   size     = pNoteDataArray->GetArrayCount();
	float fallTime = CheckLineY / pNoteArray->GetFallSpeed();
	m_EndTime      = pNoteDataArray->GetData(size - 1).eventTime / 1000.0f + fallTime + 3.0f;

	// 音色変更の適応。
	for (int i = 0; i < pMusicData->trucks.size(); i++)
	{
		GMInstrument instrument = static_cast<GMInstrument>(pMusicData->instruments[i]);
		g_MidiOutput.ChangeInstrument(instrument, pMusicData->trucks[i]);
	}
	
	// DEBUG : ノーツが落ちてくる秒数をデバッグプリントする。(確認用)
	for (int i = 0; i < pNoteArray->GetNoteArray().GetArrayCount(); i++)
	{
		MOF_PRINTLOG("%d\n", pNoteArray->GetNoteArray()[i].GetStartTime());
	}

	// 演奏するスコアの登録。
	m_ScoreKey = std::pair<std::string, int>(pMusicData->title.c_str(), GetData().trackNo);

	// モーションの作成。
	m_ComboMotion << CEaseMotion<float>( 0.0f, -5.0f, Ease::Out, EaseType::Expo, 0.25f);
	m_ComboMotion << CEaseMotion<float>(-5.0f,  0.0f, Ease::In , EaseType::Expo, 0.25f);

	// タイマーをスタートさせる。
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

	int prevCombo = g_PlayResult.combo;

	// 2キーでタイトルへ戻る。
	if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		ChangeScene(SceneName::Title);
	}
	// 終わったらリザルトへ。
	if (m_StartTime.GetTime() > m_EndTime)
	{
		// スコアの更新判定。
		g_PlayResult.score = m_Score.GetScore();
		int prev = CScoreManager::GetScoreValue(m_ScoreKey);
		int now = m_Score.GetScore();
		if (prev < now)
		{
			CScoreManager::GetScore(m_ScoreKey).SetScore(now);
		}
		if (g_PlayResult.maxCombo > CScoreManager::GetScore(m_ScoreKey).GetMaxCombo())
		{
			CScoreManager::GetScore(m_ScoreKey).SetMaxCombo(g_PlayResult.maxCombo);
		}

		ChangeScene(SceneName::Result);
	}

	// ノーツの更新。
	g_NoteArray[g_MusicSelect].Update();

	// コンボのモーションを再生する。
	if (prevCombo != g_PlayResult.combo)
	{
		m_ComboMotion.Reset();
		m_ComboMotion.Start();
	}

	m_ComboMotion.Update();
}

void CGame::Render(void) const
{
	// 譜面の縦の線のやつ。
	RenderKeyLine();
	
	// ノーツの描画。
	g_NoteArray[g_MusicSelect].Render();

	// 判定ラインの描画。
	//RenderCheckLine();
	
	// スコアの描画。
	CRectangle scoreRect;
	m_pFont->CalculateStringRect(30, 30, "0000000000", scoreRect);
	scoreRect.Expansion(10);
	CGraphicsUtilities::RenderFillRect(scoreRect, MOF_ALPHA_BLACK(0), MOF_ALPHA_BLACK(64), MOF_ALPHA_BLACK(0), MOF_ALPHA_BLACK(64));
	m_pFont->RenderFormatString(30, 30, MOF_ALPHA_WHITE(196), "%010d", m_Score.GetScore());

	// コンボカウントを表示する位置を計算する。
	CRectangle comboRect;
	m_pFont->CalculateStringRect(0, 0, std::string(std::to_string(g_PlayResult.combo) + " Combo").c_str(), comboRect);
	int offsetX = SceneWidth - comboRect.Right - 30;

	// コンボカウントのアニメーション表示。
	m_pFont->RenderFormatString(offsetX, 60 + m_ComboMotion.GetValue(), MOF_ALPHA_WHITE(196), "%d", g_PlayResult.combo);

	// Comboを表示するためにずらす位置を再計算する。
	m_pFont->CalculateStringRect(0, 0, std::to_string(g_PlayResult.combo).c_str(), comboRect);
	m_pFont->RenderString(offsetX + comboRect.Right, 60, MOF_ALPHA_WHITE(196), " Combo");

	// とりあえずラインひいとけばそれっぽく見える。
	CGraphicsUtilities::RenderLine(offsetX - 10, 60 + comboRect.Bottom + 3, SceneWidth - 10, 60 + comboRect.Bottom + 3, MOF_ALPHA_WHITE(196));

	// ヒットリザルトの描画。
	NoteHitResult hit = CNote::GetHitResult();

	std::string hitstr = 
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
		: "PERFECT";

	float scale   = (1.0f - (m_ComboMotion.GetValue() / 15.0f));
	m_pFont->CalculateStringRect(0, 0, hitstr.c_str(), comboRect);
	float resultX = SceneWidth - comboRect.GetWidth() - 30;
	float resultY = 60 + comboRect.Bottom + 10;

	m_pFont->RenderStringScale(
		resultX - (comboRect.GetWidth() * scale - comboRect.GetWidth()) * 0.5f, resultY, scale,
		MOF_ALPHA_WHITE(196),
		hitstr.c_str()
	);

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

