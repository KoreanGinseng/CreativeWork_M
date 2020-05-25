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


using MyApp = CSceneManager<SceneName, GameData>;