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
* file: BiliBiliParse.cpp
* function: B站视频解析
* ----------------------------------------------------------------------------
* todo: html err返回
*		b站其他有需求内容的解析
*		配置文件自定义解析内容
* ----------------------------------------------------------------------------
******************************************************************************/
#include "BilibiliParse.h"

using namespace std;
using namespace Cyan;
using namespace cpr;
using json = nlohmann::json;

MocliaUsingApi::bilibili bapi;
MocliaParseNetwork bnet;

MessageChain MocliaParseBilibili::BiliParse(std::string uoi)
{
	json res;
	MessageChain biliMessage;
	biliVideo bvideo;

	if (uoi.find(bapi.b23) == 0)
	{
		res = GetB23Json(uoi);
	}
	else if (uoi.find(bapi.bvideo) == 0)
	{
		res = getABVJson(uoi.substr(strlen(bapi.bvideo.c_str())));
	}
	else if (uoi.find("BV") == 0 || uoi.find("bv") == 0)
	{
		res = getABVJson(uoi.substr(strlen("BV")));
	}
	else if (uoi.find("AV") == 0 || uoi.find("av") == 0)
	{
		res = getABVJson(uoi.substr(strlen("av")));
	}
	else
	{
		biliMessage = MessageChain()
			.Plain("错误的解析式");
		return biliMessage;
	}

	if (res.at("code").get<int64_t>() == 0)
	{
		bvideo.aid = res.at("data").at("aid").get<int64_t>();
		bvideo.bvid = res.at("data").at("bvid").get<string>();
		bvideo.owner = res.at("data").at("owner").at("name").get<string>();
		bvideo.preview = res.at("data").at("pic").get<string>();
		bvideo.title = res.at("data").at("title").get<string>();
		bvideo.zone = res.at("data").at("tname").get<string>();

		GroupImage preview;
		preview.Url = bvideo.preview;

		biliMessage = MessageChain()
			.Plain("视频解析结果：")
			.Image(preview)
			.Plain("标题：" + bvideo.title + "\n")
			.Plain("ID：" + bvideo.bvid + "(av" + to_string(bvideo.aid) + ")\n")
			.Plain("分区：" + bvideo.zone + "\n")
			.Plain("作者：" + bvideo.owner + "\n")
			.Plain("跳转链接：" + bapi.bvideo + bvideo.bvid);

		return biliMessage;
	}
	else
	{
		biliMessage = MessageChain()
			.Plain(res.at("message").get<string>());
		return biliMessage;
	}
}

json MocliaParseBilibili::GetB23Json(string b23Url)
{
	json httpres;
	Response getRes = bnet.HttpGet(b23Url, { {"uid","123456"} });
	string url = getRes.url.str(), bvid;
	int64_t bvpos = 0, bvlength = 0;
	if (url.find(bapi.bvideo) != string::npos)
	{
		bvpos = url.find(bapi.bvideo) + strlen(bapi.bvideo.c_str());
		bvlength = url.find("?", bvpos) - bvpos;
		bvid = url.substr(bvpos, bvlength);
		httpres = getABVJson(bvid);
		return httpres;
	}
	else
	{
		throw "错误的链接";
	}

}

json MocliaParseBilibili::getABVJson(string abv)
{
	Response abvjson;
	json avjson, bvjson;

	if (isDigitAll(abv)) // 判断是不是av号
	{
		abvjson = bnet.HttpGet(
			bapi.videoView + "?aid=" + abv, { {"uid","123456"} });
		avjson = json::parse(abvjson.text);
		return avjson;
	}
	else
	{
		abvjson = bnet.HttpGet(
			bapi.videoView + "?bvid=" + abv, { {"uid","123456"} });
		bvjson = json::parse(abvjson.text);
		return bvjson;
	}
}

/*==============================================================================
*                          查询窄字节字符串是否全是数字
* ============================================================================*/
bool MocliaParseBilibili::isDigitAll(std::string str)
{
	// 检查字符串是否非空，且迭代器范围内所有数值为数字，满足条件输出true  
	bool flag =
		!str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
	// 返回判断的结果  
	return flag;
}