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

	C4          = 0x3C,      // �h
	C4_S        = 0x3D,      // �h#
	D4_F        = C4_S,      // ��b
	D4          = 0x3E,      // ��
	D4_S        = 0x3F,      // ��#
	E4_F        = D4_S,      // �~b
	E4          = 0x40,      // �~
	F4          = 0x41,      // �t�@
	F4_S        = 0x42,      // �t�@#
	G4_F        = F4_S,      // �\b
	G4          = 0x43,      // �\
	G4_S        = 0x44,      // �\#
	A4_F        = G4_S,      // ��b
	A4          = 0x45,      // ��
	A4_S        = 0x46,      // ��#
	B4_F        = A4_S,      // �Vb
	B4          = 0x47,      // �V
			
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
	// �h����
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
	// �s�A�m�n
	AcosticGrandPiano = 0,    // �A�R�[�X�e�B�b�N�E�O�����h�E�s�A�m
	BrightAcosticPiano,       // �u���C�g�E�A�R�[�X�e�B�b�N�E�s�A�m(���邢���F)
	ElectricGrandPiano,       // �G���N�g���b�N�E�O�����h�E�s�A�m
	HonkyTonkPiano,           // �z���L�[�E�g���N�E�s�A�m
	ElectricPiano1,           // �G���s�A�m�^�C�v�P
	ElectricPiano2,           // �G���s�A�m�^�C�v�Q
	Harpsicord,               // �n�[�v�V�[�R�[�h
	Clavi,                    // �N���r�l�b�g

	// �N���}�`�b�N�E�p�[�J�b�V�����n
	Celesta,                  // �N���X�^(�S��)
	Glockenspiel,             // �O���b�P���E�V���v�[��
	MusicBox,                 // �I���S�[��
	Vibraphone,               // ���B�����t�H��(��^�S��)
	Marimba,                  // �}�����o(��^�؋�)
	Xylophone,                // �T�C���t�H��(�؋�)
	TubularBells,             // �`���[�u���[�E�x��
	Dulcimer,                 // �_���V�}�[

	// �I���K���n
	DrawberOrgan,             // ��ʓI�ȃI���K��
	PercussiveOrgan,          // �A�^�b�N(�^�b�`)���������I���K��
	RockOrgan,                // ���X���[�E�I���K��
	ChurchOrgan,              // �p�C�v�I���K��
	ReadOrgan,                // �����݃I���K��
	Acoordion,                // �A�R�[�f�B�I��
	Harmonica,                // �n�[���j�J
	TangoAccordion,           // �{�^���E�A�R�[�f�B�I��

	// �M�^�[�n
	NylonAcosticGuitar,       // �i�C�������̃A�R�[�X�e�B�b�N�E�M�^�[(�K�b�g�E�M�^�[)
	SteelAcosticGuitar,       // �X�`�[�����̃A�R�[�X�e�B�b�N�E�M�^�[(�t�H�[�N�E�M�^�[)
	JazzElectricGuitar,       // �W���Y�p�G���L�E�M�^�[
	CleanElectricGuitar,      // �N���[���p�G���L�E�M�^�[
	MutedElectricGuitar,      // �~���[�g�M�^�[
	OverdrivenGuitar,         // �c�񂾉��̃M�^�[
	DistortionGuitar,         // �I�[�o�[�h���C�u�M�^�[������ɘc�܂����M�^�[
	GuitarHarmonics,          // �n�[���j�N�X

	// �x�[�X�n
	AcousticBass,             // �A�R�[�X�e�B�b�N�E�x�[�X
	FingeredElectricBass,     // �w�e���x�[�X
	PickedElectricBass,       // �s�b�N�e���x�[�X
	FretlessBass,             // �t���b�g���X�E�x�[�X
	SlapBass1,                // �X���b�v�x�[�X�P
	SlapBass2,                // �X���b�v�x�[�X�Q
	SynthBass1,               // �V���Z�E�x�[�X�P
	SynthBass2,               // �V���Z�E�x�[�X�Q

	// �X�g�����O�X�n
	Violin,                   // ���@�C�I����
	Viola,                    // ���B�I��
	Cello,                    // �`�F��
	Contrabass,               // �R���g���o�X
	TremoloStrings,           // �g�������e���̃X�g�����O�X
	PizzicatoStrings,         // �s�`�J�[�g(�~���[�g)�e���̃X�g�����O�X
	OrchestralHarp,           // �n�[�v
	Timpani,                  // �e�B���p�j

	// �A���T���u���n
	StringEnsemble1,          // �X�g�����O�X�E�A���T���u���P ��{�`
	StringEnsemble2,          // �X�g�����O�X�E�A���T���u���Q �\�t�g
	SynthStrings1,            // �V���Z�E�X�g�����O�X�E�A���T���u���P
	SynthStrings2,            // �V���Z�E�X�g�����O�X�E�A���T���u���Q
	ChoirAahs,                // �R�[���X�E�A���T���u��
	VoiceOohs,                // �R�[���X�E�A���T���u��
	SynthChoir,               // ���H�C�X�A���T���u��
	OrchestraHit,             // �I�[�P�X�g���E�q�b�g

	// �u���X�n
	Trumpet,                  // �g�����y�b�g
	Trombone,                 // �g�����{�[��
	Tuba,                     // �`���[�o
	MutedTrumpet,             // ������̕t�����g�����y�b�g
	FrenchHorn,               // �z����
	BrassSection,             // �u���X�E�A���T���u��
	SynthBrass1,              // �V���Z�E�A���T���u���P
	SynthBrass2,              // �V���Z�E�A���T���u���Q

	// ���[�h�n
	SopranoSax,               // �\�v���m�E�T�b�N�X
	AltoSax,                  // �A���g�E�T�b�N�X
	TenorSax,                 // �e�i�[�E�T�b�N�X
	BaritoneSax,              // �o���g���E�T�b�N�X
	Oboe,                     // �I�[�{�G
	EnglishHorn,              // �C���O���b�V���E�z����
	Bassoon,                  // �o�X�[��
	Clarinet,                 // �N�����l�b�g

	// �p�C�v�n
	Piccolo,                  // �s�b�R��
	Flute,                    // �t���[�g
	Recorder,                 // ���R�[�_�[
	PanFlute,                 // �p���E�t���[�g
	Blownbottle,              // �r�̌��ɑ��𐁂������ďo�鉹
	Shakuhachi,               // �ڔ�
	Whistle,                  // ���J
	Ocarina,                  // �I�J���i

	// �V���Z�E���[�h�n
	SquareWave,               // ��`�g
	SawWave,                  // ������g
	SynCalliope,              // �J���I�y��
	ChifferLead,              // ���炩�߂̉�
	Charang,                  // �d�߂̉�
	SoloVox,                  // �q���[�}���E���H�C�X
	FifthSawWave,             // 5�x�̘a���t��
	BassAndLead,              // �V���Z�E�x�[�X�t��

	// �V���Z�E�p�b�h�n
	Fantasia,                 // �x���n
	WarmPad,                  // �����݂̂��鉹
	Polysynth,                // �|���E���[�O
	SpaceVoice,               // �R�[���X�n
	BowedGlass,               // �O���X�j�C�n
	MetalPad,                 // �����n
	HaloPad,                  // ���邢��
	SweepPad,                 // ���˂�n

	// �V���Z�E�G�t�F�N�g�n
	IceRain,                  // FX1
	Soundtrack,               // FX2
	Crystal,                  // FX3
	Atmosphere,               // FX4
	Brightness,               // FX5
	Goblin,                   // FX6
	EchoDrops,                // FX7
	StarTheme,                // FX8

	// �G�X�j�b�N�n
	Sitar,                    // �V�^�[��
	Banjo,                    // �o���W���[
	Shamisen,                 // �O����
	Koto,                     // ��
	Kalimba,                  // �J�����o
	Bagpipe,                  // �o�O�p�C�v
	Fiddle,                   // �t�B�h��
	Shanai,                   // �V���[��

	// �p�[�J�b�V���n
	TinkleBell,               // �N���X�}�X�E�x��
	Agogo,                    // �A�S�[�S
	SteelDrums,               // �X�e�B�[���E�h����
	Woodblock,                // �E�b�h�u���b�N
	TaikoDrum,                // �a����
	MelodicTom,               // �����E�^��
	SynthDrum,                // �V���Z�E�^��
	ReverseCymbal,            // �����@�[�X�E�V���o��

	// ���ʉ�
	GuitarFretNoise,          // �M�^�[�̃t���b�g�������鉹
	BreathNoise,              // ���p����
	Seashore,                 // �g��
	BirdTweet,                // ���̖���
	TelephoneRing,            // ���d�b�̃x����
	Helicopter,               // �w���R�v�^�[�̃v���y����
	Applause,                 // ����
	Gunshot,                  // �e��
};

