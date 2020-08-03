#pragma once
#include "Mof.h"


enum PianoKey : MofU8
{
	C           = 0x00,
	C_S         = 0x01,
	D_F         = C_S,
	D           = 0x02,
	D_S         = 0x03,
	E_F         = D_S,
    E           = 0x04,
	F           = 0x05,
	F_S         = 0x06,
	G_F         = F_S,
	G           = 0x07,
	G_S         = 0x08,
	A_F         = G_S,
	A           = 0x09,
	A_S         = 0x0A,
	B_F         = A_S,
	B           = 0x0B,

	C0          = 0x0C,
	C0_S        = 0x0D,
	D0_F        = C0_S,
	D0          = 0x0E,
	D0_S        = 0x0F,
	E0_F        = D0_S,
    E0          = 0x10,
	F0          = 0x11,
	F0_S        = 0x12,
	G0_F        = F0_S,
	G0          = 0x13,
	G0_S        = 0x14,
	A0_F        = G0_S,
	A0          = 0x15,
	A0_S        = 0x16,
	B0_F        = A0_S,
	B0          = 0x17,

	C1          = 0x18,
	C1_S        = 0x19,
	D1_F        = C1_S,
	D1          = 0x1A,
	D1_S        = 0x1B,
	E1_F        = D1_S,
    E1          = 0x1C,
	F1          = 0x1D,
	F1_S        = 0x1E,
	G1_F        = F1_S,
	G1          = 0x1F,
	G1_S        = 0x20,
	A1_F        = G1_S,
	A1          = 0x21,
	A1_S        = 0x22,
	B1_F        = A1_S,
	B1          = 0x23,
		
	C2          = 0x24,
	C2_S        = 0x25,
	D2_F        = C2_S,
	D2          = 0x26,
	D2_S        = 0x27,
	E2_F        = D2_S,
    E2          = 0x28,
	F2          = 0x29,
	F2_S        = 0x2A,
	G2_F        = F2_S,
	G2          = 0x2B,
	G2_S        = 0x2C,
	A2_F        = G2_S,
	A2          = 0x2D,
	A2_S        = 0x2E,
	B2_F        = A2_S,
	B2          = 0x2F,
		
	C3          = 0x30,
	C3_S        = 0x31,
	D3_F        = C3_S,
	D3          = 0x32,
	D3_S        = 0x33,
	E3_F        = D3_S,
	E3          = 0x34,
	F3          = 0x35,
	F3_S        = 0x36,
	G3_F        = F3_S,
	G3          = 0x37,
	G3_S        = 0x38,
	A3_F        = G3_S,
	A3          = 0x39,
	A3_S        = 0x3A,
	B3_F        = A3_S,
	B3          = 0x3B,

	C4          = 0x3C,      // ド
	C4_S        = 0x3D,      // ド#
	D4_F        = C4_S,      // レb
	D4          = 0x3E,      // レ
	D4_S        = 0x3F,      // レ#
	E4_F        = D4_S,      // ミb
	E4          = 0x40,      // ミ
	F4          = 0x41,      // ファ
	F4_S        = 0x42,      // ファ#
	G4_F        = F4_S,      // ソb
	G4          = 0x43,      // ソ
	G4_S        = 0x44,      // ソ#
	A4_F        = G4_S,      // ラb
	A4          = 0x45,      // ラ
	A4_S        = 0x46,      // ラ#
	B4_F        = A4_S,      // シb
	B4          = 0x47,      // シ
			
	C5          = 0x48,
	C5_S        = 0x49,
	D5_F        = C5_S,
	D5          = 0x4A,
	D5_S        = 0x4B,
	E5_F        = D5_S,
    E5          = 0x4C,
	F5          = 0x4D,
	F5_S        = 0x4E,
	G5_F        = F5_S,
	G5          = 0x4F,
	G5_S        = 0x50,
	A5_F        = G5_S,
	A5          = 0x51,
	A5_S        = 0x52,
	B5_F        = A5_S,
	B5          = 0x53,
			
