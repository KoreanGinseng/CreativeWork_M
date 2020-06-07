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
	// テクスチャがなければ描画しない。
	if (!m_pTexture)
	{
		return;
	}

	// 座標を画像の下中心に画像を描画する。
	float scale = WindowScale[CWindowUtillities::GetWindowSize()];
	m_pTexture->RenderScale(m_Pos.x * scale, m_Pos.y * scale, scale, TEXALIGN_BOTTOMCENTER);
}

void CPlayer::Release(void)
{

}
