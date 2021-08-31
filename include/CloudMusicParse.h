#pragma once

#include "MiraiBotAndInclude.h"
#include "JsonParse.h"
#include "Network.h"

class MocliaParseCloudMusic
{
public:

	typedef struct music_t
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