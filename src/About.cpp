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
* file: About.cpp
* function: 程序关于页的实现
* ----------------------------------------------------------------------------
* todo: unknown
* ----------------------------------------------------------------------------
******************************************************************************/
#include "About.h"

using namespace std;

string MocliaBotAbout::botInfo(std::string mahVer, std::string mcppVer)
{
	programMessage prog;
#ifdef _MSC_VER
	prog.complier = "MSVC " + to_string(_MSC_VER);
#ifdef _M_AMD64
	prog.compliePlatform = "windows x64 ";
#elif _M_IX86
	prog.compliePlatform = "windows x86 ";
#elif _M_ARM
#ifdef _M_ARM64
	prog.compliePlatform = "windows aarch64 ";
#else
	prog.compliePlatform = "windows arm ";
#endif // _M_ARM64
#endif // _M_AMD64
#endif // _MSC_VER

#ifdef __GNUC__
	prog.complier = "GNUC ";
	prog.complier += __VERSION__;
#ifdef __x86_64
	prog.compliePlatform = "linux x86_64 ";
#elif __aarch64__
	prog.compliePlatform = "linux aarch64 ";
#else
	prog.compliePlatform = "linux arm ";
#endif
#endif

#ifdef _DEBUG
	prog.progType = "debug";
#else
	prog.progType = "release";
#endif // _DEBUG

	prog.complieDate = __DATE__;
	prog.complieTime = __TIME__;
	prog.supportPlatform = "mirai oicq]";
	prog.mahVer = mahVer;
	prog.miraicppVer = mcppVer;
	prog.progName = _BotName_;
	prog.progAuthor = _BotAuthor_;
	prog.progVer = _ParseBotVersion_;

	string out = prog.progName + " by " + prog.progAuthor + " Ver "
		+ prog.progVer + " " + prog.progType + "\n"
		+ "Complied by " + "[" + prog.complier + " " + prog.complieDate
		+ " " + prog.complieTime + "]\n"
		+ "Platform [" + prog.compliePlatform + " "
		+ prog.supportPlatform + "\n"
		+ "Using [mirai-cpp version " + prog.miraicppVer + "]\n"
		+ "Connecting [Mirai-API-Http version " + mahVer + "]\n"
		+ "命令列表：\n"
		+ "关于解析 —— 本插件帮助列表\n"
		+ "点歌[歌名] —— 在网易云平台进行点歌\n"
		+ "开启识图 —— 在本群开启识图功能（仅群主或管理）\n"
		+ "关闭识图 —— 在本群关闭识图功能（仅群主或管理）\n"
		+ "[回复内容]识图 —— 识别回复内容中的第一张图\n"
		+ "识图[图片] —— 识别图片";

	return out;
}