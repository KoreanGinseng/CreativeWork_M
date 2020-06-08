#pragma once
#include "Common.h"

class CSetting : public MyApp::CScene
{
private:

	int m_Select;

public:

	explicit CSetting(const InitData& init);

	virtual ~CSetting(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;

};

