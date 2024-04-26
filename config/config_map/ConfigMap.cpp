#include "ConfigMap.hpp"
#include <vector>

std::unordered_map<std::string, int> ConfigMap::configMap;

ConfigMap::ConfigMap() {
    std::vector<std::string> setting_names = {
        "read_delay",
        "write_delay",
        "rewind_delay",
        "shift_delay"
    };
    ConfigReader config("../config/config.txt");
    for (auto& name : setting_names) {
        configMap[name] = config.getDelay(name);
    }
}
