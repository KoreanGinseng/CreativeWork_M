#include "BackRender.h"

CBackRender::CBackRender(void)
{
	for (int i = 0; i < 30; i++)
	{
		m_BackIconRotate[i] = MOF_ToRadian(CUtilities::Random(0, 360));
		int x = CUtilities::Random(1000, 1800);
		int y = CUtilities::Random( 200,  500);
		if (x < SceneWidth)
		{
			y = -static_cast<float>(CUtilities::Random(200, 500));
		}
		m_BackIconPos[i]      = Vector2(x, y);
		m_pBackIconTexture[i] = TextureAsset(TextureData[TexName::Kirin_1 + CUtilities::Random(3)].first);
	}

	m_Scale    = 1.0f;
	m_Rotate   = 0.0f;
	m_pTitleTexture = TextureAsset("Title");

	m_ScaleMotion << CEaseMotion<float>(1.0f, 1.2f, Ease::InOut, EaseType::Sine, 0.5f);
	m_ScaleMotion << CEaseMotion<float>(1.2f, 1.0f, Ease::InOut, EaseType::Sine, 0.5f);

	m_ScaleMotion.Start();
}

CBackRender::~CBackRender(void)
{
}

void CBackRender::Update(void)
{
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

	for (int i = 0; i < 30; i++)
	{
		m_BackIconRotate[i] += 0.01f;
		m_BackIconPos[i] += Vector2(-2.0f, 1.5f);

		if (m_BackIconPos[i].x + 200 < 0 ||
			m_BackIconPos[i].y - 100 > SceneHeight)
		{
			m_BackIconRotate[i] = MOF_ToRadian(CUtilities::Random(0, 360));
			int x = CUtilities::Random(1000, 1500);
			int y = CUtilities::Random( 200,  500);
			if (x < SceneWidth)
			{
				y = -static_cast<float>(CUtilities::Random(200, 500));
			}
			m_BackIconPos[i]      = Vector2(x, y);
			m_pBackIconTexture[i] = TextureAsset(TextureData[TexName::Kirin_1 + CUtilities::Random(3)].first);
		}
	}
}

void CBackRender::Render(void) const
{
	for (int i = 0; i < 30; i++)
	{
		m_pBackIconTexture[i]->RenderScaleRotate(m_BackIconPos[i].x, m_BackIconPos[i].y, 0.5f, m_BackIconRotate[i], MOF_ALPHA_WHITE(64), TEXALIGN_CENTERCENTER);
	}

	m_pTitleTexture->RenderScaleRotate(SceneWidth * 0.5f, SceneHeight * 0.5f, m_Scale, m_Rotate, MOF_ALPHA_WHITE(128), TEXALIGN_CENTERCENTER);
}

void CBackRender::RenderBackBoard(const Vector2& centerPos, const Vector2& scale, const MofU32& color)
{
	g_pGraphics->SetStencilEnable(TRUE);
	g_pGraphics->SetStencilControl(ComparisonFunc::COMPARISON_ALWAYS, StencilOp::STENCIL_INCR, StencilOp::STENCIL_INCR, StencilOp::STENCIL_INCR);

	g_pGraphics->SetColorWriteEnable(FALSE);
	TextureAsset("Back_1")->RenderScale(centerPos.x, centerPos.y, scale.x, scale.y, TEXALIGN_CENTERCENTER);
	g_pGraphics->SetColorWriteEnable(TRUE);

	g_pGraphics->SetStencilControl(ComparisonFunc::COMPARISON_LESS, StencilOp::STENCIL_KEEP, StencilOp::STENCIL_KEEP, StencilOp::STENCIL_KEEP);

	Vector2 texSize(TextureAsset("Back_1")->GetWidth() * scale.x, TextureAsset("Back_1")->GetHeight() * scale.y);
	CRectangle rect(centerPos.x - texSize.x, centerPos.y - texSize.y, centerPos.x + texSize.x, centerPos.y + texSize.y);
	CGraphicsUtilities::RenderFillRect(rect, color);

	g_pGraphics->SetStencilEnable(FALSE);
}