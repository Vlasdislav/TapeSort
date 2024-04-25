#include <iostream>
#include "TapeSort.hpp"

// -10 0 12 12 -1 12 -1 -11 100 1000 1

int main() {
    FileTape file1("files/input.txt");
    FileTape file2("files/output.txt");
    TapeSort::sort(file1, file2, 1);
}
