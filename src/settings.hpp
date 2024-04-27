#pragma once

#include <optional>
#include <functional>

using delayFunc = std::function<int()>;
using configMap = std::unordered_map<std::string, delayFunc>;

namespace opt {
    /// @brief Функция присвоения значения из типа `std::optional<T>` в переменную типа `T`
    /// @tparam T 
    /// @param lhs левый операнд - объект, которому присваивается значение
    /// @param rhs_opt правый операнд - объект, значение которого передается для присваивания
    /// @return `bool`: Получилось или не получилось присвоить значение
    template<typename T>
    bool assign(T& lhs, const std::optional<T>& rhs_opt) {
        if (rhs_opt.has_value()) {
            lhs = rhs_opt.value();
            return true;
        }
        return false;
    }
};

namespace valid {
    inline void guardInputData(const int& argc) {
        if (argc != 3) {
            std::cerr << "Ожидалось: ./TATLIN <INPUT_FILENAME> <OUTPUT_FILENAME>" << std::endl;
            exit(1);
        }
    }

    inline void guardConsoleInputData(size_t& M) {
        do {
            std::cout << "Укажите сколько байт оперaтивной памяти можно использовать (минимум 4): ";
            std::cin >> M;
        } while (M < 4);
    }
};
