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
* file: CloudMusicParse.h
* function: 网易云音乐解析的有关定义
* ----------------------------------------------------------------------------
* todo: 网易云音乐链接解析
* ----------------------------------------------------------------------------
******************************************************************************/
#pragma once

#include "MiraiBotAndInclude.h"
#include "Network.h"

class MocliaParseCloudMusic
{
public:

	struct music_t
	{
		std::string name;
		std::string artist;
		std::string previewUrl;
		int64_t id = 0;
		std::string jumpUrl;
		std::string playUrl;
		std::string error;
	};

	// 单纯的点歌  
	music_t OnlySongRequest(std::string musicName);

private:
	// 从网易云的url中获取json  
	nlohmann::json getJson(std::string songName);
};