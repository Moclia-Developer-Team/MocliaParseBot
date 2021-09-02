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
* file: Network.cpp
* function: 处理网络请求
* ----------------------------------------------------------------------------
* todo: 添加状态码判断
*		添加代理
*		添加cookie
* ----------------------------------------------------------------------------
******************************************************************************/
#include "Network.h"

using namespace std;
using namespace cpr;

string MocliaParseNetwork::HttpGet(string url)
{
	try
	{
		Response URLGet = Get(Url{ url });
		return URLGet.text;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
}

string MocliaParseNetwork::HttpPost(string url, string body)
{
	try
	{
		Response URLPost = Post(Url{ url }, Body{ body });
		return URLPost.text;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
}