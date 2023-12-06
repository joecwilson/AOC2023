#include <vector>
#include <string>

std::vector<std::string> string_split(std::string string, std::string delimiter)
{
    std::vector<std::string> ret;
    size_t pos = 0;
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) 
    {
        token = string.substr(0, pos);
        string.erase(0, pos + delimiter.length());
        ret.push_back(token);
    }
    return ret;
}