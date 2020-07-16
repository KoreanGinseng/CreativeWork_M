#include "SelectScene.h"
#include "Load.h"

// ���t�Ȃ̃��X�g�ԍ�
int      g_MusicSelect = 0;


CSelectScene::CSelectScene(const CSelectScene::InitData & init) :
	MyApp::CScene::IScene(init)
{
	g_MusicSelect   = 0;

	float x = SceneWidth  - 180;
	float y = SceneHeight - 110;
	m_PlayBtn       = CButton(CRectangle(              x,               y,         x + 150,           y + 80));
	m_PlayAutoBtn   = CButton(CRectangle(        x - 250,               y,         x -  30,           y + 80));
	m_SelectBtnUp   = CButton(CRectangle(            530,              30,             580,               80));
	m_SelectBtnDown = CButton(CRectangle(            530,SceneHeight - 80,             580, SceneHeight - 30));
	m_SetBtn        = CButton(CRectangle(SceneWidth - 80,              30, SceneWidth - 30,               80));
	
	m_SelectBtnUp  .SetTexture(TextureAsset("ArrowUp"));
	m_SelectBtnDown.SetTexture(TextureAsset("ArrowDown"));
	m_SetBtn       .SetTexture(TextureAsset("Gear"));
	m_PlayBtn      .SetTexture(TextureAsset("Play"));
	m_PlayAutoBtn  .SetTexture(TextureAsset("PlayAuto"));

	m_TruckIndex    = 0;

	m_pSelect1Texture = TextureAsset("Select_1");
	m_pSelect2Texture = TextureAsset("Select_2");

	m_pNameFont = FontAsset("MusicName");
	m_pInfoFont = FontAsset("Info");
	m_pNameFont->SetSize(50);
	m_pInfoFont->SetSize(36);

	m_ArrowMotion << CEaseMotion<float>(0.0f, 5.0f, Ease::InOut, EaseType::Sine, 0.5f);
	m_ArrowMotion << CEaseMotion<float>(5.0f, 0.0f, Ease::InOut, EaseType::Sine, 0.5f);

	m_ArrowMotion.Start();

	m_Scale    = 1.0f;
	m_Rotate   = 0.0f;
	m_pTitleTexture = TextureAsset("Title");

	m_ScaleMotion << CEaseMotion<float>(1.0f, 1.2f, Ease::InOut, EaseType::Sine, 0.5f);
	m_ScaleMotion << CEaseMotion<float>(1.2f, 1.0f, Ease::InOut, EaseType::Sine, 0.5f);

	m_ScaleMotion.Start();
}

CSelectScene::~CSelectScene(void)
{
}

