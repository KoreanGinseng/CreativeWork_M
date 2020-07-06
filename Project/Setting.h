#pragma once
#include "Common.h"
#include "Button.h"

class CSetting : public MyApp::CScene
{
private:

	int m_Select;

	CButton m_SelectUp;
	CButton m_SelectDown;
	CButton m_SelectLeft;
	CButton m_SelectRight;
	CButton m_Start;
	CButton m_Back;

public:

	explicit CSetting(const InitData& init);

	virtual ~CSetting(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;

};

