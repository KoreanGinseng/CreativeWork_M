#include "Setting.h"

CSetting::CSetting(const InitData & init) :
	MyApp::CScene::IScene(init)
{
	m_Select = 1;
}

CSetting::~CSetting(void)
{
}

void CSetting::Update(void)
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		ChangeScene(SceneName::Select);
	}

	// マウスホイールでのカーソル移動。
	int wheelMove = g_pInput->GetMouseWheelMove() * 0.01f;
	if (wheelMove)
	{
		g_MusicSelect -= wheelMove;
	}

	// 上下矢印キーでのカーソル移動。
	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		m_Select--;
	}
	if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		m_Select++;
	}

	// セレクト数が超えないようにする。
	m_Select = MOF_CLIPING(m_Select, 1, 4);

	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		switch (m_Select)
		{
		case 1:
			GetData().fallSpeed -= 0.1f;
			GetData().fallSpeed = MOF_MAX(1.0f, GetData().fallSpeed);
			break;
		case 2:
			GetData().keyLength =
				(GetData().keyLength == KeyLength::_25) || (GetData().keyLength == KeyLength::_37)
				? KeyLength::_25
				: GetData().keyLength == KeyLength::_49
				? KeyLength::_37
				: GetData().keyLength == KeyLength::_61
				? KeyLength::_49
				: KeyLength::_61;
			break;
		case 3:
			GetData().offsetKey = (PianoKey)(GetData().offsetKey - 1);
			break;
		case 4:
			GetData().autoParam = (Auto)((int)GetData().autoParam - 1);
			GetData().autoParam = (Auto)MOF_MAX(0, (int)GetData().autoParam);
			break;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		switch (m_Select)
		{
		case 1:
			GetData().fallSpeed += 0.1f;
			GetData().fallSpeed = MOF_MIN(10.0f, GetData().fallSpeed);
			break;
		case 2:
			GetData().keyLength =
				(GetData().keyLength == KeyLength::_88) || (GetData().keyLength == KeyLength::_61)
				? KeyLength::_88
				: GetData().keyLength == KeyLength::_49
				? KeyLength::_61
				: GetData().keyLength == KeyLength::_37
				? KeyLength::_49
				: KeyLength::_37;
			break;
		case 3:
			GetData().offsetKey = (PianoKey)(GetData().offsetKey + 1);
			break;
		case 4:
			GetData().autoParam = (Auto)((int)GetData().autoParam + 1);
			GetData().autoParam = (Auto)MOF_MIN(2, (int)GetData().autoParam);
			break;
		}
	}
}

void CSetting::Render(void) const
{
	CGraphicsUtilities::RenderString(0, 0, "Setting");

	CGraphicsUtilities::RenderString(0,  30, "FallSpeed : %.1f", GetData().fallSpeed);
	CGraphicsUtilities::RenderString(0,  60, "KeyLength : %2d" , GetData().keyLength);
	CGraphicsUtilities::RenderString(0,  90, "OffsetKey : %03u", GetData().offsetKey);
	CGraphicsUtilities::RenderString(0, 120, "AutoParam : %s", GetData().autoParam == Auto::All ? "All" : GetData().autoParam == Auto::Semi ? "Semi" : "None");

	CGraphicsUtilities::RenderString(350, m_Select * 30, "←");
}
