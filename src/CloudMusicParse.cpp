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
* file: CloudMusicParse.cpp
* function: 网易云音乐解析实现
* ----------------------------------------------------------------------------
* todo: 网易云音乐链接解析
* ----------------------------------------------------------------------------
******************************************************************************/
#include "CloudMusicParse.h"

using namespace std;
using json = nlohmann::json;

MocliaUsingApi::cloudMusic capi;

json MocliaParseCloudMusic::getJson(string songName)
{
	MocliaParseNetwork mpn;
	json returnJson;

	returnJson = json::parse(
		mpn.HttpPost(
			capi.search, "s=" + songName + "&limit=1&type=1"));

	return returnJson;
}

MocliaParseCloudMusic::music_t MocliaParseCloudMusic::OnlySongRequest(
	string musicName)
{
	music_t music;
	json musicJson = getJson(musicName);
	json miraiapp;

	//cout << musicJson << endl;

	if (musicJson.at("/result"_json_pointer).empty())
	{
		music.error = "music not found";
	}
	else
	{
		// 歌曲标题
		music.name =
			musicJson.at("/result/songs/0/name"_json_pointer).get<string>();
		// 歌曲作者
		music.artist =
			musicJson.at(
				"/result/songs/0/artists/0/name"_json_pointer).get<string>();
		// 歌曲封面链接
		music.previewUrl =
			musicJson.at(
				"/result/songs/0/album/picUrl"_json_pointer).get<string>();
		// 歌曲id
		music.id = 
			musicJson.at("/result/songs/0/id"_json_pointer).get<int64_t>();
		// 歌曲跳转链接
		music.jumpUrl = capi.jump + to_string(music.id);
		// 歌曲播放链接
		music.playUrl = capi.play + to_string(music.id) + ".mp3";
		// 错误信息
		music.error = "none";
	}
	return music;
}