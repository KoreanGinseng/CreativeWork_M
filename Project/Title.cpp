#include "Title.h"
#include "MIDIOut.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init) 
{
	// ����������
}

CTitle::~CTitle(void)
{
	// �������
}

void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		ChangeScene(SceneName::Select);
	}
}

void CTitle::Render(void) const
{
	CGraphicsUtilities::RenderString(0,  0, "Title");
	CGraphicsUtilities::RenderString(0, 30, "Enter�L�[�ŃZ���N�g��ʂ�");
}
