#include "Button.h"

CButton::CButton(void) :
	m_Pos(),
	m_Size(),
	m_String(""),
	m_pFont(nullptr)
{
}

CButton::~CButton(void)
{
}

void CButton::Initialize(const Vector2 & pos, const Vector2 & size, const std::string & str, const std::shared_ptr<CFontA>& pFont)
{
	SetPos(pos);
	SetSize(size);
	SetString(str);
	SetFont(pFont);
}

void CButton::Render(void) const
{
	CRectangle baseRect  = GetRect();
	CRectangle backRectW = baseRect;
	CRectangle backRectH = baseRect;

	backRectW.Expansion(3, 0);
	backRectH.Expansion(0, 3);

	// ボタンの影。
	if (!IsClickL())
	{
		CGraphicsUtilities::RenderFillRect(baseRect , MOF_COLOR_HBLACK);
		CGraphicsUtilities::RenderFillRect(backRectW, MOF_COLOR_HBLACK);
		CGraphicsUtilities::RenderFillRect(backRectH, MOF_COLOR_HBLACK);

		baseRect. Translation(Vector2(0, -3));
		backRectW.Translation(Vector2(0, -3));
		backRectH.Translation(Vector2(0, -3));
	}

	// ボタン本体。
	CGraphicsUtilities::RenderFillRect(baseRect , MOF_COLOR_CWHITE);
	CGraphicsUtilities::RenderFillRect(backRectW, MOF_COLOR_CWHITE);
	CGraphicsUtilities::RenderFillRect(backRectH, MOF_COLOR_CWHITE);

	// フォントが登録されていない場合、文字の描画はしない。
	if (!m_pFont)
	{
		return;
	}

	// 文字の描画。
	CRectangle textRect;
	m_pFont->CalculateStringRect(0, 0, m_String.c_str(), textRect);
	m_pFont->RenderString(
		baseRect.GetCenter().x - textRect.GetWidth()  * 0.5f,
		baseRect.GetCenter().y - textRect.GetHeight() * 0.5f,
		MOF_COLOR_BLACK, m_String.c_str()
	);

}

void CButton::SetPos(const Vector2 & pos)
{
	m_Pos = pos;
}

void CButton::SetSize(const Vector2 & size)
{
	m_Size = size;
}

void CButton::SetString(const std::string & str)
{
	m_String = str;
}

void CButton::SetFont(const std::shared_ptr<CFontA>& pFont)
{
	m_pFont = pFont;
}

Vector2 CButton::GetPos(void) const
{
	return m_Pos;
}

Vector2 CButton::GetSize(void) const
{
	return m_Size;
}

std::string CButton::GetString(void) const
{
	return m_String;
}

std::shared_ptr<CFontA> CButton::GetFont(void) const
{
	return m_pFont;
}

CRectangle CButton::GetRect(void) const
{
	return CRectangle(m_Pos, m_Pos + m_Size);
}

const bool CButton::IsMouseOrver(void) const noexcept
{
	Vector2 mp;
	g_pInput->GetMousePos(mp);
	return GetRect().CollisionPoint(mp);
}

const bool CButton::IsClickL(void) const noexcept
{
	return IsMouseOrver() && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON);
}
