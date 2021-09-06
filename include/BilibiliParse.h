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
* file: BiliBiliParse.h
* function: B站视频解析相关定义
* ----------------------------------------------------------------------------
* todo: unknown
* ----------------------------------------------------------------------------
******************************************************************************/
#pragma once

#include <nlohmann/json.hpp>

#include "MiraiBotAndInclude.h"
#include "Network.h"

class MocliaParseBilibili
{
public:
	/*
	* @brief 通过B站的API进行解析
	* @param 字符串：b站的url(bilibili.com或b23.tv)或者av号/bv号
	* @return 解析完成后内容组成的消息链
	*/
	Cyan::MessageChain BiliParse(std::string uoi);
	
private:
	nlohmann::json GetB23Json(std::string b23Url);
	nlohmann::json getABVJson(std::string abv);
	bool isDigitAll(std::string str);

	struct biliVideo
	{
		std::string bvid;
		int64_t aid;
		std::string preview;
		std::string title;
		std::string owner;
		std::string zone;
	};
};