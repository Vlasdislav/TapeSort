#include "ConfigMap.hpp"
#include "../../settings.hpp"
#include <vector>
#include <chrono>
#include <thread>

ConfigMap::ConfigMap() {
    std::vector<std::string> setting_names = {
        "read_delay",
        "write_delay",
        "rewind_delay",
        "shift_delay"
    };
    ConfigReader config("../config/config.txt");
    for (const auto& name : setting_names) {
        getConfigMap()[name] = [config, name]() mutable {
            int time = config.getDelay(name);
            std::chrono::milliseconds delay(time);
            std::this_thread::sleep_for(delay);
            return time;
        };
    }
}

std::unordered_map<std::string, delayFunc>& ConfigMap::getConfigMap() {
    static std::unordered_map<std::string, delayFunc> configMap;
    return configMap;
}
