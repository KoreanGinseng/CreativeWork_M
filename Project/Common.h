#pragma once
#include "SceneManager.h"
#include "AssetBase.h"
#include "Note.h"
#include "EaseMotionController.h"

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
	KeyLength                 keyLength = KeyLength::_88;
			                  
	Auto                      autoParam =     Auto::Semi;
			                  
	PianoKey                  offsetKey =   PianoKey::A0;
			                  
	int                       trackNo   =              0;

	MofU8                     channel   =           0x00;
};

// jsonData.
struct MusicData
{
	std::string        title;
	std::string        fileName;
	float              fallSpd;
	std::vector<MofU8> trucks;
	std::vector<MofU8> instruments;
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

	MofU32      score    = 0;

	void Clear(void)
	{
		perfect  = 0;
		great    = 0;
		good     = 0;
		bad      = 0;
		miss     = 0;
		combo    = 0;
		maxCombo = 0;
		score    = 0;
	}
};

// TextureData
enum TexName
{
	Title,
	Kirin_1,
	Kirin_2,
	Kirin_3,
	Kirin_4,
	Back_1,
	Back_2,
	Play,
	PlayAuto,
	Select_1,
	Select_2,
	Gear,
	ArrowUp,
	ArrowDown,
	ArrowLeft_1,
	ArrowLeft_2,
	ArrowRight_1,
	ArrowRight_2,
	TexNameCount,
};

constexpr std::pair<char*, char*> TextureData[] =
{
	std::pair<char*, char*>("Title"       , "img/Title.png"       ),
	std::pair<char*, char*>("Kirin_1"     , "img/Kirin_1.png"     ),
	std::pair<char*, char*>("Kirin_2"     , "img/Kirin_2.png"     ),
	std::pair<char*, char*>("Kirin_3"     , "img/Kirin_3.png"     ),
	std::pair<char*, char*>("Kirin_4"     , "img/Kirin_4.png"     ),
	std::pair<char*, char*>("Back_1"      , "img/Back_1.png"      ),
	std::pair<char*, char*>("Back_2"      , "img/Back_2.png"      ),
	std::pair<char*, char*>("Play"        , "img/Play.png"        ),
	std::pair<char*, char*>("PlayAuto"    , "img/PlayAuto.png"    ),
	std::pair<char*, char*>("Select_1"    , "img/Select_1.png"    ),
	std::pair<char*, char*>("Select_2"    , "img/Select_2.png"    ),
	std::pair<char*, char*>("Gear"        , "img/Gear.png"        ),
	std::pair<char*, char*>("ArrowUp"     , "img/ArrowUp.png"     ),
	std::pair<char*, char*>("ArrowDown"   , "img/ArrowDown.png"   ),
	std::pair<char*, char*>("ArrowLeft_1" , "img/ArrowLeft_1.png" ),
	std::pair<char*, char*>("ArrowLeft_2" , "img/ArrowLeft_2.png" ),
	std::pair<char*, char*>("ArrowRight_1", "img/ArrowRight_1.png"),
	std::pair<char*, char*>("ArrowRight_2", "img/ArrowRight_2.png"),
};


extern    CDynamicArray<CNoteArray>  g_NoteArray;
extern    CDynamicArray<MusicData>   g_MusicData;
extern    int                        g_MusicSelect;
extern    PlayResult                 g_PlayResult;

constexpr int    SceneWidth            =                                                     1280;
			     
constexpr int    SceneHeight           =                                                      720;
			     
constexpr int    WhiteKeyCount         =                                                       52;
				  						                      
constexpr int    PianoWhiteKeyWidth    =                               SceneWidth / WhiteKeyCount;
			     
constexpr int    PianoWhiteKeyHeight   =                                                      100;
			     
constexpr int    PianoBlackKeyWidth    =                                PianoWhiteKeyWidth * 0.5f;
			     
constexpr int    PianoBlackKeyHeight   =                               PianoWhiteKeyHeight * 0.6f;
			     
constexpr int    PianoRollOffsetX      = (SceneWidth - WhiteKeyCount * PianoWhiteKeyWidth) * 0.5f;
				  						                      
constexpr int    PianoRollOffsetY      =                                                      620;
			     
constexpr int    CheckLineY            =                                    PianoRollOffsetY - 40;

constexpr double Version               =                                                      0.1;

using MyApp = CSceneManager<SceneName, GameData>;