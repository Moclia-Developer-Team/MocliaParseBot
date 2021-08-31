/**
 * 一些需要全局引用的头文件和机器人定义
*/
#pragma once

#ifndef _ParseBotVersion_
#define _ParseBotVersion_  "1.0.0"
#endif
#ifndef _BotName_
#define _BotName_  "MocliaParseBot"
#endif
#ifndef _BotAuthor_
#define _BotAuthor_  "Moclia-Development-Team 星翛-STASWIT"
#endif

// 标准库  
#include <iostream>
#include <map>
#include <string>

// 第三方库  
#include <mirai/mirai.h>

class MocliaUsingApi
{
public:
	class cloudMusic
	{
	public:
		const std::string search = "http://music.163.com/api/search/pc";
		const std::string jump = "https://music.163.com/#/song?id=";
		const std::string play = "http://music.163.com/song/media/outer/url?id=";
	};
};