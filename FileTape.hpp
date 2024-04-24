#pragma once

#include "Tape.hpp"
#include <fstream>
#include <vector>

class FileTape final : public Tape {
public:
    explicit FileTape(const std::string& io_filename) {
        io_file_.open(io_filename, std::ios::in | std::ios::out);
        if (!io_file_.is_open()) {
            throw std::ifstream::failure("Неудалось открыть файл `" + io_filename + "`");
        }
        io_file_.clear(); // !!!
        current_pos_ = 0;
    }

    ~FileTape() override {
        io_file_.close();
    }

    int32_t read() override {
        int32_t num;
        // io_file_.read(reinterpret_cast<char*>(&num), sizeof(int32_t));
        io_file_ >> num;
        return num;
    }

    void write(const int32_t num) override {
        // io_file_.write(reinterpret_cast<const char*>(&num), sizeof(int32_t));
        io_file_ << num << ' ';
    }

    void write(const std::vector<int32_t>& vec) {
        std::cout << "\nwrite: ";
        for (auto& num : vec) {
            // write(num);
            io_file_ << num << ' ';
            std::cout << num << ' ';
        }
        std::cout << std::endl;
    }

    void moveForward() override {
        // if (isEnd()) {
        //     throw std::out_of_range("moveForward: Выход за границы ленты");
        // }
        ++current_pos_;
        io_file_.seekg(current_pos_ * sizeof(int32_t), std::ios::beg);
    }

    void moveBackward() override {
        if (current_pos_ == 0) {
            throw std::out_of_range("moveBackward: Выход за границы ленты");
        }
        --current_pos_;
        io_file_.seekg(current_pos_ * sizeof(int32_t), std::ios::beg);
    }

    bool isEnd() override {
        return io_file_.eof();
    }

    size_t getCurrentPos() override {
        return current_pos_;
    }
private:
    std::fstream io_file_;
    size_t current_pos_;
};





// #pragma once
//
// #include "Tape.hpp"
// #include <fstream>
//
// class FileTape : public Tape {
// public:
//     FileTape(const std::string& input_filename,
//             const std::string& output_filename) {
//         input_file_.open(input_filename, std::ios::binary);
//         output_file_.open(output_filename, std::ios::binary);
//         current_pos_ = 0;
//     }
//
//     ~FileTape() override {
//         input_file_.close();
//         output_file_.close();
//     }
//
//     int32_t read() override {
//         int32_t num;
//         input_file_.read(reinterpret_cast<char*>(&num), sizeof(int32_t));
//         return num;
//     }
//
//     void write(const int32_t num) override {
//         output_file_.write(reinterpret_cast<const char*>(&num), sizeof(int32_t));
//     }
//
//     void moveForward() override {
//         if (isEnd()) {
//             throw std::logic_error("moveForward: Выход за границы ленты");
//         }
//         ++current_pos_;
//         input_file_.seekg(current_pos_ * sizeof(int32_t), std::ios::beg);
//     }
//
//     void moveBackward() override {
//         if (current_pos_ == 0) {
//             throw std::logic_error("moveBackward: Выход за границы ленты");
//         }
//         --current_pos_;
//         input_file_.seekg(current_pos_ * sizeof(int32_t), std::ios::beg);
//     }
//
//     bool isEnd() override {
//         return input_file_.eof();
//     }
// private:
//     std::ifstream input_file_;
//     std::ofstream output_file_;
//     size_t current_pos_;
// };
