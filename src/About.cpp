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
		+ "关于点歌 —— 本插件帮助列表\n"
		+ "点歌[歌名] —— 在网易云平台进行点歌";

	return out;
}