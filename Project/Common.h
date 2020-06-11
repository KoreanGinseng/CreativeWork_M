#pragma once
#include "SceneManager.h"
#include "AssetBase.h"
#include "Note.h"

using namespace sip;

// シーンのキー
enum class SceneName
{
	Title,

	Select,

	Game,

	Result,

	Load,

	Setting,

};

// 各シーン共通のデータ
struct GameData 
{
	float                     fallSpeed =           5.0f;
			                  
	KeyLength                 keyLength = KeyLength::_88;
			                  
	Auto                      autoParam =     Auto::Semi;
			                  
	PianoKey                  offsetKey =   PianoKey::A0;
			                  
	int                       trackNo   =              0;
};

// jsonData.
struct MusicData
{
	std::string title;
	std::string fileName;
	MofU8       instrument;
};

struct PlayResult
{
	MofU32      perfect  = 0;
	MofU32      great    = 0;
	MofU32      good     = 0;
	MofU32      bad      = 0;
	MofU32      miss     = 0;

	MofU32      combo    = 0;

	MofU32      maxCombo = 0;

	void Clear(void)
	{
		perfect  = 0;
		great    = 0;
		good     = 0;
		bad      = 0;
		miss     = 0;
		combo    = 0;
		maxCombo = 0;
	}
};


extern    CDynamicArray<CNoteArray>  g_NoteArray;
extern    CDynamicArray<MusicData>   g_MusicData;
extern    int                        g_MusicSelect;
extern    PlayResult                 g_PlayResult;

constexpr int  SceneWidth            =                                                     1280;

constexpr int  SceneHeight           =                                                      720;

constexpr int  WhiteKeyCount         =                                                       52;
										                      
constexpr int  PianoWhiteKeyWidth    =                               SceneWidth / WhiteKeyCount;

constexpr int  PianoWhiteKeyHeight   =                                                      100;

constexpr int  PianoBlackKeyWidth    =                                PianoWhiteKeyWidth * 0.5f;

constexpr int  PianoBlackKeyHeight   =                               PianoWhiteKeyHeight * 0.6f;

constexpr int  PianoRollOffsetX      = (SceneWidth - WhiteKeyCount * PianoWhiteKeyWidth) * 0.5f;
										                      
constexpr int  PianoRollOffsetY      =                                                      620;

constexpr int  CheckLineY            =                                    PianoRollOffsetY - 40;

using MyApp = CSceneManager<SceneName, GameData>;