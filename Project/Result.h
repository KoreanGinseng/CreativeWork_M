#pragma once
#include "Common.h"
#include "BackRender.h"
#include "Button.h"

class CResult : public MyApp::CScene
{
private:

	CBackRender               m_BackRender;

	std::shared_ptr<CFontA>   m_pFont;
	
	std::shared_ptr<CTexture> m_pTexture;

	CButton                   m_BackBtn;

public:

	explicit CResult(const CResult::InitData& init);

	virtual ~CResult(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;

	void RenderBackBoard(const Vector2& centerPos, const Vector2& scale) const;
};

