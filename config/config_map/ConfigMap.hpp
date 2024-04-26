#pragma once

#include "../ConfigReader.hpp"
#include <unordered_map>

class ConfigMap {
public:
    ConfigMap();

    static std::unordered_map<std::string, int> configMap;
};
