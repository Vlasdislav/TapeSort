#pragma once

#include <string>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <optional>

class Tape {
public:
    virtual ~Tape() = default;
    virtual std::optional<int32_t> read() = 0;
    virtual void write(const int32_t&) = 0;
    virtual void moveForward() = 0;
    virtual void moveBackward() = 0;
    virtual bool isEnd() = 0;
    virtual size_t getCurrentPos() = 0;
    virtual std::string_view getName() = 0;
};
