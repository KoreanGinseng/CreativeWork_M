#include "Title.h"
#include "MIDIOut.h"

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
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		ChangeScene(SceneName::Select);
	}
}

void CTitle::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Title");
}