	C6          = 0x54,
	C6_S        = 0x55,
	D6_F        = C5_S,
	D6          = 0x56,
	D6_S        = 0x57,
	E6_F        = D5_S,
    E6          = 0x58,
	F6          = 0x59,
	F6_S        = 0x5A,
	G6_F        = F5_S,
	G6          = 0x5B,
	G6_S        = 0x5C,
	A6_F        = G5_S,
	A6          = 0x5D,
	A6_S        = 0x5E,
	B6_F        = A5_S,
	B6          = 0x5F,
	
	C7          = 0x60,
	C7_S        = 0x61,
	D7_F        = C7_S,
	D7          = 0x62,
	D7_S        = 0x63,
	E7_F        = D7_S,
    E7          = 0x64,
	F7          = 0x65,
	F7_S        = 0x66,
	G7_F        = F7_S,
	G7          = 0x67,
	G7_S        = 0x68,
	A7_F        = G7_S,
	A7          = 0x69,
	A7_S        = 0x6A,
	B7_F        = A7_S,
	B7          = 0x6B,
			
	C8          = 0x6C,
	C8_S        = 0x6D,
	D8_F        = C8_S,
	D8          = 0x6E,
	D8_S        = 0x6F,
	E8_F        = D8_S,
    E8          = 0x70,
	F8          = 0x71,
	F8_S        = 0x72,
	G8_F        = F8_S,
	G8          = 0x73,
	G8_S        = 0x74,
	A8_F        = G8_S,
	A8          = 0x75,
	A8_S        = 0x76,
	B8_F        = A8_S,
	B8          = 0x77,
			
	C9          = 0x78,
	C9_S        = 0x79,
	D9_F        = C9_S,
	D9          = 0x7A,
	D9_S        = 0x7B,
	E9_F        = D9_S,
    E9          = 0x7C,
	F9          = 0x7D,
	F9_S        = 0x7E,
	G9_F        = F9_S,
	G9          = 0x7F,
	G9_S        = 0x80,
	A9_F        = G9_S,
	A9          = 0x81,
	A9_S        = 0x82,
	B9_F        = A9_S,
	B9          = 0x83,
			
	C10         = 0x84,
	C10_S       = 0x85,
	D10_F       = C10_S,
	D10         = 0x86,
	D10_S       = 0x87,
	E10_F       = D10_S,
    E10         = 0x88,
	F10         = 0x89,
	F10_S       = 0x8A,
	G10_F       = F10_S,
	G10         = 0x8B,
	G10_S       = 0x8C,
	A10_F       = G10_S,
	A10         = 0x8D,
	A10_S       = 0x8E,
	B10_F       = A10_S,
	B10         = 0x8F,
			
	C11         = 0x90,
	C11_S       = 0x91,
	D11_F       = C11_S,
	D11         = 0x92,
	D11_S       = 0x93,
	E11_F       = D11_S,
    E11         = 0x94,
	F11         = 0x95,
	F11_S       = 0x96,
	G11_F       = F11_S,
	G11         = 0x97,
	G11_S       = 0x98,
	A11_F       = G11_S,
	A11         = 0x99,
	A11_S       = 0x9A,
	B11_F       = A11_S,
	B11         = 0x9B,
				
	C12         = 0x9C,
	C12_S       = 0x9D,
	D12_F       = C12_S,
	D12         = 0x9E,
	D12_S       = 0x9F,
	E12_F       = D12_S,
    E12         = 0xA0,
	F12         = 0xA1,
	F12_S       = 0xA2,
	G12_F       = F12_S,
	G12         = 0xA3,
	G12_S       = 0xA4,
	A12_F       = G12_S,
	A12         = 0xA5,
	A12_S       = 0xA6,
	B12_F       = A12_S,
	B12         = 0xA7,
			
	C13         = 0xA8,
	C13_S       = 0xA9,
	D13_F       = C13_S,
	D13         = 0xAA,
	D13_S       = 0xAB,
	E13_F       = D13_S,
    E13         = 0xAC,
	F13         = 0xAD,
	F13_S       = 0xAE,
	G13_F       = F13_S,
	G13         = 0xAF,
	G13_S       = 0xB0,
	A13_F       = G13_S,
	A13         = 0xB1,
	A13_S       = 0xB2,
	B13_F       = A13_S,
	B13         = 0xB3,
			
