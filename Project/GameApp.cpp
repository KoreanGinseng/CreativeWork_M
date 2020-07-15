/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "MIDIInput.h"
#include    "picojson.h"


CDynamicArray<MusicData> g_MusicData;

// �N�����ɓǂݍ��݂��s���֐��B
bool StartLoad(void)
{
	// �ǂݍ��ݒ��ɐڑ�����Ă���Midi�f�o�C�X�����f�o�b�N�ɕ\������B
	MOF_PRINTLOG("midi device count : %d\n", g_MIDIInput.GetDeviceCount());

	// JSON�f�[�^�̓ǂݍ��݁B
	std::ifstream ifs("music_list.json", std::ios::in);
	if (ifs.fail())
	{
		MOF_PRINTLOG("failed to read music_list.json\n");
		return false;
	}
	
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	ifs.close();

	// JSON�f�[�^����͂���B
	picojson::value v;
	const std::string err = picojson::parse(v, json);
	if (err.empty() == false)
	{
		MOF_PRINTLOG(err.c_str());
		return false;
	}

	picojson::object& obj = v.get<picojson::object>();
	// map��range-based-for�ł܂킵�Ă���B
	for (const auto& p : obj)
	{
		// �z������擾����B
		picojson::array obj2 = p.second.get<picojson::array>();
		for (const auto& q : obj2)
		{
			// �z����̃I�u�W�F�N�g�f�[�^���擾����B
			picojson::object obj3 = q.get<picojson::object>();
			MusicData md;
			for (const auto s : obj3)
			{
				if (s.first == "title")
				{
					md.title = s.second.get<std::string>();
				}
				if (s.first == "file_name")
				{
					md.fileName = s.second.get<std::string>();
				}
				if (s.first == "fall_speed")
				{
					md.fallSpd = s.second.get<double>();
				}
				if (s.first == "trucks")
				{
					picojson::array truckArray = s.second.get<picojson::array>();
					for (int tc = 0; tc < truckArray.size(); tc++)
					{
						md.trucks.push_back(truckArray[tc].get<double>());
					}
				}
			}
			g_MusicData.Add(md);
			g_NoteArray.Add();
		}
	}

	// json����ȃf�[�^�̓ǂݍ��݂��s���B
	for (int i = 0; i < g_MusicData.GetArrayCount(); i++)
	{
		if (!LoadStanderdMidiFile(g_MusicData[i].fileName.c_str(), g_NoteArray[i]))
		{
			return false;
		}
	}

	return true;
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	// �f�ރt�H���_�̎w��B
	CUtilities::SetCurrentDirectory("Resource");

	// �e�V�[���̒ǉ��ƁA�t�F�[�h�F�̐ݒ�B
	m_SceneManager
		.Add<CTitle>      (SceneName::Title)
		.Add<CSelectScene>(SceneName::Select)
		.Add<CGame>       (SceneName::Game)
		.Add<CResult>     (SceneName::Result)
		.Add<CLoad>       (SceneName::Load)
		.Add<CSetting>    (SceneName::Setting)
		.SetFadeColor(MOF_COLOR_WHITE);

	// �ǂݍ��݊֐��̓o�^�B
	CLoad::SetLoadFunc("StartLoad", StartLoad);

	// �N�����Ɏ��s����ǂݍ��݊֐��̎w��B
	CLoad::SetLoadFuncName("StartLoad");

	// �ǂݍ��݂��I��������Ƃ̎��̃V�[���B
	CLoad::SetNextScene(SceneName::Title);

	// �J�n�V�[���̐ݒ�B
	m_SceneManager.Initialize(SceneName::Load);

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();
	g_MIDIInput.RefreshKey();

	// �e�V�[���̍X�V�B
	if (!m_SceneManager.Update())
	{
		// �V�[���X�V���ɃG���[�����������ꍇ�̏����B
		PostQuitMessage(1);
	}

	// �L�[�����ꂽ�Ƃ��ɉ��o����B
	for (int i = 0; i < 256; i++)
	{
		if (g_MIDIInput.IsKeyPush(i))
		{
			g_Midiout.Play(g_MIDIInput.GetVelocity(i), i, m_SceneManager.GetData()->channel);
		}

		if (g_MIDIInput.IsKeyPull(i))
		{
			g_Midiout.Stop(i, m_SceneManager.GetData()->channel);
		}
	}

	// DEBUG : P�L�[��A4�̉���炷
	if (g_pInput->IsKeyPush(MOFKEY_P))
	{
		g_Midiout.Play(0.8f, PianoKey::A4, m_SceneManager.GetData()->channel);
	}
	if (g_pInput->IsKeyPull(MOFKEY_P))
	{
		g_Midiout.Stop(PianoKey::A4, m_SceneManager.GetData()->channel);
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.18f, 0.24f, 0.0f, 1.0f, 0);

	// �e�V�[���̕`��B
	if (!m_SceneManager.Render())
	{
		// �V�[���`�撆�ɃG���[�����������ꍇ�̏����B
		PostQuitMessage(2);
	}

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {

	// �e�A�Z�b�g�̉���B
	CTextureAsset::Release();
	CMeshAsset::Release();
	CSoundAsset::Release();

	return TRUE;
}