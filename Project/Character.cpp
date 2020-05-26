#include "Character.h"

CCharacter::CCharacter(void) :
	m_Hp(0),
	m_pTexture(nullptr),
	m_bDead(false),
	m_Pos()
{
}

CCharacter::~CCharacter(void)
{
}

void CCharacter::Damage(const int& dmg)
{
	m_Hp -= dmg;

	// �̗͂�0�ȉ��̏ꍇ�A���S�t���O�𗧂Ă�B
	if (m_Hp <= 0)
	{
		m_bDead = true;
	}
}

void CCharacter::SetTexture(const std::shared_ptr<CTexture>& pTexture)
{
	m_pTexture = pTexture;
}

void CCharacter::SetPos(const Vector2 & pos)
{
	m_Pos = pos;
}

const bool CCharacter::IsDead(void) const
{
	return m_bDead;
}
