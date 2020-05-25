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

// �E�B���h�E�T�C�Y
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