	C14         = 0xB4,
	C14_S       = 0xB5,
	D14_F       = C14_S,
	D14         = 0xB6,
	D14_S       = 0xB7,
	E14_F       = D14_S,
    E14         = 0xB8,
	F14         = 0xB9,
	F14_S       = 0xBA,
	G14_F       = F14_S,
	G14         = 0xBB,
	G14_S       = 0xBC,
	A14_F       = G14_S,
	A14         = 0xBD,
	A14_S       = 0xBE,
	B14_F       = A14_S,
	B14         = 0xBF,
			
	C15         = 0xC0,
	C15_S       = 0xC1,
	D15_F       = C15_S,
	D15         = 0xC2,
	D15_S       = 0xC3,
	E15_F       = D15_S,
    E15         = 0xC4,
	F15         = 0xC5,
	F15_S       = 0xC6,
	G15_F       = F15_S,
	G15         = 0xC7,
	G15_S       = 0xC8,
	A15_F       = G15_S,
	A15         = 0xC9,
	A15_S       = 0xCA,
	B15_F       = A15_S,
	B15         = 0xCB,
					
	C16         = 0xCC,
	C16_S       = 0xCD,
	D16_F       = C16_S,
	D16         = 0xCE,
	D16_S       = 0xCF,
	E16_F       = D16_S,
    E16         = 0xD0,
	F16         = 0xD1,
	F16_S       = 0xD2,
	G16_F       = F16_S,
	G16         = 0xD3,
	G16_S       = 0xD4,
	A16_F       = G16_S,
	A16         = 0xD5,
	A16_S       = 0xD6,
	B16_F       = A16_S,
	B16         = 0xD7,
			
	C17         = 0xD8,
	C17_S       = 0xD9,
	D17_F       = C17_S,
	D17         = 0xDA,
	D17_S       = 0xDB,
	E17_F       = D17_S,
    E17         = 0xDC,
	F17         = 0xDD,
	F17_S       = 0xDE,
	G17_F       = F17_S,
	G17         = 0xDF,
	G17_S       = 0xE0,
	A17_F       = G17_S,
	A17         = 0xE1,
	A17_S       = 0xE2,
	B17_F       = A17_S,
	B17         = 0xE3,
			
	C18         = 0xE4,
	C18_S       = 0xE5,
	D18_F       = C18_S,
	D18         = 0xE6,
	D18_S       = 0xE7,
	E18_F       = D18_S,
    E18         = 0xE8,
	F18         = 0xE9,
	F18_S       = 0xEA,
	G18_F       = F18_S,
	G18         = 0xEB,
	G18_S       = 0xEC,
	A18_F       = G18_S,
	A18         = 0xED,
	A18_S       = 0xEE,
	B18_F       = A18_S,
	B18         = 0xEF,
			
	C19         = 0xF0,
	C19_S       = 0xF1,
	D19_F       = C19_S,
	D19         = 0xF2,
	D19_S       = 0xF3,
	E19_F       = D19_S,
    E19         = 0xF4,
	F19         = 0xF5,
	F19_S       = 0xF6,
	G19_F       = F19_S,
	G19         = 0xF7,
	G19_S       = 0xF8,
	A19_F       = G19_S,
	A19         = 0xF9,
	A19_S       = 0xFA,
	B19_F       = A19_S,
	B19         = 0xFB,

	C20         = 0xFC,
	C20_S       = 0xFD,
	D20_F       = C20_S,
	D20         = 0xFE,
	D20_S       = 0xFF,
};

enum DrumKey : MofU8
{
	// ドラム
	AcousticBassDrum = B1,
	BassDrum         = C2,

	SideStick        = C2_S,
	AcousticSnare    = D2,
	HandClap         = D2_S,
	ElectricSnare    = E2,
		
	LowFloorTom      = F2,
	HighFloorTom     = G2,
	LowTom           = A2,
	LowMidTom        = B2,
	HighMidTom       = C3,
	HighTom          = D3,

	ClosedHighHat    = F2_S,
	PedalHighHat     = G2_S,
	OpenHighHat      = A2_S,

	CrashSymbal1     = C3_S,
	RideSymbal1      = D3_S,
	ChineseSymbal    = E3,
	RideBell         = F3,
	SprashSymbal     = G3,
	CrashSymbal2     = A3,
	RideSymbal2      = B3,

