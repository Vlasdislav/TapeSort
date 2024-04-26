#include <iostream>
#include "TapeSort.hpp"
#include "config/config_map/ConfigMap.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Ожидалось: ./TATLIN <INPUT_FILENAME> <OUTPUT_FILENAME>" << std::endl;
        return 1;
    }
    // Создание объекта для заполнения статического мепа кофигураций
    ConfigMap{};
    for (auto& [l, r] : ConfigMap::configMap) {
        std::cout << l << ' ' << r << std::endl;
    }

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    FileTape input_tape(input_filename);
    FileTape output_tape(output_filename);
    size_t M;
    std::cout << "Укажите сколько байт оперaтивной памяти можно использовать: ";
    std::cin >> M;

    TapeSort::sort(input_tape, output_tape, M / sizeof(int32_t));
}
