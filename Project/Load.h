#pragma once
#include "LoadBase.h"

class CLoad : public CLoadBase
{
private:

public:

	CLoad(const CLoad::InitData& init);

	virtual ~CLoad(void);

	virtual void Update(void) override;

	virtual void Render(void) const override;
};

