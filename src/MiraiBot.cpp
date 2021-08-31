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
* file: MiraiBot.cpp
* function: 处理和mirai交互的所有操作
* ----------------------------------------------------------------------------
* todo: 网易云音乐链接解析
*		b站视频解析
*		ascii2d识图
*		彩色控制台
* ----------------------------------------------------------------------------
******************************************************************************/
#include "MiraiBotAndInclude.h"
#include "About.h"
#include "CloudMusicParse.h"

using namespace std;
using namespace Cyan;

MocliaParseCloudMusic mpcm;
MocliaBotAbout mba;
MiraiBot bot;
SessionOptions opts = SessionOptions::FromJsonFile("./config.json");

int main()
{
#if defined(WIN32) || defined(_WIN32)
	system("title MocliaParseBot");
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001 & cls");
#endif
	
/*==============================================================================
*                             与miraiApiHttp建立连接
* ============================================================================*/
	while (true)
	{
		try
		{
			cout << "尝试与 mirai-api-http 建立连接..." << endl;
			bot.Connect(opts);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(1);
	}
	cout << "Bot Working..." << endl;

/*==============================================================================
*                                  群消息处理
* ============================================================================*/
	bot.On<GroupMessage>(
		[&](GroupMessage m)
		{
			try
			{
				string plain = m.MessageChain.GetPlainText();

				if (plain == "关于点歌")
				{
					string mcppVer = bot.GetMiraiCppVersion();
					string mahVer = bot.GetMiraiApiHttpVersion();
					string info = mba.botInfo(mahVer, mcppVer);
					m.Reply(MessageChain().Plain(info));
				}
				else if (plain.find("点歌") == 0)
				{
					string musicName = plain.substr(strlen("点歌"));
					MocliaParseCloudMusic::music_t musicMsg =
						mpcm.OnlySongRequest(musicName);
					if (musicMsg.error == "music not found")
					{
						m.Reply(
							MessageChain().Plain("云村中没有这首歌哟。"));
					}
					else
					{
						MusicShare share;
						share.Kind(MusicShareKind::NeteaseCloudMusic);
						share.Title(musicMsg.name);
						share.Summary(musicMsg.artist);
						share.JumUrl(musicMsg.jumpUrl);
						share.PictureUrl(musicMsg.previewUrl);
						share.MusicUrl(musicMsg.playUrl);
						share.Brief("[分享]" + musicMsg.name);
						m.Reply(MessageChain().Add<MusicShare>(share));
					}
				}

			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		});

/*==============================================================================
*                               断线自动重连
* ============================================================================*/
	bot.On<LostConnection>([&](LostConnection e)
		{
			cout << e.ErrorMessage << " (" << e.Code << ")" << endl;
			while (true)
			{
				try
				{
					cout << "尝试连接 mirai-api-http..." << endl;
					bot.Reconnect();
					cout << "与 mirai-api-http 重新建立连接!" << endl;
					break;
				}
				catch (const std::exception& ex)
				{
					cout << ex.what() << endl;
				}
				MiraiBot::SleepSeconds(1);
			}
		});

/*==============================================================================
*                                  指令系统
* ============================================================================*/
	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "exit")
		{
			// 程序结束前必须调用 Disconnect，否则 mirai-api-http 会内存泄漏。
			bot.Disconnect();
			break;
		}
	}

	return 0;
}