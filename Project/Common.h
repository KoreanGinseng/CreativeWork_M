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

// �E�B���h�E�T�C�Y
enum WINDOWSIZE {

	LARGE,

	MEDIUM,

	SMALL,

	WINDOWSIZE_CONT
};

// �e�V�[�����ʂ̃f�[�^
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