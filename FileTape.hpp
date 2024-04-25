#pragma once

#include "Tape.hpp"
#include <fstream>

class FileTape final : public Tape {
public:
    explicit FileTape(const std::string& io_filename) : current_pos_(0) {
        io_file_.open(io_filename, std::ios::in | std::ios::out);
        if (!io_file_.is_open()) {
            throw std::ifstream::failure("Неудалось открыть файл `" + io_filename + "`");
        }
        io_file_.clear();
    }

    ~FileTape() override {
        io_file_.close();
    }

    std::optional<int32_t> read() override {
        if (isEmpty() || isEnd()) {
            return std::nullopt;
        }
        int32_t num;
        if (io_file_ >> num) {
            io_file_.flush();
            moveForward();
            return num;
        }
        return std::nullopt;
    }

    void write(const int32_t num) override {
        if (io_file_ << num << ' ') {
            io_file_.flush();
            moveForward();
        }
    }

    void write(const std::vector<int32_t>& vec) override {
        for (auto& num : vec) {
            write(num);
        }
    }

    void moveForward() override {
        ++current_pos_;
    }

    void moveBackward() override {
        if (current_pos_ == 0) {
            throw std::out_of_range("moveBackward: Выход за границы ленты");
        }
        --current_pos_;
    }

    bool isEnd() override {
        return io_file_.eof();
    }

    bool isEmpty() {
        return io_file_.peek() == EOF;
    }

    size_t getCurrentPos() override {
        return current_pos_;
    }

    bool copy(const std::string& source_filename) override {
        std::ifstream source_file(source_filename);
        if (!source_file.is_open()) {
            std::cerr << "Невозможно открыть файл: `" << source_filename << "`" << std::endl;
            return false;
        }
        if (source_file.peek() != EOF) {
            io_file_ << source_file.rdbuf();
            io_file_.flush();
            source_file.close();
        }
        return true;
    }
private:
    std::fstream io_file_;
    size_t current_pos_;
};