	Tambourine       = F3_S,
	Cowbell          = G3_S,
	Vivraslap        = A3_S,
	MuteTriangle     = G5_S,
	OpenTriangle     = A5,

	HighBongo        = C4,
	LowBongo         = C4_S,
	MuteHighConga    = D4,
	OpenHighConga    = D4_S,
	LowConga         = E4,
	HighTimbale      = F4,
	LowTimbale       = F4_S,
	HighAgogo        = G4,
	LowAgogo         = G4_S,
	Cabasa           = A4,
	Maracas          = A4_S,
	ShortWhistle     = B4,
	LongWhistle      = C5,
	ShortGuiro       = C5_S,
	LongGuiro        = D5,
	Claves           = D5_S,
	HighWoodBlock    = E5,
	LowWoodBlock     = F5,
	CloseCuica       = F5_S,
	OpenCuica        = G5,
};

enum GMInstrument : MofU8
{
	// ピアノ系
	AcosticGrandPiano = 0,    // アコースティック・グランド・ピアノ
	BrightAcosticPiano,       // ブライト・アコースティック・ピアノ(明るい音色)
	ElectricGrandPiano,       // エレクトリック・グランド・ピアノ
	HonkyTonkPiano,           // ホンキー・トンク・ピアノ
	ElectricPiano1,           // エレピアノタイプ１
	ElectricPiano2,           // エレピアノタイプ２
	Harpsicord,               // ハープシーコード
	Clavi,                    // クラビネット

	// クロマチック・パーカッション系
	Celesta,                  // クレスタ(鉄琴)
	Glockenspiel,             // グロッケン・シュプール
	MusicBox,                 // オルゴール
	Vibraphone,               // ヴィヴラフォン(大型鉄琴)
	Marimba,                  // マリンバ(大型木琴)
	Xylophone,                // サイロフォン(木琴)
	TubularBells,             // チューブラー・ベル
	Dulcimer,                 // ダルシマー

	// オルガン系
	DrawberOrgan,             // 一般的なオルガン
	PercussiveOrgan,          // アタック(タッチ)感が強いオルガン
	RockOrgan,                // レスリー・オルガン
	ChurchOrgan,              // パイプオルガン
	ReadOrgan,                // 足踏みオルガン
	Acoordion,                // アコーディオン
	Harmonica,                // ハーモニカ
	TangoAccordion,           // ボタン・アコーディオン

	// ギター系
	NylonAcosticGuitar,       // ナイロン弦のアコースティック・ギター(ガット・ギター)
	SteelAcosticGuitar,       // スチール弦のアコースティック・ギター(フォーク・ギター)
	JazzElectricGuitar,       // ジャズ用エレキ・ギター
	CleanElectricGuitar,      // クリーン用エレキ・ギター
	MutedElectricGuitar,      // ミュートギター
	OverdrivenGuitar,         // 歪んだ音のギター
	DistortionGuitar,         // オーバードライブギターをさらに歪ませたギター
	GuitarHarmonics,          // ハーモニクス

	// ベース系
	AcousticBass,             // アコースティック・ベース
	FingeredElectricBass,     // 指弾きベース
	PickedElectricBass,       // ピック弾きベース
	FretlessBass,             // フレットレス・ベース
	SlapBass1,                // スラップベース１
	SlapBass2,                // スラップベース２
	SynthBass1,               // シンセ・ベース１
	SynthBass2,               // シンセ・ベース２

	// ストリングス系
	Violin,                   // ヴァイオリン
	Viola,                    // ヴィオラ
	Cello,                    // チェロ
	Contrabass,               // コントラバス
	TremoloStrings,           // トレモロ弾きのストリングス
	PizzicatoStrings,         // ピチカート(ミュート)弾きのストリングス
	OrchestralHarp,           // ハープ
	Timpani,                  // ティンパニ