constexpr char* InstrumentNameStr[] =
{
	// �s�A�m�n
	"�A�R�[�X�e�B�b�N�E�O�����h�E�s�A�m",
	"�u���C�g�E�A�R�[�X�e�B�b�N�E�s�A�m(���邢���F)",
	"�G���N�g���b�N�E�O�����h�E�s�A�m",
	"�z���L�[�E�g���N�E�s�A�m",
	"�G���s�A�m�^�C�v�P",
	"�G���s�A�m�^�C�v�Q",
	"�n�[�v�V�[�R�[�h",
	"�N���r�l�b�g",

	// �N���}�`�b�N�E�p�[�J�b�V�����n
	"�N���X�^(�S��)",
	"�O���b�P���E�V���v�[��",
	"�I���S�[��",
	"���B�����t�H��(��^�S��)",
	"�}�����o(��^�؋�)",
	"�T�C���t�H��(�؋�)",
	"�`���[�u���[�E�x��",
	"�_���V�}�[",

	// �I���K���n
	"��ʓI�ȃI���K��"
	"�A�^�b�N(�^�b�`)���������I���K��",
	"���X���[�E�I���K��",
	"�p�C�v�I���K��",
	"�����݃I���K��",
	"�A�R�[�f�B�I��",
	"�n�[���j�J",
	"�{�^���E�A�R�[�f�B�I��",

	// �M�^�[�n
	"�i�C�������̃A�R�[�X�e�B�b�N�E�M�^�[(�K�b�g�E�M�^�[)",
	"�X�`�[�����̃A�R�[�X�e�B�b�N�E�M�^�[(�t�H�[�N�E�M�^�[)",
	"�W���Y�p�G���L�E�M�^�[",
	"�N���[���p�G���L�E�M�^�[",
	"�~���[�g�M�^�[",
	"�c�񂾉��̃M�^�[",
	"�I�[�o�[�h���C�u�M�^�[������ɘc�܂����M�^�[",
	"�n�[���j�N�X",

	// �x�[�X�n
	"�A�R�[�X�e�B�b�N�E�x�[�X",
	"�w�e���x�[�X",
	"�s�b�N�e���x�[�X",
	"�t���b�g���X�E�x�[�X",
	"�X���b�v�x�[�X�P",
	"�X���b�v�x�[�X�Q",
	"�V���Z�E�x�[�X�P",
	"�V���Z�E�x�[�X�Q",

	// �X�g�����O�X�n
	"���@�C�I����",
	"���B�I��",
	"�`�F��",
	"�R���g���o�X",
	"�g�������e���̃X�g�����O�X",
	"�s�`�J�[�g(�~���[�g)�e���̃X�g�����O�X",
	"�n�[�v",
	"�e�B���p�j",

	// �A���T���u���n
	"�X�g�����O�X�E�A���T���u���P ��{�`",
	"�X�g�����O�X�E�A���T���u���Q �\�t�g",
	"�V���Z�E�X�g�����O�X�E�A���T���u���P",
	"�V���Z�E�X�g�����O�X�E�A���T���u���Q",
	"�R�[���X�E�A���T���u��",
	"�R�[���X�E�A���T���u��",
	"���H�C�X�A���T���u��",
	"�I�[�P�X�g���E�q�b�g",

	// �u���X�n
	"�g�����y�b�g",
	"�g�����{�[��",
	"�`���[�o",
	"������̕t�����g�����y�b�g",
	"�z����",
	"�u���X�E�A���T���u��",
	"�V���Z�E�A���T���u���P",
	"�V���Z�E�A���T���u���Q",

	// ���[�h�n
	"�\�v���m�E�T�b�N�X",
	"�A���g�E�T�b�N�X",
	"�e�i�[�E�T�b�N�X",
	"�o���g���E�T�b�N�X",
	"�I�[�{�G",
	"�C���O���b�V���E�z����",
	"�o�X�[��",
	"�N�����l�b�g",

	// �p�C�v�n
	"�s�b�R��",
	"�t���[�g",
	"���R�[�_�[",
	"�p���E�t���[�g",
	"�r�̌��ɑ��𐁂������ďo�鉹",
	"�ڔ�",
	"���J",
	"�I�J���i",

	// �V���Z�E���[�h�n
	"��`�g",
	"������g",
	"�J���I�y��",
	"���炩�߂̉�",
	"�d�߂̉�",
	"�q���[�}���E���H�C�X",
	"5�x�̘a���t��",
	"�V���Z�E�x�[�X�t��",

	// �V���Z�E�p�b�h�n
	"�x���n",
	"�����݂̂��鉹",
	"�|���E���[�O",
	"�R�[���X�n",
	"�O���X�j�C�n",
	"�����n",
	"���邢��",
	"���˂�n",

	// �V���Z�E�G�t�F�N�g�n
	"FX1",
	"FX2",
	"FX3",
	"FX4",
	"FX5",
	"FX6",
	"FX7",
	"FX8",

	// �G�X�j�b�N�n
	"�V�^�[��",
	"�o���W���[",
	"�O����",
	"��",
	"�J�����o",
	"�o�O�p�C�v",
	"�t�B�h��",
	"�V���[��",

	// �p�[�J�b�V���n
	"�N���X�}�X�E�x��",
	"�A�S�[�S",
	"�X�e�B�[���E�h����",
	"�E�b�h�u���b�N",
	"�a����",
	"�����E�^��",
	"�V���Z�E�^��",
	"�����@�[�X�E�V���o��",

	// ���ʉ�
	"�M�^�[�̃t���b�g�������鉹",
	"���p����",
	"�g��",
	"���̖���",
	"���d�b�̃x����",
	"�w���R�v�^�[�̃v���y����",
	"����",
	"�e��",
};

