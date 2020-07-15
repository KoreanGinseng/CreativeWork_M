#include "SelectScene.h"
#include "Load.h"

// ���t�Ȃ̃��X�g�ԍ�
int      g_MusicSelect = 0;


CSelectScene::CSelectScene(const CSelectScene::InitData & init) :
	MyApp::CScene::IScene(init)
{
	g_MusicSelect   = 0;
	m_SelectBtnUp   = CButton(CRectangle(500, 90,530,120), "��");
	m_SelectBtnDown = CButton(CRectangle(500,120,530,150), "��");
	m_SetBtn        = CButton(CRectangle(100,180,200,210), "����");
	m_TruckIndex    = 0;
	m_bAuto         = false;
}

CSelectScene::~CSelectScene(void)
{
}

void CSelectScene::Update(void)
{
	// �I�������Ȃ�GO!
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		m_SetBtn.IsPull())
	{
		GetData().trackNo = g_MusicData[g_MusicSelect].trucks[m_TruckIndex];
		GetData().autoParam = m_bAuto ? Auto::All : Auto::Semi;
		//ChangeScene(SceneName::Setting);
		ChangeScene(SceneName::Game);
	}

	// �}�E�X�z�C�[���ł̃J�[�\���ړ��B
	int wheelMove = g_pInput->GetMouseWheelMove() * 0.01f;
	if (wheelMove)
	{
		g_MusicSelect += wheelMove;
	}

	// �㉺���L�[�ł̃J�[�\���ړ��B
	if (g_pInput->IsKeyPush(MOFKEY_UP) ||
		m_SelectBtnUp.IsPull())
	{
		g_MusicSelect--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN) ||
		m_SelectBtnDown.IsPull())
	{
		g_MusicSelect++;
	}

	// ���E���L�[�Ńg���b�N�̑I���B
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		m_TruckIndex--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		m_TruckIndex++;
	}

	// Space�L�[�ŃI�[�g�v���C�؂�ւ��B
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		m_bAuto = !m_bAuto;
	}

	// �Z���N�g�����Ȑ��𒴂��Ȃ��悤�ɂ���B
	g_MusicSelect = MOF_CLIPING(g_MusicSelect, 0, g_MusicData.GetArrayCount() - 1);
	m_TruckIndex  = MOF_CLIPING(m_TruckIndex , 0, g_MusicData[g_MusicSelect].trucks.size() - 1);
}

void CSelectScene::Render(void) const
{
	CGraphicsUtilities::RenderString(0,   0, "Select");

	CGraphicsUtilities::RenderString(0,  30, "select : %d", g_MusicSelect);

	CGraphicsUtilities::RenderString(0,  60, "title : %s", g_MusicData[g_MusicSelect].title.c_str());

	CGraphicsUtilities::RenderString(0,  90, "�㉺�L�[�ŋȑI���AEnter�L�[�ŉ��t������");

	CGraphicsUtilities::RenderString(0, 120, "truckNo : %2u", g_MusicData[g_MusicSelect].trucks[m_TruckIndex]);

	CGraphicsUtilities::RenderString(0, 150, "Auto : %s", m_bAuto ? "TRUE" : "FALSE");
	
	m_SelectBtnDown.Render();
	m_SelectBtnUp.Render();
	m_SetBtn.Render();
}
