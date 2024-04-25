#pragma once

#include "Tape.hpp"
#include "FileTape.hpp"
#include "settings.hpp"
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

class TapeSort {
public:
    static void sort(Tape& input_tape, Tape& output_tape, const size_t& memory_limit) {
        const std::vector<std::string> tmp_filenames = { 
                                                        "tmp/file_1.txt",
                                                        "tmp/file_2.txt",
                                                        "tmp/file_3.txt"
                                                    };
        size_t tmp_cur_pos = 0;
        std::vector<int32_t> buffer(memory_limit);
        std::queue<std::string> queue;
        while (!input_tape.isEnd()) {
            size_t fullness_buff = 0;
            while (!input_tape.isEnd() && fullness_buff < memory_limit) {
                opt::assign(buffer[fullness_buff], input_tape.read());
                ++fullness_buff;
            }
            std::sort(buffer.begin(), buffer.begin() + fullness_buff);
            std::string new_filename = tmp_filenames[tmp_cur_pos];
            FileTape new_file_tape(new_filename);
            new_file_tape.write(buffer);
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
                std::cout << next_filename << std::endl;
            }
        }
        std::string result = queue.front();
        queue.pop();
        // TODO: copy data to `output.txt`
        input_tape.copy(result);
    }

    static void mergeTwoFiles(const std::string& lhs_filename,
                            const std::string& rhs_filename,
                            const std::string& next_filename) {
        FileTape tmp_file_tape_lhs(lhs_filename);
        FileTape tmp_file_tape_rhs(rhs_filename);
        FileTape tmp_file_tape_merged(next_filename);
        bool is_prepared_read_lhs = true;
        bool is_prepared_read_rhs = true;
        while (!tmp_file_tape_lhs.isEnd() && !tmp_file_tape_rhs.isEnd()) {
            int32_t current_element_lhs;
            int32_t current_element_rhs;
            if (is_prepared_read_lhs) {
                opt::assign(current_element_lhs, tmp_file_tape_lhs.read());
                is_prepared_read_lhs = false;
            }
            if (is_prepared_read_rhs) {
                opt::assign(current_element_rhs, tmp_file_tape_rhs.read());
                is_prepared_read_rhs = false;
            }
            if (current_element_lhs < current_element_rhs) {
                tmp_file_tape_merged.write(current_element_lhs);
                is_prepared_read_lhs = true;
                // tmp_file_tape_rhs.moveBackward();
            } else {
                tmp_file_tape_merged.write(current_element_rhs);
                is_prepared_read_rhs = true;
                // tmp_file_tape_lhs.moveBackward();
            }
        }
        while (!tmp_file_tape_lhs.isEnd()) {
            int32_t current_element_lhs;
            if (opt::assign(current_element_lhs, tmp_file_tape_lhs.read())) {
                tmp_file_tape_merged.write(current_element_lhs);
            }
        }
        while (!tmp_file_tape_rhs.isEnd()) {
            int32_t current_element_rhs;
            if (opt::assign(current_element_rhs, tmp_file_tape_rhs.read())) {
                tmp_file_tape_merged.write(current_element_rhs);
            }
        }
    }
};
