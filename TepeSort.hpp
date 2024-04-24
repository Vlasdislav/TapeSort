#pragma once

#include "Tape.hpp"
#include "FileTape.hpp"
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

class TapeSort {
public:
    static void sort(Tape& input_tape, Tape& output_tape, const size_t& memory_limit) {
        const std::vector<std::string> tmp_filenames = { "tmp/file_1.txt",
                                                    "tmp/file_2.txt",
                                                    "tmp/file_3.txt" };
        size_t tmp_cur_pos = 0;
        std::vector<int32_t> buffer(memory_limit);
        std::queue<std::string> queue;
        while (!input_tape.isEnd()) {
            size_t fullness_buff = 0;
            while (!input_tape.isEnd() && fullness_buff < memory_limit) {
                buffer[fullness_buff] = input_tape.read();
                ++fullness_buff;
            }
            std::sort(buffer.begin(), buffer.begin() + fullness_buff);
            std::string new_filename = tmp_filenames[tmp_cur_pos];
            FileTape new_file_tape(new_filename);
            std::cout << new_filename << std::endl;
            // new_file_tape.write(1);
            // new_file_tape.write(2);
            // new_file_tape.write(3);
            std::cout << new_file_tape.read() << ' ' << new_file_tape.read() << ' ' << new_file_tape.read() << std::endl;
            exit(0);
            // std::cout << "buffer: ";
            // new_file_tape.write(buffer);
            // // std::cout << "new_file_tape: ";
            // // while (!new_file_tape.isEnd()) {
            // //     std::cout << new_file_tape.read() << ' ';
            // // }
            std::cout << std::endl;
            tmp_cur_pos = (tmp_cur_pos + 1) % 3;
            queue.emplace(new_filename);
            if (queue.size() == 2) {
                std::string lhs_filename = queue.front();
                queue.pop();
                std::string rhs_filename = queue.front();
                queue.pop();
                std::string next_filename = tmp_filenames[tmp_cur_pos];
                tmp_cur_pos = (tmp_cur_pos + 1) % 3;
                mergeTwoFiles(lhs_filename, rhs_filename, next_filename);
                queue.emplace(next_filename);
            }
        }
        std::string result = queue.front();
        queue.pop();
        std::cout << result << std::endl;
        // TODO: copy()
    }

    static void mergeTwoFiles(const std::string& lhs_filename,
                            const std::string& rhs_filename,
                            const std::string& next_filename) {
        FileTape tmp_file_tape_lhs(lhs_filename);
        FileTape tmp_file_tape_rhs(rhs_filename);
        FileTape tmp_file_tape_merged(next_filename);
        while (!tmp_file_tape_lhs.isEnd() && !tmp_file_tape_rhs.isEnd()) {
            int32_t current_element_lhs = tmp_file_tape_lhs.read();
            int32_t current_element_rhs = tmp_file_tape_rhs.read();
            if (current_element_lhs < current_element_rhs) {
                tmp_file_tape_merged.write(current_element_lhs);
                // std::cout << current_element_lhs << ' ';
            } else {
                tmp_file_tape_merged.write(current_element_rhs);
                // std::cout << current_element_rhs << ' ';
            }
        }
        while (!tmp_file_tape_lhs.isEnd()) {
            int32_t current_element_lhs = tmp_file_tape_lhs.read();
            tmp_file_tape_merged.write(current_element_lhs);
            // std::cout << current_element_lhs << ' ';
        }
        while (!tmp_file_tape_rhs.isEnd()) {
            int32_t current_element_rhs = tmp_file_tape_rhs.read();
            tmp_file_tape_merged.write(current_element_rhs);
            // std::cout << current_element_rhs << ' ';
        }
        // std::cout << std::endl;
    }
};
