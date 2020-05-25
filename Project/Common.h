#pragma once
#include "SceneManager.h"
#include "AssetBase.h"

using namespace sip;

// シーンのキー
enum class SceneName
{
	Title,

	Game,

	Load,

};

// 各シーン共通のデータ
struct GameData {

	int windowWidth;

	int windowHeight;

};

// ウィンドウサイズ
enum WindowSize {

	LARGE,

	MEDIUM,

	SMALL,

	WINDOWSIZE_CONT
};

constexpr std::pair<int, int> WindowSize[WINDOWSIZE_CONT] =
{
	{ 800, 600 },
	{ 400, 300 },
	{ 200, 150 },
};


using MyApp = CSceneManager<SceneName, GameData>;