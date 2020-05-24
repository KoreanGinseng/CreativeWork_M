#pragma once
#include "Common.h"

class CButton
{
private:

	Vector2                 m_Pos;

	Vector2                 m_Size;

	std::string             m_String;

	std::shared_ptr<CFontA> m_pFont;

public:

	CButton(void);
	
	~CButton(void);

	void Initialize(const Vector2& pos, const Vector2& size, const std::string& str = "", const std::shared_ptr<CFontA>& pFont = nullptr);

	void Render(void) const;

	void SetPos(const Vector2& pos);

	void SetSize(const Vector2& size);

	void SetString(const std::string& str);

	void SetFont(const std::shared_ptr<CFontA>& pFont);

	Vector2 GetPos(void) const;

	Vector2 GetSize(void) const;

	std::string GetString(void) const;

	std::shared_ptr<CFontA> GetFont(void) const;
	
	CRectangle GetRect(void) const;

	const bool IsMouseOrver(void) const noexcept;
	
	const bool IsClickL(void) const noexcept;

};