void CSelectScene::Update(void)
{
	int truckNo  = g_MusicData[g_MusicSelect].trucks[m_TruckIndex];
	int truckCnt = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray().GetArrayCount();
	// �I�������Ȃ�GO!
	if (
		// �{�^���n�����ꂽ���̔���B
		(
		    g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		    m_PlayAutoBtn.IsPull()             ||
		    m_PlayBtn.IsPull()
		)   
		&&
		// �f�[�^�����邩�ǂ����̔���B
		(
			truckNo < truckCnt                 &&
			g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[truckNo].GetArrayCount() > 0
		) 
	   )
	{
		GetData().trackNo = g_MusicData[g_MusicSelect].trucks[m_TruckIndex];
		GetData().channel = GetData().trackNo;
		GetData().autoParam = m_PlayAutoBtn.IsPull() ? Auto::All : Auto::Semi;
		ChangeScene(SceneName::Game);
	}

	// �ݒ��ʂցB
	if (m_SetBtn.IsPull())
	{
		ChangeScene(SceneName::Setting);
	}

	// �w�i�̍X�V�B
	m_ScaleMotion.Update();

	m_Scale = m_ScaleMotion.GetValue();

	// ���[�v������B
	if (m_ScaleMotion.IsEnd())
	{
		m_ScaleMotion.Reset();
		m_ScaleMotion.Start();
	}

	m_Rotate += 0.01f;

	m_Rotate = MOF_NORMALIZE_RADIANANGLE(m_Rotate);

	// ���̂ӂ�ӂ킷�郂�[�V�����̍X�V�B
	m_ArrowMotion.Update();

	m_SelectBtnUp  .GetRect().SetPosition(Vector2(530,               30) + Vector2(0, -m_ArrowMotion.GetValue()));
	m_SelectBtnDown.GetRect().SetPosition(Vector2(530, SceneHeight - 80) + Vector2(0,  m_ArrowMotion.GetValue()));

	// �A�j���[�V���������[�v������B
	if (m_ArrowMotion.IsEnd())
	{
		m_ArrowMotion.Reset();
		m_ArrowMotion.Start();
	}

	// �}�E�X�z�C�[���ł̃J�[�\���ړ��B
	int wheelMove = g_pInput->GetMouseWheelMove() * 0.01f;
	if (wheelMove)
	{
		int max  = g_MusicData.GetArrayCount();

		g_MusicSelect += wheelMove;

		// ���[�����鏈���B
		if (g_MusicSelect < 0)
		{
			g_MusicSelect += max;
		}
		else if (g_MusicSelect >= max)
		{
			g_MusicSelect -= max;
		}
	}

	// �㉺���L�[�ł̃J�[�\���ړ��B
	if (g_pInput->IsKeyPush(MOFKEY_UP) ||
		m_SelectBtnUp.IsPull())
	{
		g_MusicSelect--;
		if (g_MusicSelect < 0)
		{
			g_MusicSelect = g_MusicData.GetArrayCount() - 1;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN) ||
		m_SelectBtnDown.IsPull())
	{
		g_MusicSelect++;
		if (g_MusicSelect > g_MusicData.GetArrayCount() - 1)
		{
			g_MusicSelect = 0;
		}
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

	// �Z���N�g�����Ȑ��𒴂��Ȃ��悤�ɂ���B
	g_MusicSelect = MOF_CLIPING(g_MusicSelect, 0, g_MusicData.GetArrayCount() - 1);
	m_TruckIndex  = MOF_CLIPING(m_TruckIndex , 0, g_MusicData[g_MusicSelect].trucks.size() - 1);
}

void CSelectScene::Render(void) const
{
	m_pTitleTexture->RenderScaleRotate(SceneWidth * 0.5f, SceneHeight * 0.5f, m_Scale, m_Rotate, MOF_ALPHA_WHITE(128), TEXALIGN_CENTERCENTER);

	for (int i = -2; i <= 2; i++)
	{
		int w = 400;
		int h = 100;
		int x = 100 + MOF_ABS(i) * -30;
		int y = (SceneHeight - h) * 0.5f + (i * (h + 50));
		CRectangle rect(x, y, x + w, y + h);

		// �w�i�e�N�X�`���̕`��B
		if (i == 0)
		{
			m_pSelect1Texture->Render(rect);
		}
		else
		{
			m_pSelect2Texture->Render(rect);
		}

		// �e�L�X�g�`��B
		CRectangle outStrRect;
		int musicNo = LoopMusicNo(g_MusicSelect + i);
		m_pNameFont->CalculateStringRect(0, 0, g_MusicData[musicNo].title.c_str(), outStrRect);
		m_pNameFont->RenderString(
			x + (rect.GetWidth()  - outStrRect.GetWidth() ) * 0.5f,
			y + (rect.GetHeight() - outStrRect.GetHeight()) * 0.5f,
			g_MusicData[musicNo].title.c_str()
		);
	}
	
	// �e�{�^���̕`��B
	m_SelectBtnDown.Render();
	m_SelectBtnUp.Render();
	m_PlayBtn.Render();
	m_PlayAutoBtn.Render();
	m_SetBtn.Render();

	// ���̕`��B
	Vector2    infoPos(SceneWidth * 0.5f + 30, 110);
	CRectangle infoRect(infoPos, Vector2(SceneWidth - 30, SceneHeight - 140));
	CGraphicsUtilities::RenderFillRect(infoRect, MOF_ALPHA_BLUE(64));

	int offsetX = infoRect.Left + 30;

	CRectangle titleNameRect;
	m_pInfoFont->CalculateStringRect(0, 0, g_MusicData[g_MusicSelect].title.c_str(), titleNameRect);
	m_pInfoFont->RenderString(infoPos.x + (infoRect.GetWidth() - titleNameRect.GetWidth()) * 0.5f, infoPos.y + 30, g_MusicData[g_MusicSelect].title.c_str());
	CGraphicsUtilities::RenderLine(infoRect.Left + 30, infoPos.y + 32 + titleNameRect.GetHeight(), infoRect.Right - 30, infoPos.y + 32 + titleNameRect.GetHeight(), MOF_COLOR_WHITE);

	int truckNo  = g_MusicData[g_MusicSelect].trucks[m_TruckIndex];
	int truckCnt = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray().GetArrayCount();
	m_pInfoFont->RenderFormatString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 3, "TrackNo   : %02u", truckNo);
	
	// �g���b�N�����݂��邩�m�F����B
	if (truckNo >= truckCnt)
	{
		m_pInfoFont->RenderString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 2, "���̃g���b�N�͑��݂��܂���B");
	}
	else
	{
		int combCnt  = g_NoteArray[g_MusicSelect].GetSMFData().GetNoteArray()[truckNo].GetArrayCount();
		m_pInfoFont->RenderFormatString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 2, "TrackName : %s"  , g_NoteArray[g_MusicSelect].GetSMFData().GetTrackNameArray()[truckNo].GetString());
		m_pInfoFont->RenderFormatString(offsetX, infoRect.Bottom - (30 + titleNameRect.GetHeight()) * 1, "MaxCombo  : %d"  , combCnt / 2);
	}
}

int CSelectScene::LoopMusicNo(const int& offset) const
{
	int no = offset;

	int size = g_MusicData.GetArrayCount();
	
	if (size == 1)
	{
		return 0;
	}
	else if (no > size - 1)
	{
		return LoopMusicNo(no - size);
	}
	else if (no < 0)
	{
		return LoopMusicNo(size + no);
	}

	return no;
}
