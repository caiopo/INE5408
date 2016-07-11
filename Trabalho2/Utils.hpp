#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

std::string exec(const char* cmd);
std::string exec(const std::string cmd);

void cat(const std::string filename);

std::string readwhole(const std::string filename);

std::vector<std::string> ls(std::string path);

std::vector<std::string> split(const std::string& str, char delim);


#endif  // UTILS_HPP