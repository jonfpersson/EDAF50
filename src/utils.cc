#include <vector>
#include <string>
#include "utils.hh"
#include <cctype>

std::vector<std::string> split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delim);
    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    tokens.push_back(str.substr(start, end));
    return tokens;
}

bool isDigit(const std::string &str)
{
    for (char c : str)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return !str.empty();
}

bool isValidName(const std::string &str)
{
    for (char c : str)
    {
        if (!std::isalnum(c))
        {
            return false;
        }
    }
    return !str.empty();
}

std::vector<size_t> findIndices(const std::vector<std::string> &vec, const std::string &target)
{
    std::vector<size_t> indexes;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == target)
        {
            indexes.push_back(i);
        }
    }
    return indexes;
}

std::string joinStrings(const std::vector<std::string> &strings, const std::string &separator)
{
    std::string result;
    for (size_t i = 0; i < strings.size(); ++i)
    {
        result += strings[i];
        if (i != strings.size() - 1)
        {
            result += separator;
        }
    }
    return result;
}
