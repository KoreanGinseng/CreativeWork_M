/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "ImageResourceDefine.h"

namespace LoadFunc
{
	// �N�����ɓǂݍ��݂��s���֐��B
	bool StartLoad(void)
	{
		// �{�^���p�t�H���g�̍쐬�B
		if (!CFontAsset::Load("Button", "���S�V�b�N"))
		{
			return false;
		}

		// �摜�f�[�^�̓ǂݍ��݁B
		CUtilities::SetCurrentDirectory("img");
		for (auto& itr : ImageResource)
		{
			if (!CTextureAsset::Load(itr.first, itr.second))
			{
				return false;
			}
		}
		CUtilities::SetCurrentDirectory("../");

		return true;
	}
}

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	// �f�ރt�H���_�̎w��
	CUtilities::SetCurrentDirectory("Resource");

	// �e�V�[���̒ǉ��ƁA�t�F�[�h�F�̐ݒ�B
	m_SceneManager
		.Add<CTitle>(SceneName::Title)
		.Add<CGame>(SceneName::Game)
		.Add<CLoad>(SceneName::Load)
		.SetFadeColor(MOF_COLOR_WHITE);

	// �ǂݍ��݊֐��̓o�^�B
	CLoad::SetLoadFunc("StartLoad", LoadFunc::StartLoad);

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

	// �e�V�[���̍X�V�B
	if (!m_SceneManager.Update())
	{
		// �V�[���X�V���ɃG���[�����������ꍇ�̏����B
		PostQuitMessage(1);
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
	g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0);

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
	CFontAsset::Release();

	return TRUE;
}