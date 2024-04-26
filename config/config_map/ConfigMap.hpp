#pragma once

#include "../ConfigReader.hpp"
#include <unordered_map>
#include "../../settings.hpp"

class ConfigMap {
public:
    ConfigMap();

    static std::unordered_map<std::string, delayFunc>& getConfigMap();
};
