#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <optional>

class Tape {
public:
    virtual ~Tape() = default;
    virtual std::optional<int32_t> read() = 0;
    virtual void write(int32_t) = 0;
    virtual void write(const std::vector<int32_t>&) = 0;
    virtual void moveForward() = 0;
    virtual void moveBackward() = 0;
    virtual bool isEnd() = 0;
    virtual size_t getCurrentPos() = 0;
    virtual bool copy(const std::string&) = 0;
};
