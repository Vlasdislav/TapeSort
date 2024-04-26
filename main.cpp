#include <iostream>
#include "TapeSort.hpp"
#include "config/config_map/ConfigMap.hpp"
#include "settings.hpp"

int main(int argc, char** argv) {
    valid::guardInputData(argc);

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    FileTape input_tape(input_filename);
    FileTape output_tape(output_filename);

    size_t M;
    valid::guardConsoleInputData(M);

    // Создание объекта для заполнения статического мепа кофигураций
    ConfigMap{};

    TapeSort::sort(input_tape, output_tape, M / sizeof(int32_t));
}
