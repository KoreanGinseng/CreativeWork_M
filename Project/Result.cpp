#include "Result.h"

CResult::CResult(const CResult::InitData & init) :
	MyApp::CScene::IScene(init)
{
}

CResult::~CResult(void)
{
}

void CResult::Update(void)
{
	// エンターキーでセレクト画面へ。
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		ChangeScene(SceneName::Select);
	}
}

void CResult::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Result");

	CGraphicsUtilities::RenderString(0,  30, "PERFECT  : %05d", g_PlayResult.perfect);
	CGraphicsUtilities::RenderString(0,  60, "GREAT    : %05d", g_PlayResult.great);
	CGraphicsUtilities::RenderString(0,  90, "GOOD     : %05d", g_PlayResult.good);
	CGraphicsUtilities::RenderString(0, 120, "BAD      : %05d", g_PlayResult.bad);
	CGraphicsUtilities::RenderString(0, 150, "MISS     : %05d", g_PlayResult.miss);
	CGraphicsUtilities::RenderString(0, 210, "MAXCOMBO : %05d", g_PlayResult.maxCombo);

	int comboCount = g_NoteArray[g_MusicSelect].GetNoteArray().GetArrayCount();
	bool bFullCombo = (comboCount == g_PlayResult.maxCombo);
	CGraphicsUtilities::RenderString(0, 270, "%s", bFullCombo ? "FULLCOMBO!!!" : "");

	CGraphicsUtilities::RenderString(0, 300, "Enterキーでセレクト画面へ戻る。");
}
