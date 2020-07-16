#pragma once
#include "Common.h"

class CButton
{
private:

	CRectangle                m_Rect;

	MofU32                    m_Color[4];

	MofU32                    m_FontColor;

	bool                      m_bMultiColor;

	std::shared_ptr<CFontA>   m_pFont;

	std::shared_ptr<CTexture> m_pTexture;

	std::string               m_String;

	void RenderTexture(void) const;

	void RenderColor(void) const;

	void RenderFont(void) const;

public:

	CButton(void);

	CButton(const CButton& btn);

	CButton(const CRectangle& rect);
	
	CButton(const CRectangle& rect, const std::string& str, const std::shared_ptr<CFontA>& pFont = nullptr);

	~CButton(void);

	void Render(void) const;

	void SetString(const std::string& str);

	void SetFont(const std::shared_ptr<CFontA>& pFont);	

	void SetTexture(const std::shared_ptr<CTexture>& pTexture);

	void SetFontColor(const MofU32& color);

	void SetColor(const MofU32& color);

	void SetColor(const MofU32& ltc, const MofU32& lbc, const MofU32& rtc, const MofU32& rbc);

	bool IsPush(void) const;

	bool IsHold(void) const;

	bool IsPull(void) const;

	CRectangle GetRect(void) const;

	CRectangle& GetRect(void);
};

