#pragma once

#include <optional>

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
