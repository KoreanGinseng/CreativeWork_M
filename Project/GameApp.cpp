/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "MIDIInput.h"
#include    "picojson.h"
#include    <fstream>


CDynamicArray<MusicData> g_MusicData;

// 起動時に読み込みを行う関数。
bool StartLoad(void)
{
	// 読み込み中に接続されているMidiデバイス数をデバックに表示する。
	MOF_PRINTLOG("midi device count : %d\n", g_MIDIInput.GetDeviceCount());

	// JSONデータの読み込み。
	std::ifstream ifs("music_list.json", std::ios::in);
	if (ifs.fail())
	{
		MOF_PRINTLOG("failed to read music_list.json\n");
		return false;
	}
	
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

	ifs.close();

	// JSONデータを解析する。
	picojson::value v;
	const std::string err = picojson::parse(v, json);
	if (err.empty() == false)
	{
		MOF_PRINTLOG(err.c_str());
		return false;
	}

	picojson::object& obj = v.get<picojson::object>();
	// mapをrange-based-forでまわしている。
	for (const auto& p : obj)
	{
		// 配列情報を取得する。
		picojson::array obj2 = p.second.get<picojson::array>();
		for (const auto& q : obj2)
		{
			// 配列内のオブジェクトデータを取得する。
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
				if (s.first == "instruments")
				{
					picojson::array instrumentArray = s.second.get<picojson::array>();
					for (int ic = 0; ic < instrumentArray.size(); ic++)
					{
						md.instruments.push_back(instrumentArray[ic].get<double>());
					}
				}
			}
			g_MusicData.Add(md);
			g_NoteArray.Add();
		}
	}

	// jsonから曲データの読み込みを行う。
	for (int i = 0; i < g_MusicData.GetArrayCount(); i++)
	{
		if (!LoadStanderdMidiFile(g_MusicData[i].fileName.c_str(), g_NoteArray[i]))
		{
			return false;
		}
	}

	// フォントを作成する。
	if (!CFontAsset::Load("MusicName", "ＭＳ ゴシック"))
	{
		return false;
	}
	if (!CFontAsset::Load("Result", "UD デジタル 教科書体 NK-B"))
	{
		return false;
	}

	// 各画像をアセットに登録する。
	for (auto& itr : TextureData)
	{
		if (!CTextureAsset::Load(itr.first, itr.second))
		{
			return false;
		}
	}

	// スコアの読み込み。
	if (!CScoreManager::Load("Score.score"))
	{
		return false;
	}
	// 設定の読み込み。
	if (!CSetting::Load())
	{
		return false;
	}

	// BGM、SEをアセットに登録する。
	if (!CSoundAsset::Load("BGM_Title", "BGM/やっぱりナゾナゾマン.mp3"))
	{
		return false;
	}
	if (!CSoundAsset::Load("BGM_Select", "BGM/ぽかぽか散歩道_2.mp3"))
	{
		return false;
	}
	if (!CSoundAsset::Load("BGM_Result", "BGM/気分UP.mp3"))
	{
		return false;
	}
	if (!CSoundAsset::Load("SE_Select", "SE/select.mp3"))
	{
		return false;
	}
	if (!CSoundAsset::Load("SE_Enter", "SE/enter.mp3"))
	{
		return false;
	}

	// SEの音量調節。
	SoundAsset("SE_Select")->SetVolume(0.05f);
	SoundAsset("SE_Enter") ->SetVolume(0.05f);

	//Sleep(10000);

	return true;
}

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	// 素材フォルダの指定。
	CUtilities::SetCurrentDirectory("Resource");

	// ロードシーン用に起動時に最小限だけを読み込みしておく。
	for (int i = TexName::Title; i <= TexName::Kirin_4; i++)
	{
		if (!CTextureAsset::Load(TextureData[i].first, TextureData[i].second))
		{
			return FALSE;
		}
	}
	if (!CFontAsset::Load("Info", "ＭＳ 明朝"))
	{
		return FALSE;
	}

	// 各シーンの追加と、フェード色の設定。
	m_SceneManager
		.Add<CTitle>      (SceneName::Title)
		.Add<CSelectScene>(SceneName::Select)
		.Add<CGame>       (SceneName::Game)
		.Add<CResult>     (SceneName::Result)
		.Add<CLoad>       (SceneName::Load)
		.Add<CSetting>    (SceneName::Setting)
		.SetFadeColor(MOF_COLOR_WHITE);

	// 読み込み関数の登録。
	CLoad::SetLoadFunc("StartLoad", StartLoad);

	// 起動時に実行する読み込み関数の指定。
	CLoad::SetLoadFuncName("StartLoad");

	// 読み込みが終わったあとの次のシーン。
	CLoad::SetNextScene(SceneName::Title);

	// 開始シーンの設定。
	m_SceneManager.Initialize(SceneName::Load);

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//キーの更新
	g_pInput->RefreshKey();
	g_MIDIInput.RefreshKey();

	// 各シーンの更新。
	if (!m_SceneManager.Update())
	{
		// シーン更新中にエラーが発生した場合の処理。
		PostQuitMessage(1);
	}

	// キー押されたときに音出すやつ。
	for (int i = 0; i < 256; i++)
	{
		if (g_MIDIInput.IsKeyPush(i))
		{
			g_MidiOutput.Play(g_MIDIInput.GetVelocity(i), i, m_SceneManager.GetData()->channel);
		}

		if (g_MIDIInput.IsKeyPull(i))
		{
			g_MidiOutput.Stop(i, m_SceneManager.GetData()->channel);
		}
	}

	// DEBUG : PキーでA4の音を鳴らす
	//if (g_pInput->IsKeyPush(MOFKEY_P))
	//{
	//	g_MidiOutput.Play(0.8f, PianoKey::A4, m_SceneManager.GetData()->channel);
	//}
	//if (g_pInput->IsKeyPull(MOFKEY_P))
	//{
	//	g_MidiOutput.Stop(PianoKey::A4, m_SceneManager.GetData()->channel);
	//}

	for (int i = 0; i < KeyboardPianoKey.size(); i++) 
	{
		auto pianoKey = i + (int)m_SceneManager.GetData()->offsetKey;
		if (g_pInput->IsKeyPush(KeyboardPianoKey[i]))
		{
			g_MidiOutput.Play(0.8f, pianoKey, m_SceneManager.GetData()->channel);
		}
		if (g_pInput->IsKeyPull(KeyboardPianoKey[i]))
		{
			g_MidiOutput.Stop(pianoKey, m_SceneManager.GetData()->channel);
		}
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f, 0.18f, 0.24f, 0.0f, 1.0f, 0);

	// 各シーンの描画。
	if (!m_SceneManager.Render())
	{
		// シーン描画中にエラーが発生した場合の処理。
		PostQuitMessage(2);
	}

	//Vector2 mp;
	//g_pInput->GetMousePos(mp);
	//CGraphicsUtilities::RenderString(0, 0, "%.f,%.f", mp.x, mp.y);

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void) {

	// 各アセットの解放。
	CTextureAsset::Release();
	CMeshAsset::Release();
	CSoundAsset::Release();

	CScoreManager::Save("Score.score");
	CSetting::Save();

	return TRUE;
}