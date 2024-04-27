#pragma once

#include "ConfigReader.hpp"
#include "settings.hpp"
#include <unordered_map>
#include <vector>

class ConfigMap {
public:
    ConfigMap();

    static configMap& getConfigMap();

    std::vector<std::string> setting_names = {
        "read_delay",
        "write_delay",
        "rewind_delay",
        "shift_delay"
    };
};
