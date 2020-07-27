#pragma once
#include "LoadBase.h"
#include "BackRender.h"

class CLoad : public CLoadBase
{
private:

	CBackRender                m_BackRender;

	CEaseMotionController<int> m_AlphaMotion;

	std::shared_ptr<CFontA>    m_pFont;

public:

	CLoad(const CLoad::InitData& init);

	virtual ~CLoad(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;
};

