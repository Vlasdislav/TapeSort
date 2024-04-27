#include "FileTape.hpp"
#include "ConfigMap.hpp"
#include "TapeSort.hpp"
#include "settings.hpp"
#include <gtest/gtest.h>

TEST(ConfigMap, Include) {
    ConfigMap{};
    configMap cm = ConfigMap::getConfigMap();
    EXPECT_EQ(cm.size(), 4);
    EXPECT_TRUE(cm.find("read_delay") != cm.end());
    EXPECT_TRUE(cm.find("write_delay") != cm.end());
    EXPECT_TRUE(cm.find("rewind_delay") != cm.end());
    EXPECT_TRUE(cm.find("shift_delay") != cm.end());
}

TEST(FileTape, Constructor) {
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

TEST(FileTape, Write) {
    std::string ft_name = "files/write.txt";
    FileTape ft(ft_name);
    EXPECT_TRUE(ft.isEnd());
    EXPECT_EQ(ft.getCurrentPos(), 0);
    ft.write(1);
    EXPECT_EQ(ft.getCurrentPos(), 1);
    ft.write(2);
    EXPECT_EQ(ft.getCurrentPos(), 2);
    ft.write(3);
    EXPECT_EQ(ft.getCurrentPos(), 3);
    EXPECT_TRUE(ft.isEnd());
}

namespace {
    void createFileWithSequence(const std::string& filename, const std::string& seq) {
        system(("echo " + seq + " > " + filename).data());
    }

    void deleteEndlInFile(const std::string& filename) {
        // Удаляется перенос строки в конце файла.
        // Применяется для файлов сгенерированных через bash
        // у таких файлов в конце всегда есть перенос.
        // Программа работает с файлами без переноса и
        // возвращает тоже без переноса
        system(("tr -d '\\n' < " + filename + " > temp.txt && mv temp.txt " + filename).data());
    }

    bool isEqualFiles(const std::string& lhs_filename, const std::string& rhs_filename) {
        // Так при тестировании все переносы удаляются,
        // а у полученных файлов программы их нет,
        // а `diff` требует чтобы были пришлось добавить
        std::ofstream lhs_file(lhs_filename);
        std::ofstream rhs_file(rhs_filename);
        lhs_file << '\n';
        rhs_file << '\n';
        return system(("diff " + lhs_filename + " " + rhs_filename).data()) == 0;
    }
}

TEST(FileTape, Read) {
    std::string ft_name = "files/read.txt";
    createFileWithSequence(ft_name, "1 2 3");
    FileTape ft(ft_name);
    EXPECT_FALSE(ft.isEnd());
    int32_t a = -1;
    EXPECT_EQ(ft.getCurrentPos(), 0);
    EXPECT_TRUE(opt::assign(a, ft.read()));
    EXPECT_EQ(a, 1);
    EXPECT_EQ(ft.getCurrentPos(), 1);
    EXPECT_TRUE(opt::assign(a, ft.read()));
    EXPECT_EQ(a, 2);
    EXPECT_EQ(ft.getCurrentPos(), 2);
    EXPECT_TRUE(opt::assign(a, ft.read()));
    EXPECT_EQ(a, 3);
    EXPECT_EQ(ft.getCurrentPos(), 3);
    EXPECT_FALSE(opt::assign(a, ft.read()));
    EXPECT_TRUE(ft.isEnd());
}

TEST(TapeSort, Merge) {
    std::string f1 = "files/f1.txt";
    std::string f2 = "files/f2.txt";
    std::string res = "files/res.txt";
    std::string ans = "files/ans.txt";
    {
        createFileWithSequence(f1, "1 3 5");
        createFileWithSequence(f2, "2 4 6");
        createFileWithSequence(ans, "1 2 3 4 5 6");
        TapeSort::mergeTwoFiles(f1, f2, res);
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(res, ans));
    }
    {
        createFileWithSequence(f1, "1");
        createFileWithSequence(f2, "2");
        createFileWithSequence(ans, "1 2");
        TapeSort::mergeTwoFiles(f1, f2, res);
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(res, ans));
    }
    {
        createFileWithSequence(f1, "");
        createFileWithSequence(f2, "");
        createFileWithSequence(ans, "");
        TapeSort::mergeTwoFiles(f1, f2, res);
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(res, ans));
    }
    {
        createFileWithSequence(f1, "");
        createFileWithSequence(f2, "2 4 6");
        createFileWithSequence(ans, "2 4 6");
        TapeSort::mergeTwoFiles(f1, f2, res);
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(res, ans));
    }
}

TEST(TapeSort, Sort) {
    std::string in = "files/input.txt";
    std::string out = "files/output.txt";
    std::string ans = "files/ans.txt";
    {
        createFileWithSequence(in, "5 4 3 2 1");
        deleteEndlInFile(in);
        FileTape input(in);
        FileTape output(out);
        TapeSort::sort(input, output, 10000);
        createFileWithSequence(ans, "1 2 3 4 5");
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(out, ans));
    }
    {
        createFileWithSequence(in, "5 4 3 2 1");
        deleteEndlInFile(in);
        FileTape input(in);
        FileTape output(out);
        TapeSort::sort(input, output, 4);
        createFileWithSequence(ans, "1 2 3 4 5");
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(out, ans));
    }
    {
        createFileWithSequence(in, "");
        deleteEndlInFile(in);
        FileTape input(in);
        FileTape output(out);
        TapeSort::sort(input, output, 4);
        createFileWithSequence(ans, "");
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(out, ans));
    }
    {
        createFileWithSequence(in, std::to_string(INT_MAX));
        deleteEndlInFile(in);
        FileTape input(in);
        FileTape output(out);
        TapeSort::sort(input, output, 4);
        createFileWithSequence(ans, std::to_string(INT_MAX));
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(out, ans));
    }
    {
        createFileWithSequence(in, "0 1 1023 013 1000 1000 -1 40 90 0 -20 -100 -1");
        deleteEndlInFile(in);
        FileTape input(in);
        FileTape output(out);
        TapeSort::sort(input, output, 4);
        createFileWithSequence(ans, "-20 -13 -1 -1 0 0 1 40 90 100 1000 1023 1000");
        deleteEndlInFile(ans);
        EXPECT_TRUE(isEqualFiles(out, ans));
    }
}
