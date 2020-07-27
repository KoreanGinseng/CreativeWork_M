#include "Result.h"

CResult::CResult(const CResult::InitData & init) :
	MyApp::CScene::IScene(init)
{
	SoundAsset("BGM_Result")->SetLoop(TRUE);
	SoundAsset("BGM_Result")->Play();
	SoundAsset("BGM_Result")->SetVolume(0.3f);

	m_pFont    = FontAsset("Result");
	m_pFont->SetSize(50);

	m_BackBtn = CButton(CRectangle(SceneWidth - 30 - TextureAsset("Back_2")->GetWidth(), SceneHeight - 30 - TextureAsset("Back_2")->GetHeight(), SceneWidth - 30, SceneHeight - 30));
	m_BackBtn.SetTexture(TextureAsset("Back_2"));
}

CResult::~CResult(void)
{
	SoundAsset("BGM_Result")->Stop();
}

void CResult::Update(void)
{
	// エンターキーでセレクト画面へ。
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		m_BackBtn.IsPull())
	{
		SoundAsset("SE_Enter")->Play();
		ChangeScene(SceneName::Select);
	}

	m_BackRender.Update();
}

void CResult::Render(void) const
{
	m_BackRender.Render();

	CBackRender::RenderBackBoard(Vector2(SceneWidth * 0.5f - 250, SceneHeight * 0.5f), Vector2(5.0f, 4.0f), MOF_ALPHA_WHITE(64));

	m_pFont->RenderFormatString(50,  10, g_MusicData[g_MusicSelect].title.c_str());
	m_pFont->RenderFormatString(50, 100, "PERFECT" ); m_pFont->RenderFormatString(400, 100, "%05dx", g_PlayResult.perfect);
	m_pFont->RenderFormatString(50, 150, "GREAT"   ); m_pFont->RenderFormatString(400, 150, "%05dx", g_PlayResult.great);
	m_pFont->RenderFormatString(50, 200, "GOOD"    ); m_pFont->RenderFormatString(400, 200, "%05dx", g_PlayResult.good);
	m_pFont->RenderFormatString(50, 250, "BAD"     ); m_pFont->RenderFormatString(400, 250, "%05dx", g_PlayResult.bad);
	m_pFont->RenderFormatString(50, 300, "MISS"    ); m_pFont->RenderFormatString(400, 300, "%05dx", g_PlayResult.miss);
	m_pFont->RenderFormatString(50, 350, "MAXCOMBO"); m_pFont->RenderFormatString(400, 350, "%05dx", g_PlayResult.maxCombo);
	
	int comboCount  = g_NoteArray[g_MusicSelect].GetNoteArray().GetArrayCount();
	bool bFullCombo = (comboCount == g_PlayResult.maxCombo);
	
	m_pFont->RenderFormatString(50, 450, MOF_XRGB(255, 51, 255), "%s", bFullCombo ? "FULLCOMBO!!!" : "");
	m_pFont->RenderFormatString(50, 500, "SCORE"   ); m_pFont->RenderFormatString(300, 500, "%010d", g_PlayResult.score);
	int hiScore = CScoreManager::GetScoreValue(ScoreKey(g_MusicData[g_MusicSelect].title.c_str(), GetData().trackNo));
	m_pFont->RenderFormatString(50, 550, "HISCORE" ); m_pFont->RenderFormatString(300, 550, "%010d", hiScore);

	m_BackBtn.Render();
}
