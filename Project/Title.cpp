#include "Title.h"
#include "MIDIOut.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// 初期化処理
	m_Scale    = 1.0f;
	m_Rotate   = 0.0f;
	m_pTitleTexture = TextureAsset("Title");

	m_ScaleMotion << CEaseMotion<float>(1.0f, 0.8f, Ease::Out, EaseType::Sine, 0.2f);
	m_ScaleMotion << CEaseMotion<float>(0.8f, 1.4f, Ease::Out, EaseType::Sine, 0.3f);
	m_ScaleMotion << CEaseMotion<float>(1.4f, 1.0f, Ease::In , EaseType::Sine, 0.2f);

	m_ScaleMotion.Start();
}

CTitle::~CTitle(void)
{
	// 解放処理
}

void CTitle::Update(void)
{
	Vector2 mp;
	g_pInput->GetMousePos(mp);
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		(CCircle(SceneWidth * 0.5f, SceneHeight * 0.5f, m_pTitleTexture->GetWidth() * 0.5f * m_Scale).CollisionPoint(mp) &&
		g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)))
	{
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

	m_Rotate = MOF_NORMALIZE_RADIANANGLE(m_Rotate);
}

void CTitle::Render(void) const
{
	m_pTitleTexture->RenderScaleRotate(SceneWidth * 0.5f, SceneHeight * 0.5f, m_Scale, m_Rotate, TEXALIGN_CENTERCENTER);
}