	// アンサンブル系
	StringEnsemble1,          // ストリングス・アンサンブル１ 基本形
	StringEnsemble2,          // ストリングス・アンサンブル２ ソフト
	SynthStrings1,            // シンセ・ストリングス・アンサンブル１
	SynthStrings2,            // シンセ・ストリングス・アンサンブル２
	ChoirAahs,                // コーラス・アンサンブル
	VoiceOohs,                // コーラス・アンサンブル
	SynthChoir,               // ヴォイスアンサンブル
	OrchestraHit,             // オーケストラ・ヒット

	// ブラス系
	Trumpet,                  // トランペット
	Trombone,                 // トロンボーン
	Tuba,                     // チューバ
	MutedTrumpet,             // 消音器の付いたトランペット
	FrenchHorn,               // ホルン
	BrassSection,             // ブラス・アンサンブル
	SynthBrass1,              // シンセ・アンサンブル１
	SynthBrass2,              // シンセ・アンサンブル２

	// リード系
	SopranoSax,               // ソプラノ・サックス
	AltoSax,                  // アルト・サックス
	TenorSax,                 // テナー・サックス
	BaritoneSax,              // バリトン・サックス
	Oboe,                     // オーボエ
	EnglishHorn,              // イングリッシュ・ホルン
	Bassoon,                  // バスーン
	Clarinet,                 // クラリネット

	// パイプ系
	Piccolo,                  // ピッコロ
	Flute,                    // フルート
	Recorder,                 // リコーダー
	PanFlute,                 // パン・フルート
	Blownbottle,              // 瓶の口に息を吹きかけて出る音
	Shakuhachi,               // 尺八
	Whistle,                  // 口笛
	Ocarina,                  // オカリナ

	// シンセ・リード系
	SquareWave,               // 矩形波
	SawWave,                  // 鋸歯状波
	SynCalliope,              // カリオペ風
	ChifferLead,              // やわらかめの音
	Charang,                  // 硬めの音
	SoloVox,                  // ヒューマン・ヴォイス
	FifthSawWave,             // 5度の和音付き
	BassAndLead,              // シンセ・ベース付き

	// シンセ・パッド系
	Fantasia,                 // ベル系
	WarmPad,                  // 温かみのある音
	Polysynth,                // ポリ・ムーグ
	SpaceVoice,               // コーラス系
	BowedGlass,               // グラス破擦系
	MetalPad,                 // 金属系
	HaloPad,                  // 明るい音
	SweepPad,                 // うねり系

	// シンセ・エフェクト系
	IceRain,                  // FX1
	Soundtrack,               // FX2
	Crystal,                  // FX3
	Atmosphere,               // FX4
	Brightness,               // FX5
	Goblin,                   // FX6
	EchoDrops,                // FX7
	StarTheme,                // FX8

	// エスニック系
	Sitar,                    // シタール
	Banjo,                    // バンジョー
	Shamisen,                 // 三味線
	Koto,                     // 琴
	Kalimba,                  // カリンバ
	Bagpipe,                  // バグパイプ
	Fiddle,                   // フィドル
	Shanai,                   // ショーム

	// パーカッシヴ系
	TinkleBell,               // クリスマス・ベル
	Agogo,                    // アゴーゴ
	SteelDrums,               // スティール・ドラム
	Woodblock,                // ウッドブロック
	TaikoDrum,                // 和太鼓
	MelodicTom,               // メロ・タム
	SynthDrum,                // シンセ・タム
	ReverseCymbal,            // リヴァース・シンバル

	// 効果音
	GuitarFretNoise,          // ギターのフレットをこする音
	BreathNoise,              // 息継ぎ音
	Seashore,                 // 波音
	BirdTweet,                // 鳥の鳴き声
	TelephoneRing,            // 黒電話のベル音
	Helicopter,               // ヘリコプターのプロペラ音
	Applause,                 // 拍手
	Gunshot,                  // 銃声
};

