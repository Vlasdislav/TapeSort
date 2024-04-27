#include "ConfigMap.hpp"
#include "settings.hpp"
#include <chrono>
#include <thread>

ConfigMap::ConfigMap() {
    ConfigReader config(CONFIG_FILE_PATH);
    for (const auto& name : setting_names) {
        getConfigMap()[name] = [config, name]() mutable {
            int time = config.getDelay(name);
            std::chrono::milliseconds delay(time);
            std::this_thread::sleep_for(delay);
            return time;
        };
    }
}

configMap& ConfigMap::getConfigMap() {
    static configMap configMap;
    return configMap;
}
