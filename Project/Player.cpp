#include "Player.h"

CPlayer::CPlayer(void) :
	CCharacter()
{
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Initialize(void)
{

}

void CPlayer::Update(void)
{

}

void CPlayer::Render(void) const
{
	// �e�N�X�`�����Ȃ���Ε`�悵�Ȃ��B
	if (!m_pTexture)
	{
		return;
	}

	// ���W���摜�̉����S�ɉ摜��`�悷��B
	float scale = WindowScale[CWindowUtillities::GetWindowSize()];
	m_pTexture->RenderScale(m_Pos.x * scale, m_Pos.y * scale, scale, TEXALIGN_BOTTOMCENTER);
}

void CPlayer::Release(void)
{

}
