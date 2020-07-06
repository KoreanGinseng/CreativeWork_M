#pragma once
#include "Common.h"
#include "Button.h"

class CSelectScene : public MyApp::CScene
{
private:

	CButton  m_SelectBtnUp;
	CButton  m_SelectBtnDown;
	CButton  m_SetBtn;

public:

	explicit CSelectScene(const CSelectScene::InitData& init);

	virtual ~CSelectScene(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;
};

