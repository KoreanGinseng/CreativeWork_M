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

// ウィンドウサイズ
enum WINDOWSIZE {

	LARGE,

	MEDIUM,

	SMALL,

	WINDOWSIZE_CONT
};

// 各シーン共通のデータ
struct GameData {

	WINDOWSIZE    windowSize;

};

constexpr std::pair<int, int> WindowSize[WINDOWSIZE_CONT] =
{
	{ 800, 600 },
	{ 400, 300 },
	{ 200, 150 },
};


using MyApp = CSceneManager<SceneName, GameData>;