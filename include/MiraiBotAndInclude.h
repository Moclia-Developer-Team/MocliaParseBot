/******************************************************************************
* ============================================================================
*	  __  __            _ _       _____                    ____        _
*    |  \/  |          | (_)     |  __ \                  |  _ \      | |
*    | \  / | ___   ___| |_  __ _| |__) |_ _ _ __ ___  ___| |_) | ___ | |_
*    | |\/| |/ _ \ / __| | |/ _` |  ___/ _` | '__/ __|/ _ \  _ < / _ \| __|
*    | |  | | (_) | (__| | | (_| | |  | (_| | |  \__ \  __/ |_) | (_) | |_
*    |_|  |_|\___/ \___|_|_|\__,_|_|   \__,_|_|  |___/\___|____/ \___/ \__|
* ============================================================================
* MocliaParseBot by mirai-api-http & mirai-cpp for platform mirai
* Copyright (C) 2021 星翛-STASWIT & Elicase-Team
* Based on Moclia Project & Moclia-Development-team
* ----------------------------------------------------------------------------
*	This program is free software: you can redistribute it and/or modify it
*	under the terms of the GNU Affero General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or (at your
*  option) any later version.
*
*	This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.
*	See the GNU Affero General Public License for more details.
*
*	You should have received a copy of the GNU Affero General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------
* file: MiraiBotAndInclude.h
* function: 一些需要全局引用的头文件和机器人定义
* ----------------------------------------------------------------------------
* todo: unknown
* ----------------------------------------------------------------------------
******************************************************************************/
#pragma once // 保证仅包含一次

#ifndef _ParseBotVersion_ // 如果没有定义机器人版本
#define _ParseBotVersion_  "1.0.0" // 定义机器人版本
#endif
#ifndef _BotName_ // 如果没有定义程序名称
#define _BotName_  "MocliaParseBot" // 定义程序名称
#endif
#ifndef _BotAuthor_ // 如果没有定义程序作者
#define _BotAuthor_  "Moclia-Development-Team 星翛-STASWIT" // 程序作者
#endif

// 标准库  
#include <iostream> // 标准输入输出流
#include <map> // 键值对
#include <string> // 字符串
#include <vector> // 单向队列

// 第三方库  
#include <mirai/mirai.h> // mirai-cpp

class MocliaUsingApi // 程序使用的api合集
{
public:
	class cloudMusic // 网易云音乐api
	{
	public:
		// 网易云搜索，后面加曲名
		const std::string search = 
			"http://music.163.com/api/search/pc";
		// 网易云音乐地址，后面加音乐id
		const std::string jump = 
			"https://music.163.com/#/song?id=";
		// 网易云音乐第三方播放地址，后面加音乐id
		const std::string play = 
			"http://music.163.com/song/media/outer/url?id=";
	};
	class ascii2d // ascii2d搜图API
	{
	public:
		// ascii2d.net主页，后面跟网页内联地址
		const std::string home = 
			"https://ascii2d.net";
		// ascii2d.net搜索页，后面跟图片url
		const std::string search = 
			"https://ascii2d.net/search/url/";
		// ascii2d.net颜色搜索地址，后面跟图片哈希，未使用
		const std::string color = 
			"https://ascii2d.net/search/color/";
		// ascii2d.net特征搜索地址，后面跟图片哈希
		const std::string bovw = 
			"https://ascii2d.net/search/bovw/";
	};
};