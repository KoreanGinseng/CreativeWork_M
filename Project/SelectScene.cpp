#include "SelectScene.h"
#include "Load.h"


int      g_MusicSelect = 0;


CSelectScene::CSelectScene(const CSelectScene::InitData & init) :
	MyApp::CScene::IScene(init)
{
	g_MusicSelect = 0;
}

CSelectScene::~CSelectScene(void)
{
}

void CSelectScene::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_4))
	{
		ChangeScene(SceneName::Setting);
	}

	// �I�������Ȃ�GO!
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		ChangeScene(SceneName::Setting);
		//ChangeScene(SceneName::Load);
		//CLoad::SetLoadFunc(
		//	"midiLoad",
		//	[&]
		//	{
		//		return LoadStanderdMidiFile(g_MusicData[g_MusicSelect].fileName.c_str(), g_NoteArray); 
		//	}
		//);
		//CLoad::SetLoadFuncName("midiLoad");
		//CLoad::SetNextScene(SceneName::Game);

		g_Midiout.ChangeInstrument((GMInstrument)g_MusicData[g_MusicSelect].instrument);
	}

	// �}�E�X�z�C�[���ł̃J�[�\���ړ��B
	int wheelMove = g_pInput->GetMouseWheelMove() * 0.01f;
	if (wheelMove)
	{
		g_MusicSelect += wheelMove;
	}

	// �㉺���L�[�ł̃J�[�\���ړ��B
	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		g_MusicSelect--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		g_MusicSelect++;
	}

	// �Z���N�g�����Ȑ��𒴂��Ȃ��悤�ɂ���B
	g_MusicSelect = MOF_CLIPING(g_MusicSelect, 0, g_MusicData.GetArrayCount() - 1);

}

void CSelectScene::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Select");

	CGraphicsUtilities::RenderString(0, 30, "select : %d", g_MusicSelect);

	CGraphicsUtilities::RenderString(0, 60, "title : %s", g_MusicData[g_MusicSelect].title.c_str());
}
