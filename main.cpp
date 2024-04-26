#include <iostream>
#include "TapeSort.hpp"

int main(int argc, char** argv) {
    std::cout << argc << std::endl;
    if (argc != 3) {
        std::cerr << "Ожидалось: ./TATLIN <INPUT_FILENAME> <OUTPUT_FILENAME>" << std::endl;
        return 1;
    }
    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    FileTape input_tape(input_filename);
    FileTape output_tape(output_filename);
    int M;
    std::cout << "Укажите сколько байт оперaтивной памяти можно использовать: ";
    std::cin >> M;
    TapeSort::sort(input_tape, output_tape, M / sizeof(int32_t));
}
