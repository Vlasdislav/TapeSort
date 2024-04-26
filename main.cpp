#include <iostream>
#include "TapeSort.hpp"
#include "config/ConfigReader.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Ожидалось: ./TATLIN <INPUT_FILENAME> <OUTPUT_FILENAME>" << std::endl;
        return 1;
    }

    ConfigReader config("./config/config.txt");
    int readDelay = config.getDelay("read_delay");
    int writeDelay = config.getDelay("write_delay");
    int rewindDelay = config.getDelay("rewind_delay");
    int shiftDelay = config.getDelay("shift_delay");
    std::cout << "Read Delay: " << readDelay << "ms\n";
    std::cout << "Write Delay: " << writeDelay << "ms\n";
    std::cout << "Rewind Delay: " << rewindDelay << "ms\n";
    std::cout << "Shift Delay: " << shiftDelay << "ms\n";

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    FileTape input_tape(input_filename);
    FileTape output_tape(output_filename);
    int M;
    std::cout << "Укажите сколько байт оперaтивной памяти можно использовать: ";
    std::cin >> M;

    TapeSort::sort(input_tape, output_tape, M / sizeof(int32_t));
}
