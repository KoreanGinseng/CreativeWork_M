#include "Game.h"

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// ����������

}

CGame::~CGame(void)
{
	// �������
}

void CGame::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		ChangeScene(SceneName::Title);
	}
}

void CGame::Render(void) const
{
	CGraphicsUtilities::RenderString(0,  0, "GameScene");
	CGraphicsUtilities::RenderString(0, 30, "return : go TitleScene");
}
