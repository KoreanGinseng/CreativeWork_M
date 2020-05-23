#pragma once
#include "Common.h"

class CTitle : public MyApp::CScene
{
private:

public:
	
	explicit CTitle(const CTitle::InitData& init);

	virtual ~CTitle(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) const override;

};