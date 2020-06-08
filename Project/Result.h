#pragma once
#include "Common.h"

class CResult : public MyApp::CScene
{
public:

	explicit CResult(const CResult::InitData& init);

	virtual ~CResult(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;
};