constexpr char* InstrumentNameStr[] =
{
	// ピアノ系
	"アコースティック・グランド・ピアノ",
	"ブライト・アコースティック・ピアノ(明るい音色)",
	"エレクトリック・グランド・ピアノ",
	"ホンキー・トンク・ピアノ",
	"エレピアノタイプ１",
	"エレピアノタイプ２",
	"ハープシーコード",
	"クラビネット",

	// クロマチック・パーカッション系
	"クレスタ(鉄琴)",
	"グロッケン・シュプール",
	"オルゴール",
	"ヴィヴラフォン(大型鉄琴)",
	"マリンバ(大型木琴)",
	"サイロフォン(木琴)",
	"チューブラー・ベル",
	"ダルシマー",

	// オルガン系
	"一般的なオルガン"
	"アタック(タッチ)感が強いオルガン",
	"レスリー・オルガン",
	"パイプオルガン",
	"足踏みオルガン",
	"アコーディオン",
	"ハーモニカ",
	"ボタン・アコーディオン",

	// ギター系
	"ナイロン弦のアコースティック・ギター(ガット・ギター)",
	"スチール弦のアコースティック・ギター(フォーク・ギター)",
	"ジャズ用エレキ・ギター",
	"クリーン用エレキ・ギター",
	"ミュートギター",
	"歪んだ音のギター",
	"オーバードライブギターをさらに歪ませたギター",
	"ハーモニクス",

	// ベース系
	"アコースティック・ベース",
	"指弾きベース",
	"ピック弾きベース",
	"フレットレス・ベース",
	"スラップベース１",
	"スラップベース２",
	"シンセ・ベース１",
	"シンセ・ベース２",

	// ストリングス系
	"ヴァイオリン",
	"ヴィオラ",
	"チェロ",
	"コントラバス",
	"トレモロ弾きのストリングス",
	"ピチカート(ミュート)弾きのストリングス",
	"ハープ",
	"ティンパニ",

	// アンサンブル系
	"ストリングス・アンサンブル１ 基本形",
	"ストリングス・アンサンブル２ ソフト",
	"シンセ・ストリングス・アンサンブル１",
	"シンセ・ストリングス・アンサンブル２",
	"コーラス・アンサンブル",
	"コーラス・アンサンブル",
	"ヴォイスアンサンブル",
	"オーケストラ・ヒット",

	// ブラス系
	"トランペット",
	"トロンボーン",
	"チューバ",
	"消音器の付いたトランペット",
	"ホルン",
	"ブラス・アンサンブル",
	"シンセ・アンサンブル１",
	"シンセ・アンサンブル２",

	// リード系
	"ソプラノ・サックス",
	"アルト・サックス",
	"テナー・サックス",
	"バリトン・サックス",
	"オーボエ",
	"イングリッシュ・ホルン",
	"バスーン",
	"クラリネット",

	// パイプ系
	"ピッコロ",
	"フルート",
	"リコーダー",
	"パン・フルート",
	"瓶の口に息を吹きかけて出る音",
	"尺八",
	"口笛",
	"オカリナ",

	// シンセ・リード系
	"矩形波",
	"鋸歯状波",
	"カリオペ風",
	"やわらかめの音",
	"硬めの音",
	"ヒューマン・ヴォイス",
	"5度の和音付き",
	"シンセ・ベース付き",

	// シンセ・パッド系
	"ベル系",
	"温かみのある音",
	"ポリ・ムーグ",
	"コーラス系",
	"グラス破擦系",
	"金属系",
	"明るい音",
	"うねり系",

	// シンセ・エフェクト系
	"FX1",
	"FX2",
	"FX3",
	"FX4",
	"FX5",
	"FX6",
	"FX7",
	"FX8",

	// エスニック系
	"シタール",
	"バンジョー",
	"三味線",
	"琴",
	"カリンバ",
	"バグパイプ",
	"フィドル",
	"ショーム",

	// パーカッシヴ系
	"クリスマス・ベル",
	"アゴーゴ",
	"スティール・ドラム",
	"ウッドブロック",
	"和太鼓",
	"メロ・タム",
	"シンセ・タム",
	"リヴァース・シンバル",

	// 効果音
	"ギターのフレットをこする音",
	"息継ぎ音",
	"波音",
	"鳥の鳴き声",
	"黒電話のベル音",
	"ヘリコプターのプロペラ音",
	"拍手",
	"銃声",
};

enum Event : MofU8
{
	Meta                             = 0xFF, 

	//システムエクスクルシーブメッセージを格納するイベント。個々の楽器メーカが独自に作成したメッセージを格納する。MIDIデバイスに何かしら設定するのに利用される。
	SysEx                            = 0xF0,     // F0 データ長 エクスクルシーブメッセージ F7
	SysEx_F7                         = 0xF7,     // F7 データ長 エクスクルシーブメッセージ
											 
