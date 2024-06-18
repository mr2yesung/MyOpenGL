#include "FileBrowser.h"

#include <Windows.h>

const std::string FileBrowser::BrowseFiles(const char* filter, const char* extension)
{
    // ANSI format
    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    char fileName[MAX_PATH] = "";

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    ofn.lpstrDefExt = extension;

    std::string filePath;

    if (GetOpenFileNameA(&ofn))
    {
        filePath = fileName;
    }

    // if the browser was closed without properly selecting the file, filePath will be empty
    return filePath;
}