#include "CloudMusicParse.h"

using namespace std;
using json = nlohmann::json;

MocliaUsingApi::cloudMusic capi;

json MocliaParseCloudMusic::getJson(string songName)
{
	MocliaParseNetwork mpn;
	json returnJson;

	returnJson = json::parse(
		mpn.HttpPost(
			capi.search, "s=" + songName + "&limit=1&type=1"));

	return returnJson;
}

MocliaParseCloudMusic::music_t MocliaParseCloudMusic::OnlySongRequest(
	string musicName)
{
	music_t music;
	json musicJson = getJson(musicName);
	json miraiapp;

	cout << musicJson << endl;

	if (musicJson.at("/result"_json_pointer).empty())
	{
		music.error = "music not found";
	}
	else
	{
		// 歌曲标题
		music.name =
			musicJson.at("/result/songs/0/name"_json_pointer).get<string>();
		// 歌曲作者
		music.artist =
			musicJson.at(
				"/result/songs/0/artists/0/name"_json_pointer).get<string>();
		// 歌曲封面链接
		music.previewUrl =
			musicJson.at(
				"/result/songs/0/album/picUrl"_json_pointer).get<string>();
		// 歌曲id
		music.id = 
			musicJson.at("/result/songs/0/id"_json_pointer).get<int64_t>();
		// 歌曲跳转链接
		music.jumpUrl = capi.jump + to_string(music.id);
		// 歌曲播放链接
		music.playUrl = capi.play + to_string(music.id) + ".mp3";
		// 错误信息
		music.error = "none";

		string brief = "[分享]" + music.name;
		
		music.musicShareJson["kind"] = "NeteaseCloudMusic";
		music.musicShareJson["title"] = music.name;
		music.musicShareJson["summary"] = music.artist;
		//music.musicShareJson["brief"] = "[分享]" + music.name;
		music.musicShareJson["brief"] = brief;
		music.musicShareJson["jumpUrl"] = music.jumpUrl;
		music.musicShareJson["musicUrl"] = music.playUrl;
		music.musicShareJson["pictureUrl"] = music.previewUrl;
	}
	return music;
}