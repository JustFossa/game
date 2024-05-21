#ifndef JSON_H
#define JSON_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

json loadJson(std::string path);

#endif // JSON_H