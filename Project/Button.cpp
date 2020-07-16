#include "Button.h"

CButton::CButton(void) :
	CButton(CRectangle())
{
}

CButton::CButton(const CButton & btn)
{
	m_Rect        = btn.m_Rect;
	m_Color[0]    = btn.m_Color[0];
	m_Color[1]    = btn.m_Color[1];
	m_Color[2]    = btn.m_Color[2];
	m_Color[3]    = btn.m_Color[3];
	m_FontColor   = btn.m_FontColor;
	m_bMultiColor = btn.m_bMultiColor;
	m_pFont       = btn.m_pFont;
	m_pTexture    = btn.m_pTexture;
	m_String      = btn.m_String;
}

CButton::CButton(const CRectangle& rect) :
	CButton(rect, "", nullptr)
{
}

CButton::CButton(const CRectangle& rect, const std::string & str, const std::shared_ptr<CFontA>& pFont) :
	m_Rect(rect),
	m_String(str),
	m_pFont(pFont),
	m_pTexture(nullptr),
	m_bMultiColor(false),
	m_FontColor(MOF_COLOR_BLACK)
{
	m_Color[0] = MOF_COLOR_WHITE;
}

CButton::~CButton(void)
{
	m_pFont = nullptr;
	m_pTexture = nullptr;
}

void CButton::Render(void) const
{
	// テクスチャが設定されている場合とそうでない場合で描画方法を変える。
	if (m_pTexture != nullptr)
	{
		RenderTexture();
	}
	else
	{
		RenderColor();
	}

	RenderFont();
}

void CButton::RenderTexture(void) const
{
	g_pGraphics->SetStencilEnable(TRUE);
	g_pGraphics->SetStencilControl(ComparisonFunc::COMPARISON_ALWAYS, StencilOp::STENCIL_INCR, StencilOp::STENCIL_INCR, StencilOp::STENCIL_INCR);
	
	m_pTexture->Render(m_Rect);

	g_pGraphics->SetStencilControl(ComparisonFunc::COMPARISON_LESS, StencilOp::STENCIL_KEEP, StencilOp::STENCIL_KEEP, StencilOp::STENCIL_KEEP);
	
	if (IsHold())
	{
		CGraphicsUtilities::RenderFillRect(m_Rect, MOF_ALPHA_WHITE(64));
	}
	
	g_pGraphics->SetStencilEnable(FALSE);
}

void CButton::RenderColor(void) const
{
	if (m_bMultiColor)
	{
		CGraphicsUtilities::RenderFillRect(m_Rect, m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	}
	else
	{
		CGraphicsUtilities::RenderFillRect(m_Rect, m_Color[0]);
	}
}

void CButton::RenderFont(void) const
{
	CRectangle outRect;

	// フォントが設定されているかどうかで処理を変える。
	// 中央寄せで文字を描画する。
	if (m_pFont != nullptr)
	{
		m_pFont->CalculateStringRect(0, 0, m_String.c_str(), outRect);

		float x = (m_Rect.GetWidth()  - outRect.GetWidth() ) * 0.5f;
		float y = (m_Rect.GetHeight() - outRect.GetHeight()) * 0.5f;

		m_pFont->RenderString(m_Rect.Left + x, m_Rect.Top + y, m_FontColor, m_String.c_str());
	}
	else
	{
		CGraphicsUtilities::CalculateStringRect(0, 0, m_String.c_str(), outRect);

		float x = (m_Rect.GetWidth()  - outRect.GetWidth() ) * 0.5f;
		float y = (m_Rect.GetHeight() - outRect.GetHeight()) * 0.5f;

		CGraphicsUtilities::RenderString(m_Rect.Left + x, m_Rect.Top + y, m_FontColor, m_String.c_str());
	}
}

void CButton::SetString(const std::string & str)
{
	m_String = str;
}

void CButton::SetFont(const std::shared_ptr<CFontA>& pFont)
{
	m_pFont = pFont;
}

void CButton::SetTexture(const std::shared_ptr<CTexture>& pTexture)
{
	m_pTexture = pTexture;
}

void CButton::SetFontColor(const MofU32 & color)
{
	m_FontColor = color;
}

void CButton::SetColor(const MofU32 & color)
{
	m_bMultiColor = false;
	m_Color[0] = color;
}

void CButton::SetColor(const MofU32 & ltc, const MofU32 & lbc, const MofU32 & rtc, const MofU32 & rbc)
{
	m_bMultiColor = true;
	m_Color[0] = ltc;
	m_Color[1] = lbc;
	m_Color[2] = rtc;
	m_Color[3] = rbc;
}

bool CButton::IsPush(void) const
{
	Vector2 mousePos;
	g_pInput->GetMousePos(mousePos);
	if (GetRect().CollisionPoint(mousePos) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		return true;
	}
	return false;
}

bool CButton::IsHold(void) const
{
	Vector2 mousePos;
	g_pInput->GetMousePos(mousePos);
	if (GetRect().CollisionPoint(mousePos) && g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	{
		return true;
	}
	return false;
}

bool CButton::IsPull(void) const
{
	Vector2 mousePos;
	g_pInput->GetMousePos(mousePos);
	if (GetRect().CollisionPoint(mousePos) && g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
	{
		return true;
	}
	return false;
}

CRectangle CButton::GetRect(void) const
{
	return m_Rect;
}

CRectangle & CButton::GetRect(void)
{
	return m_Rect;
}
