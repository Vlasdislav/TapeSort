#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class ConfigReader {
public:
    ConfigReader(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                size_t pos = line.find('=');
                if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos - 1);
                    int value = std::stoi(line.substr(pos + 1));
                    configValues[key] = value;
                }
            }
            file.close();
        } else {
            std::cerr << "Не удается открыть конфигурационный файл: " << filename << std::endl;
        }
    }

    int getDelay(const std::string& key) const {
        auto it = configValues.find(key);
        if (it != configValues.end()) {
            return it->second;
        } else {
            std::cerr << "Ключ не найден в конфигурационном файле: " << key << std::endl;
            return -1;
        }
    }
private:
    std::unordered_map<std::string, int> configValues;
};
