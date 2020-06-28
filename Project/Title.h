#pragma once
#include "Common.h"
#include "Button.h"

class CTitle : public MyApp::CScene
{
private:

	CButton m_StartBtn;

public:
	
	explicit CTitle(const CTitle::InitData& init);

	virtual ~CTitle(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) const override;

};