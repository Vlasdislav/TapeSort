#include "FileTape.hpp"
#include "ConfigMap.hpp"
#include "settings.hpp"
#include <gtest/gtest.h>

TEST(FileTape, Constructor) {
    ConfigMap{};
    try {
        FileTape ft("");
        EXPECT_FALSE(true);
    } catch(const std::exception& e) {
        EXPECT_TRUE(true);
    }
    std::string ft_name = "files/ctr.txt";
    FileTape ft(ft_name);
    EXPECT_EQ(ft.getName(), ft_name);
    EXPECT_EQ(ft.getCurrentPos(), 0);
}

TEST(FileTape, move) {
    
}

TEST(FileTape, write) {
    std::string ft_name = "files/write.txt";
    FileTape ft(ft_name);
    EXPECT_EQ(ft.getCurrentPos(), 0);
    ft.write(1);
    EXPECT_EQ(ft.getCurrentPos(), 1);
    int32_t a = 0;
    ft.moveBackward();
    opt::assign(a, ft.read());
    EXPECT_EQ(a, 1);
}
