#ifndef UTILS_HH
#define UTILS_HH
#include<vector>
#include<string>

std::vector<std::string> split(const std::string &str, const std::string &delim);
bool isDigit(const std::string &str);
bool isValidName(const std::string &str);

std::vector<size_t> findIndices(const std::vector<std::string>& vec, const std::string& target);
std::string joinStrings(const std::vector<std::string>& strings, const std::string& separator = "");
#endif 