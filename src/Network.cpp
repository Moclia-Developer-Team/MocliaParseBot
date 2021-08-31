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