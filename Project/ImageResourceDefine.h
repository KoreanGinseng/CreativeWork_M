#pragma once
#include <iostream>

// 画像データの列挙。
enum IMAGE_RESOURCE
{

	BABY_BOY,

	IMAGE_RESOURCE_COUNT,

};

// 画像データの定義。
constexpr std::pair<char*, char*> ImageResource[IMAGE_RESOURCE_COUNT] = 
{
	{ "baby_boy", "baby_boy.png" },
};