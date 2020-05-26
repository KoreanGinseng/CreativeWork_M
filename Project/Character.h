#pragma once
#include "Common.h"

class CCharacter
{
protected:

	int                               m_Hp;

	std::shared_ptr<CTexture>         m_pTexture;

	bool                              m_bDead;

	Vector2                           m_Pos;

public:

	CCharacter(void);

	virtual ~CCharacter(void);

	virtual void Initialize(void) = 0;

	virtual void Update(void) = 0;

	virtual void Render(void) = 0;

	virtual void Release(void) = 0;

	virtual void Damage(const int& dmg);

	void SetTexture(const std::shared_ptr<CTexture>& pTexture);

	void SetPos(const Vector2& pos);

	const bool IsDead(void) const;

};

