/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include    "ImageResourceDefine.h"

namespace LoadFunc
{
	// 起動時に読み込みを行う関数。
	bool StartLoad(void)
	{
		// ボタン用フォントの作成。
		if (!CFontAsset::Load("Button", "游ゴシック"))
		{
			return false;
		}

		// 画像データの読み込み。
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
		@brief			アプリケーションの初期化
		@param			None

		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {

	// 素材フォルダの指定
	CUtilities::SetCurrentDirectory("Resource");

	// 各シーンの追加と、フェード色の設定。
	m_SceneManager
		.Add<CTitle>(SceneName::Title)
		.Add<CGame>(SceneName::Game)
		.Add<CLoad>(SceneName::Load)
		.SetFadeColor(MOF_COLOR_WHITE);

	// 読み込み関数の登録。
	CLoad::SetLoadFunc("StartLoad", LoadFunc::StartLoad);

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

	// 各シーンの更新。
	if (!m_SceneManager.Update())
	{
		// シーン更新中にエラーが発生した場合の処理。
		PostQuitMessage(1);
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
	g_pGraphics->ClearTarget(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0);

	// 各シーンの描画。
	if (!m_SceneManager.Render())
	{
		// シーン描画中にエラーが発生した場合の処理。
		PostQuitMessage(2);
	}

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
	CFontAsset::Release();

	return TRUE;
}