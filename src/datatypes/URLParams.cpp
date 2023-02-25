#include "URLParams.hpp"

#define PATH_STRING "path"

using std::string;

URLParams::URLParams(const std::string &url_) : rawUrl(url_)
{
    parse();
}

URLParams::~URLParams()
{
}

void    URLParams::parse()
{
    size_t pathStart = rawUrl.find("/");
    size_t questMark = rawUrl.find("?");
    if (pathStart == string::npos)
        return;
    string path = rawUrl.substr(pathStart, questMark - pathStart);
    params.emplace(PATH_STRING, path);

    size_t paramStart = questMark;
    do 
    {
        paramStart += 1;
        size_t eqSign = rawUrl.find("=", paramStart);
        size_t paramDelim = rawUrl.find("&", paramStart);
        if (eqSign == string::npos)
            break;
        string name = rawUrl.substr(paramStart, eqSign - paramStart);
        string value = rawUrl.substr(eqSign + 1, paramDelim - eqSign - 1);
        params.emplace(name, value);
        paramStart = rawUrl.find("&", paramStart);
    } while (paramStart != string::npos);
}

std::string     URLParams::path()
{
    return getParam(PATH_STRING);
}

std::string     URLParams::getParam(const char *name)
{
    auto it = params.find(name);
    if (it == params.end())
        return "";
    return it->second;
}