#pragma once

#include <cpr/cpr.h>

#include "MiraiBotAndInclude.h"

class MocliaParseNetwork
{
public:
	std::string HttpGet(string url);
	std::string HttpPost(string url, string body);
};