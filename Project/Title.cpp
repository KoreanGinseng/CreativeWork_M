#include "Title.h"
#include "MIDIOut.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// ����������
	m_StartBtn = CButton(CRectangle(SceneWidth * 0.5f - 100, 100, SceneWidth * 0.5f + 100, 200), "�ȑI����");
}

CTitle::~CTitle(void)
{
	// �������
}

void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		m_StartBtn.IsPull())
	{
		ChangeScene(SceneName::Select);
	}
}

void CTitle::Render(void) const
{
	CGraphicsUtilities::RenderString(0,  0, "Title");
	CGraphicsUtilities::RenderString(0, 30, "Enter�L�[�ŃZ���N�g��ʂ�");
	m_StartBtn.Render();
}
