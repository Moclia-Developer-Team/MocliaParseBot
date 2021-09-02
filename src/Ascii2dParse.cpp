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
* file: Ascii2dParse.cpp
* function: ascii2d.net图片解析处理
* ----------------------------------------------------------------------------
* todo: 优化getResult函数
*       封装重复性处理实现
* ----------------------------------------------------------------------------
******************************************************************************/
#include "Ascii2dParse.h" // 引用有关头文件

using namespace std; // 标准命名空间
using namespace Cyan; // mirai-cpp命名空间

MocliaUsingApi::ascii2d ma2d; // api类
MocliaParseNetwork net; // 网络访问类

/*==============================================================================
*                     通过图片地址或者哈希值获取html页面
* ============================================================================*/
string MocliaParseAscii2d::getHtml(
    const std::string& picUrlorHash, const std::string& type)
{
    if (type == "color")
    {
        string colorHtml = net.HttpGet(ma2d.search + picUrlorHash);
        return colorHtml;
    }
    else if (type == "bovw")
    {
        string bovwHtml = net.HttpGet(ma2d.bovw + picUrlorHash);
        return bovwHtml;
    }
    else
    {
        throw "error type";
    }
}

/*==============================================================================
*                          解析html页面获取需要的内容
* ============================================================================*/
MocliaParseAscii2d::a2dPic MocliaParseAscii2d::getResult(string& html)
{
    a2dPic apic;

    /*提取需要搜索的图片哈希值*/
    pdg.hashPos = 
        html.find("\'hash\'>") + strlen("\'hash\'>");
    pdg.hashLength = 
        html.find("</div>", pdg.hashPos) - pdg.hashPos;
    apic.searchHash = 
        html.substr(pdg.hashPos, pdg.hashLength);

    /*根据<hr>标签消除非图片区域*/
    pdg.hrPos = 
        html.find("<hr>") + strlen("<hr>");
    pdg.hrPos = 
        html.find("<hr>", pdg.hrPos) + strlen("<hr>");
    pdg.dataLength = 
        html.find("<hr>", pdg.hrPos) - pdg.hrPos;
    html = 
        html.substr(pdg.hrPos, pdg.dataLength);

    /*取出预览图地址*/
    pdg.previewPos = 
        html.find("src=\"") + strlen("src=\"");
    pdg.previewLength = 
        html.find("\"", pdg.previewPos) - pdg.previewPos;
    apic.preview = 
        ma2d.home + html.substr(pdg.previewPos, pdg.previewLength);

    if (html.find("yande.re") != string::npos)
    {
        yget.urlPos = 
            html.find("yande.re") - strlen("https://");
        yget.urlLength = 
            html.find("\"><", yget.urlPos) - yget.urlPos;
        apic.imouto.url = 
            html.substr(yget.urlPos, yget.urlLength);
    }
    else
    {
        apic.imouto.url.clear();
    }

    if (html.find("/assets/pixiv") != string::npos)
    {
        pget.searchPos = 
            html.find("/assets/pixiv");

        /*优化，tmd优化*/

        /*取出图片链接*/
        // 通过find找到开始位置的下标，还需加上查找字符串的长度才是需要的下标
        pget.urlPos = 
            html.find("href=\"", pget.searchPos) + strlen("href=\"");
        // 同理，随后两个下标相减得出长度
        pget.urlLength = 
            html.find("\">", pget.urlPos) - pget.urlPos;
        // 用substr从指定下标截取指定长度的字符串
        apic.pixiv.url = 
            html.substr(pget.urlPos, pget.urlLength);

        /*取出图片标题*/
        pget.titlePos = 
            html.find("\">", pget.urlPos) + strlen("\">");
        pget.titleLength = 
            html.find("</a>", pget.titlePos) - pget.titlePos;
        apic.pixiv.title = 
            html.substr(pget.titlePos, pget.titleLength);

        /*取出作者主页地址*/
        pget.authorUrlPos = 
            html.find("href=\"", pget.titlePos) + strlen("href=\"");
        pget.authorUrlLength = 
            html.find("\">", pget.authorUrlPos) - pget.authorUrlPos;
        apic.pixiv.authorUrl = 
            html.substr(pget.authorUrlPos, pget.authorUrlLength);

        /*取出作者名称*/
        pget.authorPos = 
            html.find("\">", pget.authorUrlPos) + strlen("\">");
        pget.authorLength = 
            html.find("</a>", pget.authorPos) - pget.authorPos;
        apic.pixiv.author = 
            html.substr(pget.authorPos, pget.authorLength);
    }
    else
    {
        apic.pixiv.author.clear();
        apic.pixiv.authorUrl.clear();
        apic.pixiv.title.clear();
        apic.pixiv.url.clear();
    }

    if (html.find("/assets/twitter") != string::npos)
    {
        tget.searchPos =
            html.find("/assets/twitter");

        /*取出图片链接*/
        tget.urlPos =
            html.find("href=\"", tget.searchPos) + strlen("href=\"");
        tget.urlLength =
            html.find("\">", tget.urlPos) - tget.urlPos;
        apic.twiiter.url =
            html.substr(tget.urlPos, tget.urlLength);

        /*取出图片标题*/
        tget.titlePos =
            html.find("\">", tget.urlPos) + strlen("\">");
        tget.titleLength =
            html.find("</a>", tget.titlePos) - tget.titlePos;
        apic.twiiter.title =
            html.substr(tget.titlePos, tget.titleLength);

        /*取出作者主页地址*/
        tget.authorUrlPos =
            html.find("href=\"", tget.titlePos) + strlen("href=\"");
        tget.authorUrlLength =
            html.find("\">", tget.authorUrlPos) - tget.authorUrlPos;
        apic.twiiter.authorUrl =
            html.substr(tget.authorUrlPos, tget.authorUrlLength);

        /*取出作者名称*/
        tget.authorPos = 
            html.find("\">", tget.authorUrlPos) + strlen("\">");
        tget.authorLength = 
            html.find("</a>", tget.authorPos) - tget.authorPos;
        apic.twiiter.author = 
            html.substr(tget.authorPos, tget.authorLength);
    }
    else
    {
        apic.twiiter.author.clear();
        apic.twiiter.authorUrl.clear();
        apic.twiiter.title.clear();
        apic.twiiter.url.clear();
    }

    if (html.find("/assets/niconico") != string::npos)
    {
        nget.searchPos =
            html.find("/assets/niconico");

        /*取出图片链接*/
        nget.urlPos =
            html.find("href=\"", nget.searchPos) + strlen("href=\"");
        nget.urlLength =
            html.find("\">", nget.urlPos) - nget.urlPos;
        apic.niconico.url =
            html.substr(nget.urlPos, nget.urlLength);

        /*取出图片标题*/
        nget.titlePos =
            html.find("\">", nget.urlPos) + strlen("\">");
        nget.titleLength =
            html.find("</a>", nget.titlePos) - nget.titlePos;
        apic.niconico.title =
            html.substr(nget.titlePos, nget.titleLength);

        /*取出作者主页地址*/
        nget.authorUrlPos =
            html.find("href=\"", nget.titlePos) + strlen("href=\"");
        nget.authorUrlLength =
            html.find("\">", nget.authorUrlPos) - nget.authorUrlPos;
        apic.niconico.authorUrl =
            html.substr(nget.authorUrlPos, nget.authorUrlLength);

        /*取出作者名称*/
        nget.authorPos =
            html.find("\">", nget.authorUrlPos) + strlen("\">");
        nget.authorLength =
            html.find("</a>", nget.authorPos) - nget.authorPos;
        apic.niconico.author =
            html.substr(nget.authorPos, nget.authorLength);
    }
    else
    {
        apic.niconico.author.clear();
        apic.niconico.authorUrl.clear();
        apic.niconico.title.clear();
        apic.niconico.url.clear();
    }

    return apic;
}

