#include "json.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

json loadJson(std::string path)

{
    std::ifstream inputFile(path);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        exit(1);
    }
    json data;
    inputFile >> data;
    inputFile.close();
    return data;
}