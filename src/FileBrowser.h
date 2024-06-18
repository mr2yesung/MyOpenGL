#pragma once

#include <string>

class FileBrowser {
public:
	static const std::string BrowseFiles(const char* filter, const char* extension);
};