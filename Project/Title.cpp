#include "Title.h"

CTitle::CTitle(const CTitle::InitData & init) :
	MyApp::CScene::IScene(init) 
{
	// 初期化処理
}

CTitle::~CTitle(void)
{
	// 解放処理
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
