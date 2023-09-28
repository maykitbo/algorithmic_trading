#include "../common/data_struct.h"

#include <gtest/gtest.h>

using namespace s21;

void OneFileTest(const std::string &file_name, unsigned expected_size)
{
    Points points = ParserCsv::Parse(file_name);
    unsigned size = points.size();
    EXPECT_EQ(size, expected_size);
    for (unsigned i = 0; i < size - 1; ++i)
    {
        EXPECT_TRUE(points[i].x > 0.0);
        EXPECT_TRUE(points[i].x < points[i + 1].x);
    }
    EXPECT_TRUE(points[size - 1].x > 0.0);
    std::sort(points.begin(), points.end(), [](const Point &a, const Point &b) { return a.x < b.x; });
    points.erase(std::unique(points.begin(), points.end(), [](const Point &a, const Point &b) { return a.x == b.x; }), points.end());
    EXPECT_EQ(size, expected_size);
}

void BadFileTest(const std::string &file_name)
{
    EXPECT_THROW(ParserCsv::Parse(file_name), std::runtime_error);
}

#define __PARSER_TEST(name, size) TEST(Parser, name) { OneFileTest("materials/" #name ".csv", size); }
#define __BAD_PARSER_TEST(name) TEST(Parser, bad_##name) { BadFileTest("materials/bad_csv/" #name ".csv"); }

__PARSER_TEST(AAPL, 254)
__PARSER_TEST(ADBE, 254)
__PARSER_TEST(CVX_original, 254)
__PARSER_TEST(CVX, 9)
__PARSER_TEST(CVX2, 9)
__PARSER_TEST(DPZ, 254)
__PARSER_TEST(F, 254)

__BAD_PARSER_TEST(AAPL)
__BAD_PARSER_TEST(CVX)
__BAD_PARSER_TEST(qwerty)