/*==============================================================================
*                             接收图片消息进行解析
* ============================================================================*/
MocliaParseAscii2d::a2dSearch MocliaParseAscii2d::picSearch(ImageMessage im)
{
    string html;
    a2dPic picture;
    a2dSearch res;
    GroupImage img;
    MessageChain pixivMsg, twiiterMsg, imoutoMsg, nicoMsg;

    // 构建返回消息——颜色搜索
    picture.type = "color";
    html = getHtml(im.ToMiraiImage().Url, picture.type);
    picture = getResult(html);
    img.Url = picture.preview;

    res.color = MessageChain()
        .Plain("这是颜色搜索的结果：")
        .Image(img);

    if (!picture.pixiv.title.empty())
    {
        pixivMsg = MessageChain()
            .Plain("pixiv:\n")
            .Plain("标题：" + picture.pixiv.title + "\n")
            .Plain("地址：" + picture.pixiv.url + "\n")
            .Plain("作者：" + picture.pixiv.author + "\n")
            .Plain("主页：" + picture.pixiv.authorUrl + "\n");
        res.color = res.color + pixivMsg;
    }

    if (!picture.twiiter.title.empty())
    {
        twiiterMsg = MessageChain()
            .Plain("twiiter:\n")
            .Plain("标题：" + picture.twiiter.title + "\n")
            .Plain("地址：" + picture.twiiter.url + "\n")
            .Plain("作者：" + picture.twiiter.author + "\n")
            .Plain("主页：" + picture.twiiter.authorUrl + "\n");
        res.color = res.color + twiiterMsg;
    }

    if (!picture.imouto.url.empty())
    {
        imoutoMsg = MessageChain()
            .Plain("yande.re:\n")
            .Plain("地址：" + picture.imouto.url + "\n");
        res.color = res.color + imoutoMsg;
    }

    if (!picture.niconico.title.empty())
    {
        nicoMsg = MessageChain()
            .Plain("niconico:\n")
            .Plain("标题：" + picture.niconico.title + "\n")
            .Plain("地址：" + picture.niconico.url + "\n")
            .Plain("作者：" + picture.niconico.author + "\n")
            .Plain("主页：" + picture.niconico.authorUrl + "\n");
        res.color = res.color + nicoMsg;
    }

    // 构建返回消息——特征搜索
    picture.type = "bovw";
    html = getHtml(picture.searchHash, picture.type);
    picture = getResult(html);
    img.Url = picture.preview;

    res.bovw = MessageChain()
        .Plain("这是特征搜索的结果：")
        .Image(img);

    if (!picture.pixiv.title.empty())
    {
        pixivMsg = MessageChain()
            .Plain("pixiv:\n")
            .Plain("标题：" + picture.pixiv.title + "\n")
            .Plain("地址：" + picture.pixiv.url + "\n")
            .Plain("作者：" + picture.pixiv.author + "\n")
            .Plain("主页：" + picture.pixiv.authorUrl + "\n");
        res.bovw = res.bovw + pixivMsg;
    }

    if (!picture.twiiter.title.empty())
    {
        twiiterMsg = MessageChain()
            .Plain("twiiter:\n")
            .Plain("标题：" + picture.twiiter.title + "\n")
            .Plain("地址：" + picture.twiiter.url + "\n")
            .Plain("作者：" + picture.twiiter.author + "\n")
            .Plain("主页：" + picture.twiiter.authorUrl + "\n");
        res.bovw = res.bovw + twiiterMsg;
    }

    if (!picture.imouto.url.empty())
    {
        imoutoMsg = MessageChain()
            .Plain("yande.re:\n")
            .Plain("地址：" + picture.imouto.url + "\n");
        res.bovw = res.bovw + imoutoMsg;
    }

    if (!picture.niconico.title.empty())
    {
        nicoMsg = MessageChain()
            .Plain("niconico:\n")
            .Plain("标题：" + picture.niconico.title + "\n")
            .Plain("地址：" + picture.niconico.url + "\n")
            .Plain("作者：" + picture.niconico.author + "\n")
            .Plain("主页：" + picture.niconico.authorUrl + "\n");
        res.bovw = res.bovw + nicoMsg;
    }

    return res;
}