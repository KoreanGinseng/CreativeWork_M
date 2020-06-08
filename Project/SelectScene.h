#pragma once
#include "Common.h"

class CSelectScene : public MyApp::CScene
{
private:

public:

	explicit CSelectScene(const CSelectScene::InitData& init);

	virtual ~CSelectScene(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;
};