enum Event : MofU8
{
	Meta                             = 0xFF, 

	//�V�X�e���G�N�X�N���V�[�u���b�Z�[�W���i�[����C�x���g�B�X�̊y�탁�[�J���Ǝ��ɍ쐬�������b�Z�[�W���i�[����BMIDI�f�o�C�X�ɉ�������ݒ肷��̂ɗ��p�����B
	SysEx                            = 0xF0,     // F0 �f�[�^�� �G�N�X�N���V�[�u���b�Z�[�W F7
	SysEx_F7                         = 0xF7,     // F7 �f�[�^�� �G�N�X�N���V�[�u���b�Z�[�W
											 
	MIDI_PolyPhonic_Key_Pressure     = 0xA0,     // An kk vv n�̃`�����l����kk�Ԗڂ̃m�[�g�Ƀx���V�e�Bvv�̃v���b�V���[����^����B
	MIDI_Control                     = 0xB0,     // Bn cc vv �R���g���[���ݒ�B�`�����l��n�ŃR���g���[���i���o�[cc��vv�̒l�𑗂�B
	MIDI_Program_Change              = 0xC0,     // Cn pp    �v���O�����`�F���W�B�`�����l��n�ŁA���F��pp�ɕύX����B
	MIDI_Channel_Pressure            = 0xD0,     // Dn vv    �`�����l��n�ɑ΂��ăv���b�V���[���vv�𑗐M����B
	MIDI_Pitch_Bend                  = 0xE0,     // En mm ll �s�b�`�x���g�B�Ȃ������g���G���f�B�A���炵���B
	MIDI_Note_On                     = 0x90,     // 9n       �m�[�g�E�I��
	MIDI_Note_Off                    = 0x80,     // 8n       �m�[�g�E�I�t
};

