#pragma once

#include "Tape/FileTape.hpp"
#include "settings.hpp"
#include <string>
#include <algorithm>

class TapeSort {
public:
    static void sort(Tape& input_tape, Tape& output_tape, const size_t& buffer_size) {
        system("mkdir tmp");
        std::vector<int> buffer(buffer_size);
        int chunk_num = 0;
        while (!input_tape.isEmpty() && !input_tape.isEnd()) {
            size_t i = 0;
            for (; i < buffer_size && !input_tape.isEmpty() && !input_tape.isEnd(); ++i) {
                opt::assign(buffer[i], input_tape.read());
            }
            std::sort(buffer.begin(), buffer.begin() + i);
            std::string chunk_filename = "tmp/chunk_" + std::to_string(chunk_num++) + ".txt";
            FileTape chunk(chunk_filename);
            for (size_t j = 0; j < i; ++j) {
                chunk.write(buffer[j]);
            }
        }
        while (chunk_num > 1) {
            std::string chunk_filename_1 = "tmp/chunk_" + std::to_string(chunk_num - 2) + ".txt";
            std::string chunk_filename_2 = "tmp/chunk_" + std::to_string(chunk_num - 1) + ".txt";
            std::string temp_filename = "tmp/temp_chunk.txt";
            mergeTwoFiles(chunk_filename_1, chunk_filename_2, temp_filename);
            remove(chunk_filename_1.data());
            remove(chunk_filename_2.data());
            rename(temp_filename.data(), ("tmp/chunk_" + std::to_string(chunk_num - 2) + ".txt").data());
            --chunk_num;
        }
        rename("tmp/chunk_0.txt", output_tape.getName().data());
        system("rm -r tmp");
    }

    static void mergeTwoFiles(const std::string& lhs_filename,
                                const std::string& rhs_filename,
                                const std::string& output_filename) {
        FileTape lhs_tape(lhs_filename);
        FileTape rhs_tape(rhs_filename);
        FileTape output_tape(output_filename);
        int32_t num_1;
        opt::assign(num_1, lhs_tape.read());
        int32_t num_2;
        opt::assign(num_2, rhs_tape.read());
        while (lhs_tape.good() && rhs_tape.good()) {
            if (num_1 < num_2) {
                output_tape.write(num_1);
                opt::assign(num_1, lhs_tape.read());
            } else {
                output_tape.write(num_2);
                opt::assign(num_2, rhs_tape.read());
            }
        }
        while (lhs_tape.good()) {
            output_tape.write(num_1);
            opt::assign(num_1, lhs_tape.read());
        }
        while (rhs_tape.good()) {
            output_tape.write(num_2);
            opt::assign(num_2, rhs_tape.read());
        }
    }
};
