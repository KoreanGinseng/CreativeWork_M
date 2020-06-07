#pragma once
#include "Character.h"
#include "WindowUtillities.h"

class CPlayer : public CCharacter
{
private:



public:

	CPlayer(void);

	virtual ~CPlayer(void);

	virtual void Initialize(void) override;

	virtual void Update(void) override;

	virtual void Render(void) const override;

	virtual void Release(void) override;

};

