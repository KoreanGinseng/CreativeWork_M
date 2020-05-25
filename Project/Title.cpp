#include "Title.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init) 
{
	// ����������

	// �{�^���t�H���g�̓o�^�B
	m_pBtnFont = FontAsset("Button");
	m_pBtnFont->SetSize(24);

	// �X�^�[�g�{�^���̏������B
	m_BtnGameStart.Initialize(Vector2(350, 300), Vector2(100, 30), "�n�߂�", m_pBtnFont);
}

CTitle::~CTitle(void)
{
	// �������
}

void CTitle::Update(void)
{
	if (m_BtnGameStart.IsClickL())
	{
		ChangeScene(SceneName::Game);
	}
}

void CTitle::Render(void) const
{
	CGraphicsUtilities::RenderString(0,  0, "TitleScene");

	m_BtnGameStart.Render();
}
