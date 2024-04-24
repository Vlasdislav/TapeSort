#include <iostream>
#include "FileTape.hpp"
#include "TepeSort.hpp"

int main() {
    FileTape input_file(INPUT_FILE_PATH);
    FileTape output_file(OUTPUT_FILE_PATH);
    // while (!input_file.isEnd()) {
    //     output_file.write(input_file.read());
    // }
    // TapeSort::sort(input_file, output_file, 2);
    std::ifstream in("tmp/file_1.txt");
    std::ofstream out("tmp/file_2.txt");
    if (in.is_open() && out.is_open()) {
        std::cout << "Good!\n";
        out << 1;
        std::cout << 1;
        int32_t s;
        while (in >> s) {
            std::cout << s << ' ';
            out << s << ' ';
        }
        std::cout << std::endl;
        in.close();
        out.close();
    } else {
        std::cout << "Bad!\n";
    }

    // int a;
    // in >> a;
    // std::cout << a << std::endl;
    // for (int i = 0; i < 10; ++i) {
    //     std::cout << in.read() << ' ';
    // }
    // std::cout << "Hello, world!1" << std::endl;
    // FileTape input_file("files/input.txt");
    // std::cout << "Hello, world!2" << std::endl;
    // FileTape output_file("files/output.txt");
    // std::cout << "Hello, world!3" << std::endl;
    // std::cout << input_file.isEnd() << std::endl;
    // // std::cout << output_file.isEnd() << std::endl;
    // // output_file.write(1);
    // // std::cout << output_file.read() << ' ' << output_file.isEnd() << std::endl;
    // TapeSort::sort(input_file, output_file, 2);
    // std::cout << "Hello, world!4" << std::endl;
}
