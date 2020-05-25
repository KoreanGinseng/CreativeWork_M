#pragma once
#include "SceneManager.h"
#include "AssetBase.h"

using namespace sip;

// �V�[���̃L�[
enum class SceneName
{
	Title,

	Game,

	Load,

};

// �e�V�[�����ʂ̃f�[�^
struct GameData {

	int windowWidth;

	int windowHeight;

};


using MyApp = CSceneManager<SceneName, GameData>;