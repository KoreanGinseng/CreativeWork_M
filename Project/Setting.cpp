#include "Setting.h"
#include "Game.h"

CSetting::CSetting(const InitData & init) :
	MyApp::CScene::IScene(init)
{
	m_SelectLeft_1_1  = CButton(CRectangle(ArrowOffsetX + ArrowSize * 1 + 15 * 1, ArrowOffsetY + ArrowSize * 0 + 15 * 0, ArrowOffsetX + ArrowSize * 2 + 15 * 1, ArrowOffsetY + ArrowSize + ArrowSize * 0 + 15 * 0));
	m_SelectLeft_1_2  = CButton(CRectangle(ArrowOffsetX + ArrowSize * 0 + 15 * 0, ArrowOffsetY + ArrowSize * 0 + 15 * 0, ArrowOffsetX + ArrowSize * 1 + 15 * 0, ArrowOffsetY + ArrowSize + ArrowSize * 0 + 15 * 0));
	m_SelectRight_1_1 = CButton(CRectangle(ArrowOffsetX + ArrowSize * 4 + 15 * 4, ArrowOffsetY + ArrowSize * 0 + 15 * 0, ArrowOffsetX + ArrowSize * 5 + 15 * 4, ArrowOffsetY + ArrowSize + ArrowSize * 0 + 15 * 0));
	m_SelectRight_1_2 = CButton(CRectangle(ArrowOffsetX + ArrowSize * 5 + 15 * 5, ArrowOffsetY + ArrowSize * 0 + 15 * 0, ArrowOffsetX + ArrowSize * 6 + 15 * 5, ArrowOffsetY + ArrowSize + ArrowSize * 0 + 15 * 0));

	m_SelectLeft_2_1  = CButton(CRectangle(ArrowOffsetX + ArrowSize * 1 + 15 * 1, ArrowOffsetY + ArrowSize * 1 + 15 * 1, ArrowOffsetX + ArrowSize * 2 + 15 * 1, ArrowOffsetY + ArrowSize + ArrowSize * 1 + 15 * 1));
	m_SelectLeft_2_2  = CButton(CRectangle(ArrowOffsetX + ArrowSize * 0 + 15 * 0, ArrowOffsetY + ArrowSize * 1 + 15 * 1, ArrowOffsetX + ArrowSize * 1 + 15 * 0, ArrowOffsetY + ArrowSize + ArrowSize * 1 + 15 * 1));
	m_SelectRight_2_1 = CButton(CRectangle(ArrowOffsetX + ArrowSize * 4 + 15 * 4, ArrowOffsetY + ArrowSize * 1 + 15 * 1, ArrowOffsetX + ArrowSize * 5 + 15 * 4, ArrowOffsetY + ArrowSize + ArrowSize * 1 + 15 * 1));
	m_SelectRight_2_2 = CButton(CRectangle(ArrowOffsetX + ArrowSize * 5 + 15 * 5, ArrowOffsetY + ArrowSize * 1 + 15 * 1, ArrowOffsetX + ArrowSize * 6 + 15 * 5, ArrowOffsetY + ArrowSize + ArrowSize * 1 + 15 * 1));

	m_Back            = CButton(CRectangle(1150,  30, 1250,  80));

	m_SelectLeft_1_1 .SetTexture(TextureAsset("ArrowLeft_1" ));
	m_SelectLeft_1_2 .SetTexture(TextureAsset("ArrowLeft_2" ));
	m_SelectRight_1_1.SetTexture(TextureAsset("ArrowRight_1"));
	m_SelectRight_1_2.SetTexture(TextureAsset("ArrowRight_2"));

	m_SelectLeft_2_1 .SetTexture(TextureAsset("ArrowLeft_1" ));
	m_SelectLeft_2_2 .SetTexture(TextureAsset("ArrowLeft_2" ));
	m_SelectRight_2_1.SetTexture(TextureAsset("ArrowRight_1"));
	m_SelectRight_2_2.SetTexture(TextureAsset("ArrowRight_2"));
	
	m_Back           .SetTexture(TextureAsset("Back_2"      ));

	m_pFont          = FontAsset("Info");
	m_pFont->SetSize(60);
}

CSetting::~CSetting(void)
{
	GetKeyLength() = GetData().keyLength;
	GetKeyOffset() = GetData().offsetKey;
}

