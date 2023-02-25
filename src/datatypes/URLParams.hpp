#ifndef URL_PARAMS_HPP
#define URL_PARAMS_HPP

#include <unordered_map>
#include <string>

class URLParams
{
private:
    std::unordered_map<std::string, std::string> params;
    std::string rawUrl;
    
public:
    URLParams(const std::string &url_);
    ~URLParams();

    std::string     path();
    std::string     getParam(const char *name);

private:
    void            parse();
};

#endif
