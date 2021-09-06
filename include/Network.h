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
* file: Network.h
* function: 网络访问的相关定义
* ----------------------------------------------------------------------------
* todo: unknown
* ----------------------------------------------------------------------------
******************************************************************************/
#pragma once

#include <cpr/cpr.h>

#include "MiraiBotAndInclude.h"

class MocliaParseNetwork
{
public:
	std::string HttpGet(std::string url);
	cpr::Response HttpGet(std::string url, std::map<std::string, std::string> sendCookies);
	std::string HttpPost(std::string url, std::string body);
};