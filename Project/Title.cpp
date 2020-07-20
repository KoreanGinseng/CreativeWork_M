#include "Title.h"
#include "MIDIOut.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理
	m_Scale    = 1.0f;
	m_Rotate   = 0.0f;
	m_pTitleTexture = TextureAsset("Title");

	SoundAsset("BGM_Title")->SetLoop(TRUE);
	SoundAsset("BGM_Title")->Play();
	SoundAsset("BGM_Title")->SetVolume(0.3f);

	for (int i = 0; i < 30; i++)
	{
		m_BackIconRotate[i] = MOF_ToRadian(CUtilities::Random(0, 360));
		int x = CUtilities::Random(1000, 1800);
		int y = CUtilities::Random( 200,  500);
		if (x < SceneWidth)
		{
			y = -CUtilities::Random(200, 500);
		}
		m_BackIconPos[i]      = Vector2(x, y);
		m_pBackIconTexture[i] = TextureAsset(TextureData[TexName::Kirin_1 + CUtilities::Random(3)].first);
	}

	m_ScaleMotion << CEaseMotion<float>(1.0f, 0.8f, Ease::Out, EaseType::Sine, 0.3f);
	m_ScaleMotion << CEaseMotion<float>(0.8f, 1.4f, Ease::Out, EaseType::Sine, 0.4f);
	m_ScaleMotion << CEaseMotion<float>(1.4f, 1.0f, Ease::In , EaseType::Sine, 0.3f);

	m_ScaleMotion.Start();
}

CTitle::~CTitle(void)
{
	// 解放処理
	SoundAsset("BGM_Title")->Stop();
}

void CTitle::Update(void)
{
	Vector2 mp;
	g_pInput->GetMousePos(mp);
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		(CCircle(SceneWidth * 0.5f, SceneHeight * 0.5f, m_pTitleTexture->GetWidth() * 0.5f * m_Scale).CollisionPoint(mp) &&
		g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)))
	{
		SoundAsset("SE_Enter")->Play();
		ChangeScene(SceneName::Select);
	}

	// タイトルの拡大モーション更新。
	m_ScaleMotion.Update();

	m_Scale = m_ScaleMotion.GetValue();

	// ループさせる。
	if (m_ScaleMotion.IsEnd())
	{
		m_ScaleMotion.Reset();
		m_ScaleMotion.Start();
	}

	m_Rotate += 0.01f;

	for (int i = 0; i < 30; i++)
	{
		m_BackIconRotate[i] += 0.01f;
		m_BackIconPos[i] += Vector2(-4, 3);

		if (m_BackIconPos[i].x + 200 < 0 ||
			m_BackIconPos[i].y - 100 > SceneHeight)
		{
			m_BackIconRotate[i] = MOF_ToRadian(CUtilities::Random(0, 360));
			int x = CUtilities::Random(1000, 1500);
			int y = CUtilities::Random( 200,  500);
			if (x < SceneWidth)
			{
				y = -CUtilities::Random(200, 500);
			}
			m_BackIconPos[i]      = Vector2(x, y);
			m_pBackIconTexture[i] = TextureAsset(TextureData[TexName::Kirin_1 + CUtilities::Random(3)].first);
		}
	}

	m_Rotate = MOF_NORMALIZE_RADIANANGLE(m_Rotate);
}

void CTitle::Render(void) const
{
	for (int i = 0; i < 30; i++)
	{
		m_pBackIconTexture[i]->RenderScaleRotate(m_BackIconPos[i].x, m_BackIconPos[i].y, 0.5f, m_BackIconRotate[i], MOF_ALPHA_WHITE(128), TEXALIGN_CENTERCENTER);
	}

	m_pTitleTexture->RenderScaleRotate(SceneWidth * 0.5f, SceneHeight * 0.5f, m_Scale, m_Rotate, TEXALIGN_CENTERCENTER);
}
