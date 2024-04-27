#pragma once

#include "Tape.hpp"
#include "ConfigMap.hpp"
#include <fstream>

class FileTape final : public Tape {
public:
    explicit FileTape(const std::string& io_filename)
                    : io_filename_(io_filename), current_pos_(0) {
        io_file_.open(io_filename, std::ios::in | std::ios::out);
        if (!io_file_.is_open()) {
            std::ofstream temp_file(io_filename);
            temp_file.close();
            io_file_.open(io_filename, std::ios::in | std::ios::out);
            if (!io_file_.is_open()) {
                throw std::ifstream::failure("Неудалось открыть файл `" + io_filename + "`");
            }
        }
    }
    
    ~FileTape() {
        io_file_.close();
    }

    std::optional<int32_t> read() override {
        if (isEmpty() || isEnd()) {
            return std::nullopt;
        }
        int32_t num;
        ConfigMap::getConfigMap()["read_delay"]();
        if (io_file_ >> num) {
            io_file_.flush();
            moveForward();
            return num;
        }
        return std::nullopt;
    }

    void write(const int32_t& num) override {
        ConfigMap::getConfigMap()["write_delay"]();
        if (io_file_ << num << ' ') {
            io_file_.flush();
            moveForward();
        }
    }

    void moveForward() override {
        ConfigMap::getConfigMap()["shift_delay"]();
        ++current_pos_;
        // io_file_.seekg(current_pos_ * sizeof(int32_t));
        // io_file_.seekp(current_pos_ * sizeof(int32_t));
    }

    void moveBackward() override {
        ConfigMap::getConfigMap()["rewind_delay"]();
        --current_pos_;
        // io_file_.seekg(current_pos_ * sizeof(int32_t));
        // io_file_.seekp(current_pos_ * sizeof(int32_t));
    }

    size_t getCurrentPos() override {
        return current_pos_;
    }

    bool isEnd() override {
        return io_file_.eof();
    }

    bool good() override {
        return static_cast<bool>(io_file_);
    }

    bool isEmpty() override {
        return io_file_.peek() == EOF;
    }

    std::string_view getName() override {
        return io_filename_;
    }
private:
    std::fstream io_file_;
    std::string io_filename_;
    size_t current_pos_;
};
