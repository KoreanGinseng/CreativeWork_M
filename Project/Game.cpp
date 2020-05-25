#include "Game.h"

CGame::CGame(const CGame::InitData & init) :
	MyApp::CScene::IScene(init)
{
	// ����������

	// �{�^���p�t�H���g�̓o�^�B
	m_pBtnFont = FontAsset("Button");
	m_pBtnFont->SetSize(16);

	// �E�B���h�E�T�C�Y�ύX�̃{�^���̏������B
	m_BtnWindowSize[WindowSize::LARGE ].Initialize(Vector2( 10, 8), Vector2(50, 18), "��", m_pBtnFont);
	m_BtnWindowSize[WindowSize::MEDIUM].Initialize(Vector2( 70, 8), Vector2(50, 18), "��", m_pBtnFont);
	m_BtnWindowSize[WindowSize::SMALL ].Initialize(Vector2(130, 8), Vector2(50, 18), "��", m_pBtnFont);

	// �őO�ʂɂ���{�^���̏������B
	m_BtnAppForward.Initialize(Vector2(210, 8), Vector2(50, 18), "�őO��", m_pBtnFont);
	m_bForward = false;

	// �^�C�g���֍s���{�^���̏������B
	m_BtnGoTitle.Initialize(Vector2(290, 8), Vector2(70, 18), "�^�C�g����", m_pBtnFont);
}

CGame::~CGame(void)
{
	// �������
}

void CGame::Update(void)
{
	// �^�C�g���֍s���{�^���������ꂽ��^�C�g���֍s�����ˁB
	if (m_BtnGoTitle.IsClickL())
	{
		ChangeScene(SceneName::Title);
	}

	for (int i = 0; i < WindowSize::WINDOWSIZE_CONT; i++)
	{
		// �����ꂽ�{�^���ɂ���ăE�B���h�E�̃T�C�Y��ύX����B
		if (m_BtnWindowSize[i].IsClickL())
		{
			g_pGraphics->SetScreenSize(WindowSize[i].first, WindowSize[i].second);

			// �ύX���ꂽ�T�C�Y���L��,�X�V����B
			GetData().windowWidth  = WindowSize[i].first;
			GetData().windowHeight = WindowSize[i].second;
			break;
		}
	}

	// �E�B���h�E�őO�ʂ̏����B
	if (m_BtnAppForward.IsClickL())
	{
		m_bForward = !m_bForward;
		m_BtnAppForward.SetString(m_bForward ? "����" : "�őO��");
		CWindowUtillities::SetForeGround(m_bForward);
	}
}

void CGame::Render(void) const
{
	// �E�B���h�E�T�C�Y�ύX�{�^���̕`��B
	for (int i = 0; i < WindowSize::WINDOWSIZE_CONT; i++)
	{
		m_BtnWindowSize[i].Render();
	}

	// �őO�ʐݒ�{�^���̕`��B
	m_BtnAppForward.Render();

	// �^�C�g���֍s���{�^���̕`��B
	m_BtnGoTitle.Render();
}
