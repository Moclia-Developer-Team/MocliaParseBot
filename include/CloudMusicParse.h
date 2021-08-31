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

	// �����ĵ��  
	music_t OnlySongRequest(std::string musicName);

private:
	// �������Ƶ�url�л�ȡjson  
	nlohmann::json getJson(std::string songName);
};