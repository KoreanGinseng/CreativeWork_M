#include "Load.h"
#include "Setting.h"

CLoad::CLoad(const CLoad::InitData & init) :
	CLoadBase(init)
{
	// ����������
	m_pFont = FontAsset("Info");
	m_pFont->SetSize(60);

	m_AlphaMotion << CEaseMotion<int>(255,   0, Ease::In, EaseType::None, 0.5f);
	m_AlphaMotion << CEaseMotion<int>(  0, 255, Ease::In, EaseType::None, 0.5f);

	m_AlphaMotion.Start();
}

CLoad::~CLoad(void)
{
	// �������
	GetData().keyLength = CSetting::GetKeyLength();
	GetData().offsetKey = CSetting::GetKeyOffset();
}

void CLoad::Update(void)
{
	// �ǂݍ��ݒ��̍X�V�����B
	m_BackRender.Update();

	if (m_AlphaMotion.IsEnd())
	{
		m_AlphaMotion.Reset();
		m_AlphaMotion.Start();
	}

	m_AlphaMotion.Update();

	// �X���b�h�ł̓ǂݍ��ݐ���B
	CLoadBase::Update();
}

void CLoad::Render(void) const
{
	g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0);

	CRectangle outRect;
	m_pFont->CalculateStringRect(0, 0, "Loading", outRect);
	m_pFont->RenderString((SceneWidth - outRect.GetWidth()) * 0.5f, SceneHeight * 0.5f + 100, MOF_ALPHA_WHITE(m_AlphaMotion.GetValue()), "Loading");

	// Loading���̃A�j���[�V�����`��B
	m_BackRender.Render();
}