	MIDI_PolyPhonic_Key_Pressure     = 0xA0,     // An kk vv nのチャンネルのkk番目のノートにベロシティvvのプレッシャー情報を与える。
	MIDI_Control                     = 0xB0,     // Bn cc vv コントローラ設定。チャンネルnでコントローラナンバーccにvvの値を送る。
	MIDI_Program_Change              = 0xC0,     // Cn pp    プログラムチェンジ。チャンネルnで、音色をppに変更する。
	MIDI_Channel_Pressure            = 0xD0,     // Dn vv    チャンネルnに対してプレッシャー情報vvを送信する。
	MIDI_Pitch_Bend                  = 0xE0,     // En mm ll ピッチベント。なぜかリトルエンディアンらしい。
	MIDI_Note_On                     = 0x90,     // 9n       ノート・オン
	MIDI_Note_Off                    = 0x80,     // 8n       ノート・オフ
};

enum MetaEvent : MofU8
{
	//メタイベント                               // FF｜イベントタイプ｜データ長｜     データ
	Sequence_Nunber                  = 0x00,     // FF              00        02               シーケンス番号、フォーマット 0 と 1
	Comment                          = 0x01,     // FF              01       len         data　テキストを書き込むためのイベント。
	Copy_Right                       = 0x02,     // FF              02       len         data　著作権が書いてある。
	Sequence_Track_Name              = 0x03,     // FF              03       len         data　シーケンス名(曲名)・トラック名。
	Instrument_Name                  = 0x04,     // FF              04       len         data　楽器名。
	Lyric                            = 0x05,     // FF              05       len         data　lyricは歌詞の事。
	Marker                           = 0x06,     // FF              06       len         data　リハーサル記号やセクション名のような、シーケンスのその時点の名称を記述する。
	Queue_Point                      = 0x07,     // FF              07       len         data　曲データ中、このイベントが挿入されている位置で、曲以外の進行を記述する。(画面のフェードアウトのような動画等に対する進行)
	Program_Name                     = 0x08,     // FF              08       len         data　プログラムチェンジとバンクチェンジで表している音色名を記載する（General MIDIが制定される前の遺物）
	Device_Name                      = 0x09,     // FF              09       len         data　このイベントがあるトラックがどのデバイスに配置されるのかということを示す。このイベントは、1トラックにつき1度だけ、最初に呼ばれるべきもの。
	Channel_Prefix                   = 0x20,     // FF              20        01           cc  MIDIイベントじゃないのに(SysEx or メタイベント)MIDIチャンネルを指定する際に用いる。
	Port_Specified                   = 0x21,     // FF              21        01           pp  出力ポートの指定  0 ～ 3 がそれぞれポートの 1 ～ 4 に対応する(例外はあるが、データのみでは判別不可)
	End_Of_Track                     = 0x2F,     // FF              2F        00　             トラックの最後であることを表す。
	Set_Tempo                        = 0x51,     // FF              51        03     tt tt tt　tttttt(3byte)には、4分音符の長さをμ秒で表したものを格納する。BPM = 120の時、4分音符の長さは 60 x 10^6 / 120 = 500000[μs]
	Smtpte_Offset                    = 0x54,     // FF              54        05   frmnsefrff　このイベントが存在する場合、トラックチャンクがスタートすべきSMPTEタイムを指定する。詳しくは規格の142ページ。
	Time_Signature                   = 0x58,     // FF              58        04  nn dd cc bb  拍子 nn = 分子 dd = 分子 cc = メトロノーム間隔[四分音符間隔なら18H] bb = 四分音符当たりの三十二分音符の数。
	Key_Signature                    = 0x59,     // FF              59        02        sf ml  キー(調)を示す   sf = 正:シャープの数 or 負:フラットの数       ml = 0:長調(メジャー) 1:短調(マイナー)
	Special_Meta_Event               = 0x7F,     // FF              7F       len         data　最初の1バイトはメーカIDで、その後に独自フォーマットのデータが続く。
	FF_None                          = 0xFF,     //                                            何も見つからなかった時、これを入れる。
};