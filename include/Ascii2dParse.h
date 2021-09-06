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
* file: Ascii2dParse.h
* function: 有关Ascii2d解析的一些定义
* ----------------------------------------------------------------------------
* todo: 优化结构
* ----------------------------------------------------------------------------
******************************************************************************/
#pragma once
#include "MiraiBotAndInclude.h"
#include "Network.h"

class MocliaParseAscii2d
{
public:
	struct pixiv_t
	{
		std::string url;
		std::string title;
		std::string author;
		std::string authorUrl;
	};

	struct twiiter_t
	{
		std::string url;
		std::string title;
		std::string author;
		std::string authorUrl;
	};

	struct imouto_t
	{
		std::string url;
	};

	struct niconico_t
	{
		std::string url;
		std::string title;
		std::string author;
		std::string authorUrl;
	};

	struct a2dPic
	{
		std::string type; // 图片搜索的类型：颜色搜索，特征搜索  
		std::string searchHash; // 用作搜索的图片哈希值
		std::string preview; // 预览图  
		pixiv_t pixiv;
		twiiter_t twiiter;
		imouto_t imouto;
		niconico_t niconico;
	};

	struct a2dSearch
	{
		Cyan::MessageChain color;
		Cyan::MessageChain bovw;
	};

	/*
	* @brief 使用Ascii2d将传入的图片进行搜索
	* @param 图片消息(ImageMessage)
	* @return 结构体a2dSearch，包含颜色识别结果和特征识别结果两个消息链
	*/
	a2dSearch picSearch(Cyan::ImageMessage im);

private:
	std::string getHtml(const std::string& hash, const std::string& type);
	a2dPic getResult(std::string& html);

	struct picDateGet
	{
		int64_t hashPos; // 被搜索图片的哈希值开始位置
		int64_t hashLength; // 被搜索图片的哈希值长度

		int64_t hrPos; // 第一个hr的位置
		int64_t dataLength; // 需要的数据长度

		int64_t previewPos; // 预览图链接位置
		int64_t previewLength; // 预览图链接长度
	} pdg;

	struct pixivGet
	{
		int64_t searchPos; // 开始搜索的位置

		int64_t urlPos; // 图片链接开始位置
		int64_t urlLength; // 图片链接长度

		int64_t titlePos; // 图片标题开始位置
		int64_t titleLength; // 图片标题长度

		int64_t authorUrlPos; // 作者主页链接开始位置
		int64_t authorUrlLength; // 作者主页链接长度

		int64_t authorPos; // 作者名称开始位置
		int64_t authorLength; // 作者名称长度
	} pget;

	struct twiiterGet
	{
		int64_t searchPos; // 开始搜索的位置

		int64_t urlPos; // 图片链接开始位置
		int64_t urlLength; // 图片链接长度

		int64_t titlePos; // 图片标题开始位置
		int64_t titleLength; // 图片标题长度

		int64_t authorUrlPos; // 作者主页链接开始位置
		int64_t authorUrlLength; // 作者主页链接长度

		int64_t authorPos; // 作者名称开始位置
		int64_t authorLength; // 作者名称长度
	} tget;

	struct imoutoGet
	{
		int64_t urlPos; // 图片链接开始位置
		int64_t urlLength; // 图片链接长度
	} yget;

	struct niconicoGet
	{
		int64_t searchPos; // 开始搜索的位置

		int64_t urlPos; // 图片链接开始位置
		int64_t urlLength; // 图片链接长度

		int64_t titlePos; // 图片标题开始位置
		int64_t titleLength; // 图片标题长度

		int64_t authorUrlPos; // 作者主页链接开始位置
		int64_t authorUrlLength; // 作者主页链接长度

		int64_t authorPos; // 作者名称开始位置
		int64_t authorLength; // 作者名称长度
	} nget;
};