enum MetaEvent : MofU8
{
	//���^�C�x���g                               // FF�b�C�x���g�^�C�v�b�f�[�^���b     �f�[�^
	Sequence_Nunber                  = 0x00,     // FF              00        02               �V�[�P���X�ԍ��A�t�H�[�}�b�g 0 �� 1
	Comment                          = 0x01,     // FF              01       len         data�@�e�L�X�g���������ނ��߂̃C�x���g�B
	Copy_Right                       = 0x02,     // FF              02       len         data�@���쌠�������Ă���B
	Sequence_Track_Name              = 0x03,     // FF              03       len         data�@�V�[�P���X��(�Ȗ�)�E�g���b�N���B
	Instrument_Name                  = 0x04,     // FF              04       len         data�@�y�햼�B
	Lyric                            = 0x05,     // FF              05       len         data�@lyric�͉̎��̎��B
	Marker                           = 0x06,     // FF              06       len         data�@���n�[�T���L����Z�N�V�������̂悤�ȁA�V�[�P���X�̂��̎��_�̖��̂��L�q����B
	Queue_Point                      = 0x07,     // FF              07       len         data�@�ȃf�[�^���A���̃C�x���g���}������Ă���ʒu�ŁA�ȈȊO�̐i�s���L�q����B(��ʂ̃t�F�[�h�A�E�g�̂悤�ȓ��擙�ɑ΂���i�s)
	Program_Name                     = 0x08,     // FF              08       len         data�@�v���O�����`�F���W�ƃo���N�`�F���W�ŕ\���Ă��鉹�F�����L�ڂ���iGeneral MIDI�����肳���O�̈╨�j
	Device_Name                      = 0x09,     // FF              09       len         data�@���̃C�x���g������g���b�N���ǂ̃f�o�C�X�ɔz�u�����̂��Ƃ������Ƃ������B���̃C�x���g�́A1�g���b�N�ɂ�1�x�����A�ŏ��ɌĂ΂��ׂ����́B
	Channel_Prefix                   = 0x20,     // FF              20        01           cc  MIDI�C�x���g����Ȃ��̂�(SysEx or ���^�C�x���g)MIDI�`�����l�����w�肷��ۂɗp����B
	Port_Specified                   = 0x21,     // FF              21        01           pp  �o�̓|�[�g�̎w��  0 �` 3 �����ꂼ��|�[�g�� 1 �` 4 �ɑΉ�����(��O�͂��邪�A�f�[�^�݂̂ł͔��ʕs��)
	End_Of_Track                     = 0x2F,     // FF              2F        00�@             �g���b�N�̍Ō�ł��邱�Ƃ�\���B
	Set_Tempo                        = 0x51,     // FF              51        03     tt tt tt�@tttttt(3byte)�ɂ́A4�������̒������ʕb�ŕ\�������̂��i�[����BBPM = 120�̎��A4�������̒����� 60 x 10^6 / 120 = 500000[��s]
	Smtpte_Offset                    = 0x54,     // FF              54        05   frmnsefrff�@���̃C�x���g�����݂���ꍇ�A�g���b�N�`�����N���X�^�[�g���ׂ�SMPTE�^�C�����w�肷��B�ڂ����͋K�i��142�y�[�W�B
	Time_Signature                   = 0x58,     // FF              58        04  nn dd cc bb  ���q nn = ���q dd = ���q cc = ���g���m�[���Ԋu[�l�������Ԋu�Ȃ�18H] bb = �l������������̎O�\�񕪉����̐��B
	Key_Signature                    = 0x59,     // FF              59        02        sf ml  �L�[(��)������   sf = ��:�V���[�v�̐� or ��:�t���b�g�̐�       ml = 0:����(���W���[) 1:�Z��(�}�C�i�[)
	Special_Meta_Event               = 0x7F,     // FF              7F       len         data�@�ŏ���1�o�C�g�̓��[�JID�ŁA���̌�ɓƎ��t�H�[�}�b�g�̃f�[�^�������B
	FF_None                          = 0xFF,     //                                            ����������Ȃ��������A���������B
};