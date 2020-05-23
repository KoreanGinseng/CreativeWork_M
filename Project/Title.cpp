#include "Title.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init) 
{
	// ‰Šú‰»ˆ—
}

CTitle::~CTitle(void)
{
	// ‰ð•úˆ—
}

void CTitle::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		ChangeScene(SceneName::Game);
	}
}

void CTitle::Render(void) const
{
	CGraphicsUtilities::RenderString(0,  0, "TitleScene");
	CGraphicsUtilities::RenderString(0, 30, "return : go GameScene");
}
