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
*		彩色控制台
* ----------------------------------------------------------------------------
******************************************************************************/
#include "MiraiBotAndInclude.h"
#include "About.h"
#include "CloudMusicParse.h"
#include "Ascii2dParse.h"

using namespace std;
using namespace Cyan;

MocliaParseCloudMusic mpcm;
MocliaBotAbout mba;
MocliaParseAscii2d ma2ds;

MiraiBot bot;
SessionOptions opts = SessionOptions::FromJsonFile("./config.json");
GID_t group;
GroupPermission gp;
map<GID_t, bool> picSearchOpen;
vector<ImageMessage> imv;
vector<QuoteMessage> qmv;

int main(int angc, char* angv[])
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

				if (plain == "关于解析")
				{
					string mcppVer = bot.GetMiraiCppVersion();
					string mahVer = bot.GetMiraiApiHttpVersion();
					string info = mba.botInfo(mahVer, mcppVer);
					m.Reply(MessageChain().Plain(info));
				}
				
				if (plain.find("点歌") == 0)
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

				if (plain == "开启识图")
				{
					group = m.Sender.Group.GID;
					gp = m.Sender.Permission;
					// 关闭了识图又想重新开启
					if (picSearchOpen.find(group) != picSearchOpen.end())
					{
						if (picSearchOpen[group])
						{
							m.Reply(
								MessageChain().Plain("本群已经开启了识图"));
						}
						else
						{
							if (gp == GroupPermission::Administrator ||
								gp == GroupPermission::Owner)
							{
								picSearchOpen[group] = true;
								m.Reply(
									MessageChain().Plain(R"(识图已开启，
请在使用过程中注意结果中可能出现的不宜内容)"));
							}
							else
							{
								m.Reply(
									MessageChain().Plain(
										"只有群主或管理员才能开启此功能"));
							}
						}
					}
					else // 全新开启识图
					{
						if (gp == GroupPermission::Administrator ||
							gp == GroupPermission::Owner)
						{
							picSearchOpen.insert(map<GID_t, bool>::value_type(m.Sender.Group.GID, true));
							m.Reply(
								MessageChain().Plain(R"(识图已开启，
请在使用过程中注意结果中可能出现的不宜内容)"));
						}
						else
						{
							m.Reply(
								MessageChain().Plain(
									"只有群主或管理员才能开启此功能"));
						}
					}
				}

				if (plain == "关闭识图")
				{
					group = m.Sender.Group.GID;
					gp = m.Sender.Permission;
					if (!picSearchOpen[group] ||
						picSearchOpen.find(group) == picSearchOpen.end())
					{
						m.Reply(
							MessageChain().Plain("识图未开启"));
					}
					else
					{
						if (gp == GroupPermission::Administrator ||
							gp == GroupPermission::Owner)
						{
							picSearchOpen[group] = false;
							m.Reply(
								MessageChain().Plain("识图已关闭"));
						}
						else
						{
							m.Reply(
								MessageChain().Plain(
									"只有群主或管理员才能关闭此功能"));
						}
					}
				}

				if (plain.find("识图") == 0 && picSearchOpen[group])
				{
					imv = m.MessageChain.GetAll<ImageMessage>();
					qmv = m.MessageChain.GetAll<QuoteMessage>();
					MocliaParseAscii2d::a2dSearch qash;
					if (!qmv.empty()) // 基于回复的识图
					{
						int64_t msgid = qmv.at(0).MessageId();
						MessageChain QuoteMegChain = 
							bot.GetGroupMessageFromId(msgid).MessageChain;
						ImageMessage quoteImageMsg = 
							QuoteMegChain.GetFirst<ImageMessage>();
						m.Reply(MessageChain().Plain("正在识图中……"));
						qash = ma2ds.picSearch(quoteImageMsg);
						m.Reply(qash.color);
						m.Reply(qash.bovw);
					}
					else if (!imv.empty()) // 基于图片尾随的识图
					{
						ImageMessage plainImageMsg = imv.at(0);
						MocliaParseAscii2d::a2dSearch pash;
						m.Reply(MessageChain().Plain("正在识图中……"));
						pash = ma2ds.picSearch(plainImageMsg);
						m.Reply(pash.color);
						m.Reply(pash.bovw);
					}
					else // 基于消息等待的识图
					{

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