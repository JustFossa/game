#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

json loadJson(std::string path);
