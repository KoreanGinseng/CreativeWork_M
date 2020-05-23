#pragma once
#include "Common.h"

class CGame : public MyApp::CScene
{
private:

public:
	
	explicit CGame(const CGame::InitData& init);

	virtual ~CGame(void);
	
	virtual void Update(void) override;
	
	virtual void Render(void) const override;

};