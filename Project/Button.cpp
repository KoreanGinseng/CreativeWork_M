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
}

void CButton::Render(void) const
{
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
