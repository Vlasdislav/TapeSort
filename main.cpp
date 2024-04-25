#include <iostream>
#include "FileTape.hpp"
#include "TepeSort.hpp"
#include "settings.hpp"

// 18 0 -13 2 1023 -30

int main() {
    FileTape input_file("./files/input.txt");
    FileTape output_file("./files/output.txt");
    // std::vector<int32_t> aa;
    // while (!input_file.isEnd()) {
    //     int32_t a;
    //     opt::assign(a, input_file.read());
    //     aa.emplace_back(a);
    //     // output_file.write(a);
    // }
    // std::sort(aa.begin(), aa.end());
    // // output_file.write(aa);
    // // std::cout << std::endl;
    // input_file.resetCurrentPos();
    TapeSort::sort(input_file, output_file, 2);
    std::string lol;
    if (std::cin >> lol) {
        system("bash clear_files.sh");
    }
}