void CSetting::Update(void)
{
	m_BackRender.Update();

	// 選択画面に戻る処理。
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) ||
		m_Back.IsPull())
	{
		SoundAsset("SE_Enter")->Play();
		ChangeScene(SceneName::Select);
	}

	if (m_SelectLeft_1_1.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().keyLength =
			(GetData().keyLength == KeyLength::_25) || (GetData().keyLength == KeyLength::_37)
			? KeyLength::_25
			: GetData().keyLength == KeyLength::_49
			? KeyLength::_37
			: GetData().keyLength == KeyLength::_61
			? KeyLength::_49
			: KeyLength::_61;
	}
	if (m_SelectLeft_1_2.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().keyLength = KeyLength::_25;
	}
	if (m_SelectRight_1_1.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().keyLength =
			(GetData().keyLength == KeyLength::_88) || (GetData().keyLength == KeyLength::_61)
			? KeyLength::_88
			: GetData().keyLength == KeyLength::_49
			? KeyLength::_61
			: GetData().keyLength == KeyLength::_37
			? KeyLength::_49
			: KeyLength::_37;
	}
	if (m_SelectRight_1_2.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().keyLength = KeyLength::_88;
	}

	if (m_SelectLeft_2_1.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().offsetKey = (PianoKey)(GetData().offsetKey - 1);
	}
	if (m_SelectLeft_2_2.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().offsetKey = (PianoKey)(GetData().offsetKey - 12);
	}

	if (m_SelectRight_2_1.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().offsetKey = (PianoKey)(GetData().offsetKey + 1);
	}
	if (m_SelectRight_2_2.IsPull())
	{
		SoundAsset("SE_Select")->Play();
		GetData().offsetKey = (PianoKey)(GetData().offsetKey + 12);
	}
}

void CSetting::Render(void) const
{
	m_BackRender.Render();

	CBackRender::RenderBackBoard(Vector2(SceneWidth * 0.5f, (SceneHeight - (SceneHeight - CheckLineY)) * 0.5f), Vector2(6.5f, 3.5f), MOF_ALPHA_WHITE(64));

	m_pFont->RenderString(200, m_SelectLeft_1_1.GetRect().Top, "KeyLength");
	m_pFont->RenderFormatString(m_SelectLeft_1_1.GetRect().Right + 30, m_SelectLeft_1_1.GetRect().Top, "%2d", GetData().keyLength);
	m_pFont->RenderString(200, m_SelectLeft_2_1.GetRect().Top, "OffsetKey");
	m_pFont->RenderFormatString(m_SelectLeft_2_1.GetRect().Right + 30, m_SelectLeft_2_1.GetRect().Top, "%03u", GetData().offsetKey);

	m_SelectLeft_1_1 .Render();
	m_SelectLeft_1_2 .Render();
	m_SelectRight_1_1.Render();
	m_SelectRight_1_2.Render();

	m_SelectLeft_2_1 .Render();
	m_SelectLeft_2_2 .Render();
	m_SelectRight_2_1.Render();
	m_SelectRight_2_2.Render();

	m_Back.Render();

	// 白鍵の描画。
	CGame::RenderWhiteKey(GetData().offsetKey, GetData().keyLength);

	// 黒鍵の描画。
	CGame::RenderBlackKey();

	float offsetx = 0;
	if (CMIDIInput::IsBlackKey(GetData().offsetKey))
	{
		// 黒鍵の場合のずらす処理。
		if (GetData().offsetKey == PianoKey::A0_S)
		{
			offsetx = PianoWhiteKeyWidth - PianoBlackKeyWidth * 0.5f;
		}
		else
		{
			// 黒鍵の数だけカウントする。
			int x = -1;
			for (int i = PianoKey::A0; i < GetData().offsetKey; i++)
			{
				if (CMIDIInput::IsWhiteKey(i))
				{
					continue;
				}
				x++;
			}
			// とりあえずずらす。
			offsetx = PianoWhiteKeyWidth * 3 - PianoBlackKeyWidth * 0.5f;
			for (int i = 1; i <= x; i++)
			{
				offsetx += PianoWhiteKeyWidth;
				if ((i % 5) != 0 && (((i - (i / 5) * 5) + 1) % 3 == 0))
				{
					offsetx += PianoWhiteKeyWidth;
				}
				if ((i % 5) == 0 && (i != 0))
				{
					offsetx += PianoWhiteKeyWidth;
				}
			}
		}
		offsetx += PianoBlackKeyWidth / 2;
	}
	else
	{
		int x = 0;
		for (int i = PianoKey::A0; i < GetData().offsetKey; i++)
		{
			if (CMIDIInput::IsBlackKey(i))
			{
				continue;
			}
			x++;
		}
		offsetx  = x * PianoWhiteKeyWidth;
		offsetx += PianoWhiteKeyWidth / 2;
	}
	float offsety = CMIDIInput::IsBlackKey(GetData().offsetKey) ? 670 : 710;
	CCircle redc(Vector2(PianoRollOffsetX + offsetx, offsety), 5);
	CGraphicsUtilities::RenderFillCircle(redc, MOF_COLOR_RED);
}

void CSetting::Save(void)
{
	FILE* fp;
	fp = fopen("Config.config", "wt");

	if (fp == NULL)
	{
		return;
	}

	fprintf(fp, "%d,%d,", GetKeyLength(), GetKeyOffset());

	fclose(fp);
}

bool CSetting::Load(void)
{
	FILE* fp;
	fp = fopen("Config.config", "rt");

	if (fp == NULL)
	{
		return false;
	}
	int length = 0, key = 0;
	fscanf(fp, "%d,%d,", &length, &key);

	GetKeyLength() = static_cast<KeyLength>(length);
	GetKeyOffset() = static_cast<PianoKey>(key);

	fclose(fp);

	return true;
}

KeyLength & CSetting::GetKeyLength(void)
{
	static KeyLength length;
	return length;
}

PianoKey & CSetting::GetKeyOffset(void)
{
	static PianoKey key;
	return key;
}
