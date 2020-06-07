#pragma once
#include <iostream>

// 成長区分の列挙。
enum GROW_KEY
{
	BABY  = 0b0000, // 幼少
	CHILD = 0b0001, // 子ども
	YOUNG = 0b0010, // 青年
	ADULT = 0b0100, // 成人
	ELDER = 0b1000, // 老人
};


// 図鑑に登録されるキャラクター列挙。
enum CHARACTER_GUITE 
{

	BABY_BOY              = 0b00000000,

};


// 成長区分を引数から調べる関数。
char GetGrowKey(const short& guideNo)
{
	return guideNo >> 4;
}